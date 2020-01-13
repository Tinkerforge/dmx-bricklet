#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your DMX Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_dmx import BrickletDMX

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dmx = BrickletDMX(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Configure Bricklet as DMX master
    dmx.set_dmx_mode(dmx.DMX_MODE_MASTER)

    # Write DMX frame with 3 channels
    dmx.write_frame([255, 128, 0])

    input("Press key to exit\n") # Use raw_input() in Python 2
    ipcon.disconnect()
