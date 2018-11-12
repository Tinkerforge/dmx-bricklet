function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletDMX;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your DMX Bricklet

    ipcon = IPConnection(); % Create IP connection
    dmx = handle(BrickletDMX(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Configure Bricklet as DMX master
    dmx.setDMXMode(BrickletDMX.DMX_MODE_MASTER);

    % Write DMX frame with 3 channels
    dmx.writeFrame([255 128 0]);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
