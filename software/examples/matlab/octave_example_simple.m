function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your DMX Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    dmx = javaObject("com.tinkerforge.BrickletDMX", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Configure Bricklet as DMX master
    dmx.setDMXMode(dmx.DMX_MODE_MASTER);

    % Write DMX frame with 3 channels
    dmx.writeFrame([255 128 0]);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
