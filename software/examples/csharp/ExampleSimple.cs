using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your DMX Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDMX dmx = new BrickletDMX(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure Bricklet as DMX master
		dmx.SetDMXMode(BrickletDMX.DMX_MODE_MASTER);

		// Write DMX frame with 3 channels
		dmx.WriteFrame(new byte[]{255, 128, 0});

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
