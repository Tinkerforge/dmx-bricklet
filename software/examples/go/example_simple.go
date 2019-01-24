package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/dmx_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your DMX Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	dmx, _ := dmx_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Configure Bricklet as DMX master
	dmx.SetDMXMode(dmx_bricklet.DMXModeMaster)

	// Write DMX frame with 3 channels
	dmx.WriteFrame([]uint8{255, 128, 0})

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
