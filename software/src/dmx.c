/* dmx-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dmx.c: DMX master and slave protocol implementation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "dmx.h"

#include "configs/config.h"
#include "configs/config_dmx.h"

#include "bricklib2/hal/system_timer/system_timer.h"

#include "xmc_uart.h"
#include "xmc_scu.h"
#include "xmc_ccu4.h"

#include "communication.h"

#define DMX_TIME_BETWEEN_SLOTS (0b1 << 8)
#define DMX_READ_CAPTURE_BREAK_COUNT (88/8) // 8us per tick

#define dmx_rx_irq_handler  IRQ_Hdlr_11
#define dmx_tx_irq_handler  IRQ_Hdlr_12
#define dmx_tff_irq_handler IRQ_Hdlr_13
#define dmx_rxa_irq_handler IRQ_Hdlr_14
#define dmx_timer_handler   IRQ_Hdlr_21


extern DMX dmx;

static bool dmx_tff_break_sent = false;


static uint8_t *dmx_payload_write_start   = dmx.frame_write_out.payload;
static uint8_t *dmx_payload_write_current = dmx.frame_write_out.payload;
static uint8_t *dmx_payload_write_end     = dmx.frame_write_out.payload + 512;

static uint8_t *dmx_payload_read_start0  = &dmx.frame_read_in[0].start_code;
static uint8_t *dmx_payload_read_start1  = &dmx.frame_read_in[1].start_code;
static uint8_t *dmx_payload_read_current = &dmx.frame_read_in[0].start_code;
static uint8_t *dmx_payload_read_end_cmp = &dmx.frame_read_in[0].start_code;
static uint8_t *dmx_payload_read_end0    = dmx.frame_read_in[0].payload + 512;
static uint8_t *dmx_payload_read_end1    = dmx.frame_read_in[1].payload + 512;



void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) dmx_tx_irq_handler(void) {
	while(!XMC_USIC_CH_TXFIFO_IsFull(DMX_USIC)) {
		DMX_USIC->IN[0] = DMX_TIME_BETWEEN_SLOTS | *dmx_payload_write_current++;
		if(dmx_payload_write_current >= dmx_payload_write_end) {
			dmx.frame_number++;
			dmx_payload_write_current = dmx_payload_write_start;
			XMC_USIC_CH_TXFIFO_DisableEvent(DMX_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

			return;
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) dmx_tff_irq_handler(void) {
	if((DMX_USIC->PSR_ASCMode & (XMC_UART_CH_STATUS_FLAG_TRANSMITTER_FRAME_FINISHED | XMC_UART_CH_STATUS_FLAG_TRANSFER_STATUS_BUSY)) == XMC_UART_CH_STATUS_FLAG_TRANSMITTER_FRAME_FINISHED) {
		// Here we have to insert a 88us break.

		// After we set the output to low we "write" 2 bytes to the buffer.
		// Sending two bytes takes 11 bit (1 start, 2 stop, 8 data) per byte with 4us per bit = 88us!
		// The data is not actually written, but the tff irq is called again after 88us

		// Since the next data is only send after the next tick call, we will wait a bit
		// longer then 88us in reality (measurements show about ~120us).
		// This is good, since not all DMX slaves do have perfect clocks.
		if(dmx_tff_break_sent) {
			dmx.new_frame_allowed = true;
		} else {
			const XMC_GPIO_CONFIG_t tx_pin_config_low = {
				.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
				.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW
			};
			XMC_GPIO_Init(DMX_TX_PIN, &tx_pin_config_low); // TODO: Replace with necessary calls
			DMX_USIC->IN[0] = 0;
			DMX_USIC->IN[0] = 0;
		}

		dmx_tff_break_sent = !dmx_tff_break_sent;
	}
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) dmx_rx_irq_handler(void) {
	while(!XMC_USIC_CH_RXFIFO_IsEmpty(DMX_USIC)) {
		if(dmx_payload_read_current < dmx_payload_read_end_cmp) {
			*dmx_payload_read_current = DMX_USIC->OUTR;
			dmx_payload_read_current++;
		} else {
			if(dmx.red_led_state.config == LED_FLICKER_CONFIG_EXTERNAL) {
				XMC_GPIO_SetOutputLow(DMX_LED_RED_PIN);
			}
			dmx.error_count_overrun++;

		  	// Disable USIC Standard Receive Buffer interrupt
		    XMC_USIC_CH_RXFIFO_DisableEvent(DMX_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE);
		    // Clear receive buffer status
		    XMC_USIC_CH_RXFIFO_ClearEvent(DMX_USIC, XMC_USIC_CH_RXFIFO_EVENT_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_ERROR | XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE);
		    XMC_USIC_CH_RXFIFO_Flush(DMX_USIC);

		    return;
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) dmx_rxa_irq_handler(void) {
	dmx.error_count_framing++;
	if(dmx.red_led_state.config == LED_FLICKER_CONFIG_EXTERNAL) {
		XMC_GPIO_SetOutputLow(DMX_LED_RED_PIN);
	}

	// Call rx handler, we try to handle the data even in case of a framing error
	dmx_rx_irq_handler();

}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) dmx_timer_handler(void) {
	XMC_CCU4_SLICE_StopTimer(CCU41_CC41);
	XMC_CCU4_SLICE_ClearTimer(CCU41_CC41);

	// Handle rx if data in buffer left
	dmx_rx_irq_handler();

	const uint16_t length = 512 - (dmx_payload_read_end_cmp - dmx_payload_read_current);
	dmx.frame_read_in[dmx.frame_next_read_in].length = length;

	if(length > 0) {
		if(dmx.frame_next_copy == 0xFF && dmx.frame_next_data_consumed) {
			dmx.frame_next_copy = dmx.frame_next_read_in;
			dmx.frame_next_read_in = (dmx.frame_next_read_in + 1) & 1;
			dmx.frame_number++;
		}
	}

	// Start from beginning again
	if(dmx.frame_next_read_in == 0) {
		dmx_payload_read_current = dmx_payload_read_start0;
		dmx_payload_read_end_cmp = dmx_payload_read_end0;
	} else {
		dmx_payload_read_current = dmx_payload_read_start1;
		dmx_payload_read_end_cmp = dmx_payload_read_end1;
	}

	// Enable USIC Standard Receive Buffer interrupt
	XMC_USIC_CH_RXFIFO_EnableEvent(DMX_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);
}

void dmx_init_timer(DMX *dmx) {
	XMC_CCU4_SLICE_CAPTURE_CONFIG_t capture_config = {
		.fifo_enable = true,
		.timer_clear_mode = XMC_CCU4_SLICE_TIMER_CLEAR_MODE_ALWAYS,
		.same_event = false,
		.ignore_full_flag = true,
		.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
		.prescaler_initval = 0,
		.float_limit = 0,
		.timer_concatenation = false,
	};

	XMC_CCU4_SLICE_EVENT_CONFIG_t capture_event0_config = {
		.mapped_input = XMC_CCU4_SLICE_INPUT_AA,
		.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE,
		.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_LOW,
		.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES,
	};

	XMC_CCU4_SLICE_EVENT_CONFIG_t capture_event1_config = {
		.mapped_input = XMC_CCU4_SLICE_INPUT_AA,
		.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
		.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
		.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES,
	};


    XMC_CCU4_Init(DMX_TIMER_CCU4, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

    // Start the prescaler
    XMC_CCU4_StartPrescaler(DMX_TIMER_CCU4);

	XMC_CCU4_SLICE_CaptureInit(DMX_TIMER_CCU4_SLICE, &capture_config);

	// Input selection, edge trigger, level trigger and LPF cycles configuration
	XMC_CCU4_SLICE_ConfigureEvent(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_EVENT_0, &capture_event0_config);
	XMC_CCU4_SLICE_ConfigureEvent(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_EVENT_1, &capture_event1_config);

	// Timer started at Falling edge (Event0), Timer stopped at Rising Edge (Event 1)
	XMC_CCU4_SLICE_StartConfig(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_EVENT_0, XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR);
	XMC_CCU4_SLICE_StopConfig(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_EVENT_1, XMC_CCU4_SLICE_END_MODE_TIMER_STOP_CLEAR);

	// Timer single-shot mode
	XMC_CCU4_SLICE_SetTimerRepeatMode(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_TIMER_REPEAT_MODE_SINGLE);

	// Enable capture slice (clearing a slice from idle mode)
	XMC_CCU4_EnableClock(DMX_TIMER_CCU4, 1);


	XMC_CCU4_SLICE_SetTimerCountingMode(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA);

	// We allow 80us break (88us according to standard), this makes sure that master can have up to 10% jitter
	// 80/(1/96.0) = 7680
    XMC_CCU4_SLICE_SetTimerPeriodMatch(DMX_TIMER_CCU4_SLICE, 7680);

    // Set the compare register values
    XMC_CCU4_SLICE_SetTimerCompareMatch(DMX_TIMER_CCU4_SLICE, 0);

    // Requesting the shadow transfer for the CCU4 slice
    XMC_CCU4_EnableShadowTransfer(DMX_TIMER_CCU4, XMC_CCU4_SHADOW_TRANSFER_SLICE_1);

	// Enable the event generation for event_id
	XMC_CCU4_SLICE_EnableEvent(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);

	// Configure the SR line for the event
	XMC_CCU4_SLICE_SetInterruptNode(DMX_TIMER_CCU4_SLICE, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);

	// Interrupt configuration for Capture
	NVIC_SetPriority(DMX_IRQ_TIMER, DMX_IRQ_TIMER_PRIORITY);

	XMC_SCU_SetInterruptControl(DMX_IRQ_TIMER, DMX_IRQCTRL_TIMER);
	NVIC_EnableIRQ(DMX_IRQ_TIMER);
}

void dmx_init_hardware(DMX *dmx, const uint8_t mode) {
	// TX pin configuration
	const XMC_GPIO_CONFIG_t tx_pin_config = {
		.mode             = DMX_TX_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// RX pin configuration
	const XMC_GPIO_CONFIG_t rx_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	// TXE (tx enable) pin configuration
	const XMC_GPIO_CONFIG_t enable_pin_config_master = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	const XMC_GPIO_CONFIG_t enable_pin_config_slave = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	// Configure  pins
	XMC_GPIO_Init(DMX_TX_PIN, &tx_pin_config);
	XMC_GPIO_Init(DMX_RX_PIN, &rx_pin_config);
	if(mode == DMX_DMX_MODE_MASTER) {
		XMC_GPIO_Init(DMX_TXE_PIN, &enable_pin_config_master);
		XMC_GPIO_Init(DMX_NRXE_PIN, &enable_pin_config_master);
	} else {
		XMC_GPIO_Init(DMX_TXE_PIN, &enable_pin_config_slave);
		XMC_GPIO_Init(DMX_NRXE_PIN, &enable_pin_config_slave);
	}

	// Initialize USIC channel in UART master mode
	// USIC channel configuration
	XMC_UART_CH_CONFIG_t config;
	config.oversampling = DMX_OVERSAMPLING;
	config.baudrate     = DMX_BAUDRATE;
	config.stop_bits    = 2;
	config.parity_mode  = XMC_USIC_CH_PARITY_MODE_NONE;
	if(mode == DMX_DMX_MODE_MASTER) {
		config.frame_length = 9;
		config.data_bits    = 9;
	} else {
		config.frame_length = 8;
		config.data_bits    = 8;
	}

	XMC_UART_CH_Init(DMX_USIC, &config);

	// Set input source path
	XMC_UART_CH_SetInputSource(DMX_USIC, DMX_RX_INPUT, DMX_RX_SOURCE);

	// Configure transmit FIFO
	XMC_USIC_CH_TXFIFO_Configure(DMX_USIC, 32, XMC_USIC_CH_FIFO_SIZE_32WORDS, 16);

	// Configure receive FIFO
	XMC_USIC_CH_RXFIFO_Configure(DMX_USIC, 0, XMC_USIC_CH_FIFO_SIZE_32WORDS, 16);

	// UART protocol events
	XMC_USIC_CH_SetInterruptNodePointer(DMX_USIC, XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL, DMX_SERVICE_REQUEST_TFF);
	XMC_USIC_CH_SetInterruptNodePointer(DMX_USIC, XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE, DMX_SERVICE_REQUEST_RXA);
	XMC_UART_CH_EnableEvent(DMX_USIC, XMC_UART_CH_EVENT_FRAME_FINISHED);

	// Set service request for tx FIFO transmit interrupt
	XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(DMX_USIC, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, DMX_SERVICE_REQUEST_TX);

	// Set service request for rx FIFO receive interrupt
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(DMX_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, DMX_SERVICE_REQUEST_RX);
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(DMX_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, DMX_SERVICE_REQUEST_RX);

	// Set priority and enable NVIC node for transfer frame finished interrupt
	NVIC_SetPriority((IRQn_Type)DMX_IRQ_TFF, DMX_IRQ_TFF_PRIORITY);
	XMC_SCU_SetInterruptControl(DMX_IRQ_TFF, DMX_IRQCTRL_TFF);
	NVIC_EnableIRQ((IRQn_Type)DMX_IRQ_TFF);

	// Set priority and enable NVIC node for transmit interrupt
	NVIC_SetPriority((IRQn_Type)DMX_IRQ_TX, DMX_IRQ_TX_PRIORITY);
	XMC_SCU_SetInterruptControl(DMX_IRQ_TX, DMX_IRQCTRL_TX);
	NVIC_EnableIRQ((IRQn_Type)DMX_IRQ_TX);

	// Set priority and enable NVIC node for receive interrupt
	NVIC_SetPriority((IRQn_Type)DMX_IRQ_RX, DMX_IRQ_RX_PRIORITY);
	XMC_SCU_SetInterruptControl(DMX_IRQ_RX, DMX_IRQCTRL_RX);
	NVIC_EnableIRQ((IRQn_Type)DMX_IRQ_RX);

	// Set priority and enable NVIC node for receive interrupt
	NVIC_SetPriority((IRQn_Type)DMX_IRQ_RXA, DMX_IRQ_RXA_PRIORITY);
	XMC_SCU_SetInterruptControl(DMX_IRQ_RXA, DMX_IRQCTRL_RXA);
	NVIC_EnableIRQ((IRQn_Type)DMX_IRQ_RXA);

	// Start UART
	XMC_UART_CH_Start(DMX_USIC);

	XMC_USIC_CH_EnableEvent(DMX_USIC, XMC_USIC_CH_EVENT_ALTERNATIVE_RECEIVE);
}

void dmx_init_leds(DMX *dmx) {
	dmx->yellow_led_state.config  = DMX_COMMUNICATION_LED_CONFIG_SHOW_COMMUNICATION;
	dmx->yellow_led_state.counter = 0;
	dmx->yellow_led_state.start   = 0;
	dmx->red_led_state.config     = LED_FLICKER_CONFIG_EXTERNAL;
	dmx->red_led_state.counter    = 0;
	dmx->red_led_state.start      = 0;

	// LED configuration
	XMC_GPIO_CONFIG_t led_pin_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	XMC_GPIO_Init(DMX_LED_RED_PIN, &led_pin_config);

	led_pin_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW; // Default on for yellow LED
	XMC_GPIO_Init(DMX_LED_YELLOW_PIN, &led_pin_config);
}

void dmx_init_memory(DMX *dmx, const bool initial) {
	if(initial) {
		// Reset all memory, set user settings to default
		memset(dmx, 0, sizeof(DMX));
		dmx->new_frame_allowed = true;
		dmx->frame_duration = 100;
		dmx->mode = DMX_DMX_MODE_MASTER;

		dmx->frame_write_in_ready = false;

		dmx->frame_started_callback_enabled = true;
		dmx->frame_available_callback_enabled = true;
		dmx->frame_callback_enabled = false;
		dmx->frame_error_count_callback_enabled = false;

		dmx->frame_next_copy = 0xFF;
		dmx->frame_next_data_consumed = true;
		dmx->frame_read_first = true;

		dmx->frame_duration_timestamp = system_timer_get_ms();
		dmx_payload_write_current = dmx_payload_write_start;
	} else {
		// Reset all memory, keep user settings
		memset(&dmx->frame_write_in, 0, sizeof(DMXFrame));
		dmx->frame_write_in_ready = false;
		memset(&dmx->frame_write_out, 0, sizeof(DMXFrame));

		memset(&dmx->frame_read_in[0], 0, sizeof(DMXFrame));
		memset(&dmx->frame_read_in[1], 0, sizeof(DMXFrame));
		memset(&dmx->frame_read_out, 0, sizeof(DMXFrame));

		dmx->frame_read_out_index = 0;
		dmx->frame_next_read_in = 0;
		dmx->frame_next_copy = 0xFF;
		dmx->frame_next_data_consumed = true;
		dmx->frame_read_first = true;

		dmx->frame_number = 0;

		dmx->new_frame_allowed = true;
		dmx->frame_duration_timestamp = system_timer_get_ms();

		dmx->error_count_overrun = 0;
		dmx->error_count_framing = 0;

		dmx->frame_started_callback = false;
		dmx->frame_available_callback = false;
		dmx->frame_callback = false;
	}
}

void dmx_change_mode(DMX *dmx, const uint8_t mode) {
	dmx->error_count_overrun = 0;
	dmx->error_count_framing = 0;
	dmx->frame_number = 0;

	if(dmx->mode == mode) {
		return;
	}

	__disable_irq();
	dmx->mode = mode;

	// Flush and disable buffer
	dmx_payload_write_current = dmx_payload_write_start;
	XMC_USIC_CH_TXFIFO_DisableEvent(DMX_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);

	dmx_payload_read_current = dmx_payload_read_start0;
	dmx_payload_read_end_cmp = dmx_payload_read_end0;
    XMC_USIC_CH_RXFIFO_DisableEvent(DMX_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);
    XMC_USIC_CH_RXFIFO_ClearEvent(DMX_USIC, XMC_USIC_CH_RXFIFO_EVENT_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_ERROR | XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE);
    XMC_USIC_CH_RXFIFO_Flush(DMX_USIC);

	dmx_init_memory(dmx, false);
	dmx_init_hardware(dmx, dmx->mode);
	dmx_init_timer(dmx);

	if(dmx->mode == DMX_DMX_MODE_MASTER) {
		NVIC_DisableIRQ(DMX_IRQ_TIMER);
	} else {
		NVIC_EnableIRQ(DMX_IRQ_TIMER);
	}
	NVIC_ClearPendingIRQ(DMX_IRQ_TIMER);
	__enable_irq();
}

void dmx_init(DMX *dmx) {
	__disable_irq();
	dmx_init_memory(dmx, true);
	dmx_init_leds(dmx);
	dmx_init_hardware(dmx, DMX_DMX_MODE_MASTER);
	dmx_init_timer(dmx);
	__enable_irq();
}


void dmx_tick(DMX *dmx) {
	if(dmx->mode == DMX_DMX_MODE_MASTER) {
		if(dmx->new_frame_allowed && dmx->frame_write_in_ready) {
			memcpy(&dmx->frame_write_out, &dmx->frame_write_in, sizeof(DMXFrame));
			dmx->frame_write_in_ready = false;

			// TODO: Set flag to write next tick?
			if(dmx->frame_read_out_index == 0) {
				memcpy(&dmx->frame_read_out, &dmx->frame_write_in, sizeof(DMXFrame));
			}
		}

		if(dmx->new_frame_allowed && system_timer_is_time_elapsed_ms(dmx->frame_duration_timestamp, dmx->frame_duration)) {
			dmx->frame_duration_timestamp += dmx->frame_duration;

			// Make sure to never overflow if the frame duration is set lower
			// than the time needed to transfer one frame!
			if(dmx->frame_duration_timestamp < system_timer_get_ms()) {
				dmx->frame_duration_timestamp = system_timer_get_ms();
			}

			dmx->frame_started_callback = true;
			dmx->frame_number++;

			if(dmx->frame_write_out.length > 0) {
				dmx->new_frame_allowed = false;
				dmx_tff_break_sent = false; // Reset the break sent status variable

				dmx_payload_write_end = dmx_payload_write_start + dmx->frame_write_out.length;

				// TODO: Do we have to disable the IRQs here
				//       to make sure that there is no TFP interrupt during our "fake MAB"?
				DMX_USIC->IN[0] = DMX_TIME_BETWEEN_SLOTS; // MAB = 8us high = 2 stop bits at end
				DMX_USIC->IN[0] = DMX_TIME_BETWEEN_SLOTS | dmx->frame_write_out.start_code;
				XMC_USIC_CH_TXFIFO_EnableEvent(DMX_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
				XMC_USIC_CH_TriggerServiceRequest(DMX_USIC, DMX_SERVICE_REQUEST_TX);

				const XMC_GPIO_CONFIG_t tx_pin_config = {
					.mode             = DMX_TX_PIN_AF,
					.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
				};
				XMC_GPIO_Init(DMX_TX_PIN, &tx_pin_config);

				dmx->yellow_led_state.counter += LED_FLICKER_STATUS_COUNTER_MAX/10; // We flicker once per 5 send dmx packet
			}
		}
	} else {
		if(dmx->frame_next_copy != 0xFF && dmx->frame_next_data_consumed) {
			if(dmx->frame_read_first) {
				// We discard the very first read frame.
				// We can't guarantee that we were able to read a full frame in this case.
				dmx->frame_read_first = false;
				dmx->frame_next_data_consumed = true;
			} else {
				memcpy(&dmx->frame_read_out, &dmx->frame_read_in[dmx->frame_next_copy], sizeof(DMXFrame));
				dmx->frame_next_data_consumed = false;

				if(dmx->frame_available_callback_enabled) {
					dmx->frame_available_callback = true;
				}

				if(dmx->frame_callback_enabled) {
					dmx->frame_callback = true;
				}

				dmx->yellow_led_state.counter += LED_FLICKER_STATUS_COUNTER_MAX/10; // We flicker once per 5 send dmx packet
			}

			dmx->frame_next_copy = 0xFF;

		}
	}

	led_flicker_tick(&dmx->yellow_led_state, system_timer_get_ms(), DMX_LED_YELLOW_PIN);
	led_flicker_tick(&dmx->red_led_state,    system_timer_get_ms(), DMX_LED_RED_PIN);
}
