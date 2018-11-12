Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your DMX Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim dmx As New BrickletDMX(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Configure Bricklet as DMX master
        dmx.SetDMXMode(BrickletDMX.DMX_MODE_MASTER)

        ' Write DMX frame with 3 channels
        dmx.WriteFrame(new Byte(){255, 128, 0})

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
