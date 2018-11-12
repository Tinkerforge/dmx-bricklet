<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDMX.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDMX;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your DMX Bricklet

$ipcon = new IPConnection(); // Create IP connection
$dmx = new BrickletDMX(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Configure Bricklet as DMX master
$dmx->setDMXMode(BrickletDMX::DMX_MODE_MASTER);

// Write DMX frame with 3 channels
$dmx->writeFrame(array(255, 128, 0));

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
