#include "bindings/hal_common.h"
#include "bindings/bricklet_dmx.h"

#define UID "XYZ" // Change XYZ to the UID of your DMX Bricklet

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


static TF_DMX dmx;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_dmx_create(&dmx, UID, hal), "create device object");

	// Configure Bricklet as DMX master
	check(tf_dmx_set_dmx_mode(&dmx, TF_DMX_DMX_MODE_MASTER), "call set_dmx_mode");

	// Write DMX frame with 3 channels
	uint8_t frame[3] = {255, 128, 0};
	check(tf_dmx_write_frame(&dmx, frame, 3), "call write_frame");
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
