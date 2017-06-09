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

#define DMX_FRAME_PAYLOAD_LENGTH 512

// http://www.dmx512-online.com/packt.html
#define DMX_TIME_MTBF  0    // Mark Time Between Frames
#define DMX_TIME_BREAK 88   // Break Time
#define DMX_TIME_MAB   8    // Mark After Break
#define DMX_TIME_MTBP  0    // Mark Time Between Packets

typedef struct {
	uint8_t payload[DMX_FRAME_PAYLOAD_LENGTH + 1]; // 0 = start code, 1-512 = data
	uint16_t length;
} DMXFrame;

typedef struct {
	DMXFrame frame_write_in;
	DMXFrame frame_write_out;
	DMXFrame frame_read;
} DMX;

void dmx_init(DMX *dmx);
void dmx_tick(DMX *dmx);

#endif
