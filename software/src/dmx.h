/* dmx-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dmx.h: DMX master and slave protocol implementation
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

#ifndef DMX_H
#define DMX_H

#include <stdint.h>
#include <stdbool.h>

#include "communication.h"

#include "bricklib2/utility/led_flicker.h"

#define DMX_OVERSAMPLING 16
#define DMX_BAUDRATE     250000

#define DMX_FRAME_PAYLOAD_LENGTH_MAX 512

// http://www.dmx512-online.com/packt.html
#define DMX_TIME_MTBF  0    // Mark Time Between Frames
#define DMX_TIME_BREAK 88   // Break Time
#define DMX_TIME_MAB   8    // Mark After Break
#define DMX_TIME_MTBP  0    // Mark Time Between Packets

typedef struct {
	uint8_t start_code;
	uint8_t payload[DMX_FRAME_PAYLOAD_LENGTH_MAX];
	uint16_t length;
	uint32_t frame_number;
} __attribute__((packed)) DMXFrame;

typedef struct {
	DMXFrame frame_write_in;
	bool frame_write_in_ready;
	DMXFrame frame_write_out;

	DMXFrame frame_read_in[2];
	DMXFrame frame_read_out;
	uint16_t frame_read_out_index;
	uint8_t frame_next_read_in;
	uint8_t frame_next_copy;
	bool frame_next_data_consumed;

	uint32_t frame_number;

	bool new_frame_allowed;

	uint16_t frame_duration;
	uint32_t frame_duration_timestamp;

	uint32_t error_count_overrun;
	uint32_t error_count_framing;

	LEDFlickerState red_led_state;
	LEDFlickerState yellow_led_state;

	uint8_t mode;

	bool frame_started_callback_enabled;
	bool frame_available_callback_enabled;
	bool frame_callback_enabled;
	bool frame_error_count_callback_enabled;

	bool frame_started_callback;
	bool frame_available_callback;
	bool frame_callback;
} DMX;

void dmx_change_mode(DMX *dmx, const uint8_t mode);

void dmx_init(DMX *dmx);
void dmx_tick(DMX *dmx);

#endif
