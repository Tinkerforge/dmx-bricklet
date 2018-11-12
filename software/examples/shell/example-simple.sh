#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your DMX Bricklet

# Configure Bricklet as DMX master
tinkerforge call dmx-bricklet $uid set-dmx-mode dmx-mode-master

# Write DMX frame with 3 channels
tinkerforge call dmx-bricklet $uid write-frame 255,128,0
