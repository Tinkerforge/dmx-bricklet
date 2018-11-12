#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_dmx'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your DMX Bricklet

ipcon = IPConnection.new # Create IP connection
dmx = BrickletDMX.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Configure Bricklet as DMX master
dmx.set_dmx_mode BrickletDMX::DMX_MODE_MASTER

# Write DMX frame with 3 channels
dmx.write_frame [255, 128, 0]

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
