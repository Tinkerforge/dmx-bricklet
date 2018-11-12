var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your DMX Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var dmx = new Tinkerforge.BrickletDMX(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Configure Bricklet as DMX master
        dmx.setDMXMode(Tinkerforge.BrickletDMX.DMX_MODE_MASTER);

        // Write DMX frame with 3 channels
        dmx.writeFrame([255, 128, 0]);
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
