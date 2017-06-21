/* dmx-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/hal/system_timer/system_timer.h"

#include "dmx.h"
#include "configs/config_dmx.h"

#define CALLBACK_ERROR_COUNT_DEBOUNCE_MS 100

extern DMX dmx;

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_SET_DMX_MODE: return set_dmx_mode(message);
		case FID_GET_DMX_MODE: return get_dmx_mode(message, response);
		case FID_WRITE_FRAME_LOW_LEVEL: return write_frame_low_level(message);
		case FID_READ_FRAME_LOW_LEVEL: return read_frame_low_level(message, response);
		case FID_SET_FRAME_DURATION: return set_frame_duration(message);
		case FID_GET_FRAME_DURATION: return get_frame_duration(message, response);
		case FID_DRAW_FRAME: return draw_frame(message);
		case FID_GET_FRAME_ERROR_COUNT: return get_frame_error_count(message, response);
		case FID_SET_COMMUNICATION_LED_CONFIG: return set_communication_led_config(message);
		case FID_GET_COMMUNICATION_LED_CONFIG: return get_communication_led_config(message, response);
		case FID_SET_ERROR_LED_CONFIG: return set_error_led_config(message);
		case FID_GET_ERROR_LED_CONFIG: return get_error_led_config(message, response);
		case FID_SET_FRAME_CALLBACK_CONFIG: return set_frame_callback_config(message);
		case FID_GET_FRAME_CALLBACK_CONFIG: return get_frame_callback_config(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_dmx_mode(const SetDMXMode *data) {
	if(data->dmx_mode > DMX_DMX_MODE_SLAVE) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	dmx_change_mode(&dmx, data->dmx_mode);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_dmx_mode(const GetDMXMode *data, GetDMXMode_Response *response) {
	response->header.length = sizeof(GetDMXMode_Response);
	response->dmx_mode      = dmx.mode;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse write_frame_low_level(const WriteFrameLowLevel *data) {
	if((dmx.mode == DMX_DMX_MODE_SLAVE) ||
	   (data->frame_length > DMX_FRAME_PAYLOAD_LENGTH_MAX) ||
	   (data->frame_chunk_offset > data->frame_length)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	const uint16_t write_from = data->frame_chunk_offset;
	const uint16_t write_to   = MIN(data->frame_length, data->frame_chunk_offset + 60);
	const uint16_t length     = write_to - write_from;

	memcpy(&dmx.frame_write_in.payload[write_from], data->frame_chunk_data, length);

	if(write_to == data->frame_length) {
		dmx.frame_write_in.length = data->frame_length;
		dmx.frame_write_in_ready = true;
	} else {
		dmx.frame_write_in_ready = false;
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse read_frame_low_level(const ReadFrameLowLevel *data, ReadFrameLowLevel_Response *response) {
	if(dmx.frame_callback_enabled && dmx.mode == DMX_DMX_MODE_SLAVE) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	response->header.length = sizeof(ReadFrameLowLevel_Response);

	const uint16_t read_from = dmx.frame_read_out_index;
	const uint16_t read_to   = MIN(dmx.frame_read_out.length, dmx.frame_read_out_index + 56);
	const uint16_t length    = read_to-read_from;

	memcpy(response->frame_chunk_data, &dmx.frame_read_out.payload[read_from], length);
	memset(&response->frame_chunk_data[length], 0, 56-length); // If end of stream: Fill last bytes with 0

	response->frame_chunk_offset = read_from;
	response->frame_length = dmx.frame_read_out.length;
	response->frame_number = dmx.frame_number;

	if(read_to == dmx.frame_read_out.length) {
		dmx.frame_read_out_index = 0;
		if(dmx.mode == DMX_DMX_MODE_SLAVE) {
			dmx.frame_next_data_consumed = true;
		}
	} else {
		dmx.frame_read_out_index = read_to;
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_frame_duration(const SetFrameDuration *data) {
	dmx.frame_duration = data->frame_duration;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_frame_duration(const GetFrameDuration *data, GetFrameDuration_Response *response) {
	response->header.length  = sizeof(GetFrameDuration_Response);
	response->frame_duration = dmx.frame_duration;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse draw_frame(const DrawFrame *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_frame_error_count(const GetFrameErrorCount *data, GetFrameErrorCount_Response *response) {
	response->header.length = sizeof(GetFrameErrorCount_Response);
	response->overrun_error_count = dmx.error_count_overrun;
	response->framing_error_count = dmx.error_count_framing;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_communication_led_config(const SetCommunicationLEDConfig *data) {
	dmx.yellow_led_state.config = data->config;

	// Set LED according to value
	if(dmx.yellow_led_state.config == DMX_COMMUNICATION_LED_CONFIG_OFF) {
		XMC_GPIO_SetOutputHigh(DMX_LED_YELLOW_PIN);
	} else {
		XMC_GPIO_SetOutputLow(DMX_LED_YELLOW_PIN);
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_communication_led_config(const GetCommunicationLEDConfig *data, GetCommunicationLEDConfig_Response *response) {
	response->header.length = sizeof(GetCommunicationLEDConfig_Response);
	response->config        = dmx.yellow_led_state.config;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_error_led_config(const SetErrorLEDConfig *data) {
	// The error config and flicker config are not the same, we save
	// the "show error" option as "external".
	if(data->config == DMX_ERROR_LED_CONFIG_SHOW_ERROR) {
		dmx.red_led_state.config = LED_FLICKER_CONFIG_EXTERNAL;
	} else {
		dmx.red_led_state.config = data->config;
	}

	// Set LED according to value
	if(dmx.red_led_state.config == DMX_ERROR_LED_CONFIG_OFF ||
			dmx.red_led_state.config == LED_FLICKER_CONFIG_EXTERNAL) {
		XMC_GPIO_SetOutputHigh(DMX_LED_RED_PIN);
	} else {
		XMC_GPIO_SetOutputLow(DMX_LED_RED_PIN);
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_error_led_config(const GetErrorLEDConfig *data, GetErrorLEDConfig_Response *response) {
	response->header.length = sizeof(GetErrorLEDConfig_Response);

	if(dmx.red_led_state.config == LED_FLICKER_CONFIG_EXTERNAL) {
		response->config = DMX_ERROR_LED_CONFIG_SHOW_ERROR;
	}
	else {
		response->config = dmx.red_led_state.config;
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_frame_callback_config(const SetFrameCallbackConfig *data) {
	dmx.frame_started_callback_enabled     = data->frame_started_callback_enabled;
	dmx.frame_available_callback_enabled   = data->frame_available_callback_enabled;
	dmx.frame_callback_enabled             = data->frame_callback_enabled;
	dmx.frame_error_count_callback_enabled = data->frame_error_count_callback_enabled;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_frame_callback_config(const GetFrameCallbackConfig *data, GetFrameCallbackConfig_Response *response) {
	response->header.length                      = sizeof(GetFrameCallbackConfig_Response);
	response->frame_started_callback_enabled     = dmx.frame_started_callback_enabled;
	response->frame_available_callback_enabled   = dmx.frame_available_callback_enabled;
	response->frame_callback_enabled             = dmx.frame_callback_enabled;
	response->frame_error_count_callback_enabled = dmx.frame_error_count_callback_enabled;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}




bool handle_frame_started_callback(void) {
	static bool is_buffered = false;
	static FrameStarted_Callback cb;

	if(!is_buffered) {
		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(FrameStarted_Callback), FID_CALLBACK_FRAME_STARTED);
		if(dmx.frame_started_callback) {
			dmx.frame_started_callback = false;
			if(!dmx.frame_started_callback_enabled) {
				return false;
			}
		} else {
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(FrameStarted_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

bool handle_frame_available_callback(void) {
	static bool is_buffered = false;
	static FrameAvailable_Callback cb;

	if(!is_buffered) {
		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(FrameAvailable_Callback), FID_CALLBACK_FRAME_AVAILABLE);
		if(dmx.frame_available_callback_enabled && dmx.frame_available_callback) {
			cb.frame_number = dmx.frame_number;
			dmx.frame_available_callback = false;
		} else {
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(FrameAvailable_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

bool handle_frame_low_level_callback(void) {
	static bool is_buffered = false;
	static FrameLowLevel_Callback cb;

	if(!is_buffered) {
		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(FrameLowLevel_Callback), FID_CALLBACK_FRAME_LOW_LEVEL);
		if(dmx.frame_callback_enabled && dmx.frame_callback) {
			const uint16_t read_from = dmx.frame_read_out_index;
			const uint16_t read_to   = MIN(dmx.frame_read_out.length, dmx.frame_read_out_index + 56);
			const uint16_t length    = read_to-read_from;

			memcpy(cb.frame_chunk_data, &dmx.frame_read_out.payload[read_from], length);
			memset(&cb.frame_chunk_data[length], 0, 56-length); // If end of stream: Fill last bytes with 0

			cb.frame_chunk_offset = read_from;
			cb.frame_length = dmx.frame_read_out.length;
			cb.frame_number = dmx.frame_number;

			if(read_to == dmx.frame_read_out.length) {
				dmx.frame_read_out_index = 0;
				dmx.frame_callback = false;
				dmx.frame_next_data_consumed = true;
			} else {
				dmx.frame_read_out_index = read_to;
			}
		} else {
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(FrameLowLevel_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

bool handle_frame_error_count_callback(void) {
	static bool is_buffered = false;
	static FrameErrorCount_Callback cb;

	static uint32_t last_error_count_framing = 0;
	static uint32_t last_error_count_overrun = 0;
	static uint32_t last_time = 0;

	memset(&cb, 0, sizeof(cb));

	if(!dmx.frame_error_count_callback_enabled) {
		return false;
	}

	if(!is_buffered) {
		if(system_timer_is_time_elapsed_ms(last_time, CALLBACK_ERROR_COUNT_DEBOUNCE_MS) &&
		   (dmx.error_count_overrun != last_error_count_overrun || dmx.error_count_framing != last_error_count_framing)) {
			last_time = system_timer_get_ms();

			tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(FrameErrorCount_Callback), FID_CALLBACK_FRAME_ERROR_COUNT);
			cb.overrun_error_count = dmx.error_count_overrun;
			cb.framing_error_count = dmx.error_count_framing;

			is_buffered = true;
		}
		else {
			is_buffered = false;
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t *)&cb, sizeof(FrameErrorCount_Callback));

		is_buffered = false;

		return true;
	}
	else {
		is_buffered = true;
	}

	return false;
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}
