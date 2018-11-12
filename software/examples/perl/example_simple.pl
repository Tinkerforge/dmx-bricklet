#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletDMX;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your DMX Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $dmx = Tinkerforge::BrickletDMX->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Configure Bricklet as DMX master
$dmx->set_dmx_mode($dmx->DMX_MODE_MASTER);

# Write DMX frame with 3 channels
$dmx->write_frame([255, 128, 0]);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
