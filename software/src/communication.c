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
#include "bricklib2/protocols/tfp/tfp.h"

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_SET_DMX_MODE: return set_dmx_mode(message);
		case FID_GET_DMX_MODE: return get_dmx_mode(message, response);
		case FID_WRITE_FRAME_LOW_LEVEL: return write_frame_low_level(message, response);
		case FID_READ_FRAME_LOW_LEVEL: return read_frame_low_level(message, response);
		case FID_SET_FRAME_DURATION: return set_frame_duration(message);
		case FID_GET_FRAME_DURATION: return get_frame_duration(message, response);
		case FID_DRAW_FRAME: return draw_frame(message);
		case FID_SET_FRAME_CALLBACK_CONFIGURATION: return set_frame_callback_configuration(message);
		case FID_GET_FRAME_CALLBACK_CONFIGURATION: return get_frame_callback_configuration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_dmx_mode(const SetDMXMode *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_dmx_mode(const GetDMXMode *data, GetDMXMode_Response *response) {
	response->header.length = sizeof(GetDMXMode_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse write_frame_low_level(const WriteFrameLowLevel *data, WriteFrameLowLevel_Response *response) {
	response->header.length = sizeof(WriteFrameLowLevel_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse read_frame_low_level(const ReadFrameLowLevel *data, ReadFrameLowLevel_Response *response) {
	response->header.length = sizeof(ReadFrameLowLevel_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_frame_duration(const SetFrameDuration *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_frame_duration(const GetFrameDuration *data, GetFrameDuration_Response *response) {
	response->header.length = sizeof(GetFrameDuration_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse draw_frame(const DrawFrame *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse set_frame_callback_configuration(const SetFrameCallbackConfiguration *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_frame_callback_configuration(const GetFrameCallbackConfiguration *data, GetFrameCallbackConfiguration_Response *response) {
	response->header.length = sizeof(GetFrameCallbackConfiguration_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}




bool handle_frame_started_callback(void) {
	static bool is_buffered = false;
	static FrameStarted_Callback cb;

	if(!is_buffered) {
		tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(FrameStarted_Callback), FID_CALLBACK_FRAME_STARTED);
		// TODO: Implement FrameStarted callback handling

		return false;
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
		// TODO: Implement FrameAvailable callback handling

		return false;
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
		// TODO: Implement FrameLowLevel callback handling

		return false;
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

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}
