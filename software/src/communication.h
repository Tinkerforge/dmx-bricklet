/* dmx-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define DMX_DMX_MODE_MASTER 0
#define DMX_DMX_MODE_SLAVE 1

#define DMX_COMMUNICATION_LED_CONFIG_OFF 0
#define DMX_COMMUNICATION_LED_CONFIG_ON 1
#define DMX_COMMUNICATION_LED_CONFIG_SHOW_HEARTBEAT 2
#define DMX_COMMUNICATION_LED_CONFIG_SHOW_COMMUNICATION 3

#define DMX_ERROR_LED_CONFIG_OFF 0
#define DMX_ERROR_LED_CONFIG_ON 1
#define DMX_ERROR_LED_CONFIG_SHOW_HEARTBEAT 2
#define DMX_ERROR_LED_CONFIG_SHOW_ERROR 3

#define DMX_BOOTLOADER_MODE_BOOTLOADER 0
#define DMX_BOOTLOADER_MODE_FIRMWARE 1
#define DMX_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define DMX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define DMX_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define DMX_BOOTLOADER_STATUS_OK 0
#define DMX_BOOTLOADER_STATUS_INVALID_MODE 1
#define DMX_BOOTLOADER_STATUS_NO_CHANGE 2
#define DMX_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define DMX_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define DMX_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define DMX_STATUS_LED_CONFIG_OFF 0
#define DMX_STATUS_LED_CONFIG_ON 1
#define DMX_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define DMX_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_SET_DMX_MODE 1
#define FID_GET_DMX_MODE 2
#define FID_WRITE_FRAME_LOW_LEVEL 3
#define FID_READ_FRAME_LOW_LEVEL 4
#define FID_SET_FRAME_DURATION 5
#define FID_GET_FRAME_DURATION 6
#define FID_GET_FRAME_ERROR_COUNT 7
#define FID_SET_COMMUNICATION_LED_CONFIG 8
#define FID_GET_COMMUNICATION_LED_CONFIG 9
#define FID_SET_ERROR_LED_CONFIG 10
#define FID_GET_ERROR_LED_CONFIG 11
#define FID_SET_FRAME_CALLBACK_CONFIG 12
#define FID_GET_FRAME_CALLBACK_CONFIG 13

#define FID_CALLBACK_FRAME_STARTED 14
#define FID_CALLBACK_FRAME_AVAILABLE 15
#define FID_CALLBACK_FRAME_LOW_LEVEL 16
#define FID_CALLBACK_FRAME_ERROR_COUNT 17

typedef struct {
	TFPMessageHeader header;
	uint8_t dmx_mode;
} __attribute__((__packed__)) SetDMXMode;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetDMXMode;

typedef struct {
	TFPMessageHeader header;
	uint8_t dmx_mode;
} __attribute__((__packed__)) GetDMXMode_Response;

typedef struct {
	TFPMessageHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[60];
} __attribute__((__packed__)) WriteFrameLowLevel;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) ReadFrameLowLevel;

typedef struct {
	TFPMessageHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[56];
	uint32_t frame_number;
} __attribute__((__packed__)) ReadFrameLowLevel_Response;

typedef struct {
	TFPMessageHeader header;
	uint16_t frame_duration;
} __attribute__((__packed__)) SetFrameDuration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetFrameDuration;

typedef struct {
	TFPMessageHeader header;
	uint16_t frame_duration;
} __attribute__((__packed__)) GetFrameDuration_Response;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetFrameErrorCount;

typedef struct {
	TFPMessageHeader header;
	uint32_t overrun_error_count;
	uint32_t framing_error_count;
} __attribute__((__packed__)) GetFrameErrorCount_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) SetCommunicationLEDConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetCommunicationLEDConfig;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) GetCommunicationLEDConfig_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) SetErrorLEDConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetErrorLEDConfig;

typedef struct {
	TFPMessageHeader header;
	uint8_t config;
} __attribute__((__packed__)) GetErrorLEDConfig_Response;

typedef struct {
	TFPMessageHeader header;
	bool frame_started_callback_enabled;
	bool frame_available_callback_enabled;
	bool frame_callback_enabled;
	bool frame_error_count_callback_enabled;
} __attribute__((__packed__)) SetFrameCallbackConfig;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetFrameCallbackConfig;

typedef struct {
	TFPMessageHeader header;
	bool frame_started_callback_enabled;
	bool frame_available_callback_enabled;
	bool frame_callback_enabled;
	bool frame_error_count_callback_enabled;
} __attribute__((__packed__)) GetFrameCallbackConfig_Response;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) FrameStarted_Callback;

typedef struct {
	TFPMessageHeader header;
	uint32_t frame_number;
} __attribute__((__packed__)) FrameAvailable_Callback;

typedef struct {
	TFPMessageHeader header;
	uint16_t frame_length;
	uint16_t frame_chunk_offset;
	uint8_t frame_chunk_data[56];
	uint32_t frame_number;
} __attribute__((__packed__)) FrameLowLevel_Callback;

typedef struct {
	TFPMessageHeader header;
	uint32_t overrun_error_count;
	uint32_t framing_error_count;
} __attribute__((__packed__)) FrameErrorCount_Callback;


// Function prototypes
BootloaderHandleMessageResponse set_dmx_mode(const SetDMXMode *data);
BootloaderHandleMessageResponse get_dmx_mode(const GetDMXMode *data, GetDMXMode_Response *response);
BootloaderHandleMessageResponse write_frame_low_level(const WriteFrameLowLevel *data);
BootloaderHandleMessageResponse read_frame_low_level(const ReadFrameLowLevel *data, ReadFrameLowLevel_Response *response);
BootloaderHandleMessageResponse set_frame_duration(const SetFrameDuration *data);
BootloaderHandleMessageResponse get_frame_duration(const GetFrameDuration *data, GetFrameDuration_Response *response);
BootloaderHandleMessageResponse get_frame_error_count(const GetFrameErrorCount *data, GetFrameErrorCount_Response *response);
BootloaderHandleMessageResponse set_communication_led_config(const SetCommunicationLEDConfig *data);
BootloaderHandleMessageResponse get_communication_led_config(const GetCommunicationLEDConfig *data, GetCommunicationLEDConfig_Response *response);
BootloaderHandleMessageResponse set_error_led_config(const SetErrorLEDConfig *data);
BootloaderHandleMessageResponse get_error_led_config(const GetErrorLEDConfig *data, GetErrorLEDConfig_Response *response);
BootloaderHandleMessageResponse set_frame_callback_config(const SetFrameCallbackConfig *data);
BootloaderHandleMessageResponse get_frame_callback_config(const GetFrameCallbackConfig *data, GetFrameCallbackConfig_Response *response);

// Callbacks
bool handle_frame_started_callback(void);
bool handle_frame_available_callback(void);
bool handle_frame_low_level_callback(void);
bool handle_frame_error_count_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 4
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_frame_started_callback, \
	handle_frame_available_callback, \
	handle_frame_low_level_callback, \
	handle_frame_error_count_callback, \


#endif
