import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletDMX;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your DMX Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDMX dmx = new BrickletDMX(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Configure Bricklet as DMX master
		dmx.setDMXMode(BrickletDMX.DMX_MODE_MASTER);

		// Write DMX frame with 3 channels
		dmx.writeFrame(new int[]{255, 128, 0});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
