EESchema Schematic File Version 2
LIBS:tinkerforge
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "DMX Bricklet"
Date "2017-05-05"
Rev "1.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2017, L.Lauer <lukas@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 550  7700 0    40   ~ 0
Copyright Tinkerforge GmbH 2017.\nThis documentation describes Open Hardware and is licensed under the\nCERN OHL v. 1.1.\nYou may redistribute and modify this documentation under the terms of the\nCERN OHL v.1.1. (http://ohwr.org/cernohl). This documentation is distributed\nWITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF\nMERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A\nPARTICULAR PURPOSE. Please see the CERN OHL v.1.1 for applicable\nconditions\n
$Comp
L DRILL U2
U 1 1 4C6050A5
P 10650 6150
F 0 "U2" H 10700 6200 60  0001 C CNN
F 1 "DRILL" H 10650 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6150 60  0001 C CNN
F 3 "" H 10650 6150 60  0001 C CNN
	1    10650 6150
	1    0    0    -1  
$EndComp
$Comp
L DRILL U3
U 1 1 4C6050A2
P 10650 6350
F 0 "U3" H 10700 6400 60  0001 C CNN
F 1 "DRILL" H 10650 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6350 60  0001 C CNN
F 3 "" H 10650 6350 60  0001 C CNN
	1    10650 6350
	1    0    0    -1  
$EndComp
$Comp
L DRILL U5
U 1 1 4C60509F
P 11000 6350
F 0 "U5" H 11050 6400 60  0001 C CNN
F 1 "DRILL" H 11000 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6350 60  0001 C CNN
F 3 "" H 11000 6350 60  0001 C CNN
	1    11000 6350
	1    0    0    -1  
$EndComp
$Comp
L DRILL U4
U 1 1 4C605099
P 11000 6150
F 0 "U4" H 11050 6200 60  0001 C CNN
F 1 "DRILL" H 11000 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6150 60  0001 C CNN
F 3 "" H 11000 6150 60  0001 C CNN
	1    11000 6150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 4C5FCFB4
P 2550 1150
F 0 "#PWR01" H 2550 1250 30  0001 C CNN
F 1 "VCC" H 2550 1250 30  0000 C CNN
F 2 "" H 2550 1150 60  0001 C CNN
F 3 "" H 2550 1150 60  0001 C CNN
	1    2550 1150
	1    0    0    -1  
$EndComp
$Comp
L CON-SENSOR2 P1
U 1 1 4C5FCF27
P 1000 2000
F 0 "P1" H 1150 2400 60  0000 C CNN
F 1 "CON-SENSOR2" V 1150 2000 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 1000 2000 60  0001 C CNN
F 3 "" H 1000 2000 60  0001 C CNN
	1    1000 2000
	-1   0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54F76B96
P 1600 1400
F 0 "C1" V 1700 1550 50  0000 L CNN
F 1 "1uF" V 1450 1400 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1600 1400 60  0001 C CNN
F 3 "" H 1600 1400 60  0001 C CNN
	1    1600 1400
	-1   0    0    1   
$EndComp
$Comp
L C C2
U 1 1 54F77AA5
P 2350 1400
F 0 "C2" V 2450 1550 50  0000 L CNN
F 1 "1uF" V 2200 1400 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2350 1400 60  0001 C CNN
F 3 "" H 2350 1400 60  0001 C CNN
	1    2350 1400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR02
U 1 1 54F77AEA
P 2350 1850
F 0 "#PWR02" H 2350 1850 30  0001 C CNN
F 1 "GND" H 2350 1780 30  0001 C CNN
F 2 "" H 2350 1850 60  0001 C CNN
F 3 "" H 2350 1850 60  0001 C CNN
	1    2350 1850
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX48 U1
U 2 1 5820E01A
P 4350 4550
F 0 "U1" H 4200 5500 60  0000 C CNN
F 1 "XMC1XXX48" H 4350 3550 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 4500 5300 60  0001 C CNN
F 3 "" H 4500 5300 60  0000 C CNN
	2    4350 4550
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX48 U1
U 1 1 5820E0F1
P 4350 2400
F 0 "U1" H 4200 3350 60  0000 C CNN
F 1 "XMC1XXX48" H 4350 1400 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 4500 3150 60  0001 C CNN
F 3 "" H 4500 3150 60  0000 C CNN
	1    4350 2400
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX48 U1
U 4 1 5820E19E
P 6150 6050
F 0 "U1" H 6000 6700 60  0000 C CNN
F 1 "XMC1XXX48" H 6150 5050 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 6300 6800 60  0001 C CNN
F 3 "" H 6300 6800 60  0000 C CNN
	4    6150 6050
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX48 U1
U 3 1 5820E1ED
P 6150 4750
F 0 "U1" H 6050 5250 60  0000 C CNN
F 1 "XMC1XXX48" H 6150 4250 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 6300 5500 60  0001 C CNN
F 3 "" H 6300 5500 60  0000 C CNN
	3    6150 4750
	1    0    0    -1  
$EndComp
$Comp
L XMC1XXX48 U1
U 5 1 5820E256
P 4400 6250
F 0 "U1" H 4250 6700 60  0000 C CNN
F 1 "XMC1XXX48" H 4400 5650 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 4550 7000 60  0001 C CNN
F 3 "" H 4550 7000 60  0000 C CNN
	5    4400 6250
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5820F9DC
P 3550 2000
F 0 "C3" V 3600 1750 50  0000 L CNN
F 1 "100nF" V 3400 1900 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3550 2000 60  0001 C CNN
F 3 "" H 3550 2000 60  0001 C CNN
	1    3550 2000
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5820FDE6
P 3900 2000
F 0 "C5" V 3950 1750 50  0000 L CNN
F 1 "100nF" V 3750 1900 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3900 2000 60  0001 C CNN
F 3 "" H 3900 2000 60  0001 C CNN
	1    3900 2000
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5821039E
P 3900 2950
F 0 "C6" V 3950 2700 50  0000 L CNN
F 1 "220nF" V 3750 2850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3900 2950 60  0001 C CNN
F 3 "" H 3900 2950 60  0001 C CNN
	1    3900 2950
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 582104B4
P 3550 2950
F 0 "C4" V 3600 2700 50  0000 L CNN
F 1 "100nF" V 3400 2850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3550 2950 60  0001 C CNN
F 3 "" H 3550 2950 60  0001 C CNN
	1    3550 2950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 5821096B
P 3550 1600
F 0 "#PWR03" H 3550 1700 30  0001 C CNN
F 1 "VCC" H 3550 1700 30  0000 C CNN
F 2 "" H 3550 1600 60  0001 C CNN
F 3 "" H 3550 1600 60  0001 C CNN
	1    3550 1600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 58210A4E
P 3550 2550
F 0 "#PWR04" H 3550 2650 30  0001 C CNN
F 1 "VCC" H 3550 2650 30  0000 C CNN
F 2 "" H 3550 2550 60  0001 C CNN
F 3 "" H 3550 2550 60  0001 C CNN
	1    3550 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 58210B67
P 3550 2300
F 0 "#PWR05" H 3550 2300 30  0001 C CNN
F 1 "GND" H 3550 2230 30  0001 C CNN
F 2 "" H 3550 2300 60  0001 C CNN
F 3 "" H 3550 2300 60  0001 C CNN
	1    3550 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 58210C80
P 3550 3250
F 0 "#PWR06" H 3550 3250 30  0001 C CNN
F 1 "GND" H 3550 3180 30  0001 C CNN
F 2 "" H 3550 3250 60  0001 C CNN
F 3 "" H 3550 3250 60  0001 C CNN
	1    3550 3250
	1    0    0    -1  
$EndComp
Text GLabel 2150 2000 2    60   Output ~ 0
S-CS
Text GLabel 2150 2100 2    60   Output ~ 0
S-CLK
Text GLabel 2150 2200 2    60   Output ~ 0
S-MOSI
Text GLabel 2150 2300 2    60   Input ~ 0
S-MISO
Text GLabel 5450 4550 0    60   Input ~ 0
S-CS
Text GLabel 5450 4750 0    60   Input ~ 0
S-CLK
Text GLabel 5450 4650 0    60   Input ~ 0
S-MOSI
Text GLabel 5450 5050 0    60   Output ~ 0
S-MISO
$Comp
L LED D1
U 1 1 582331F0
P 2850 5800
F 0 "D1" H 2850 5900 50  0000 C CNN
F 1 "yellow" H 2850 5700 50  0000 C CNN
F 2 "kicad-libraries:D0603F" H 2850 5800 50  0001 C CNN
F 3 "" H 2850 5800 50  0000 C CNN
	1    2850 5800
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 58233423
P 2850 6100
F 0 "D2" H 2850 6200 50  0000 C CNN
F 1 "red" H 2850 6000 50  0000 C CNN
F 2 "kicad-libraries:D0603F" H 2850 6100 50  0001 C CNN
F 3 "" H 2850 6100 50  0000 C CNN
	1    2850 6100
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 5823347E
P 2850 6400
F 0 "D3" H 2850 6500 50  0000 C CNN
F 1 "blue" H 2850 6300 50  0000 C CNN
F 2 "kicad-libraries:D0603F" H 2850 6400 50  0001 C CNN
F 3 "" H 2850 6400 50  0000 C CNN
	1    2850 6400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 58233528
P 3550 6600
F 0 "P2" H 3550 6750 50  0000 C CNN
F 1 "BOOT" V 3650 6600 50  0000 C CNN
F 2 "kicad-libraries:SolderJumper" H 3550 6500 50  0001 C CNN
F 3 "" H 3550 6500 50  0000 C CNN
	1    3550 6600
	-1   0    0    1   
$EndComp
$Comp
L R_PACK4 RP1
U 1 1 582335FC
P 3400 6300
F 0 "RP1" H 3400 6750 50  0000 C CNN
F 1 "1k" H 3400 6250 50  0000 C CNN
F 2 "kicad-libraries:0603X4" H 3400 6300 50  0001 C CNN
F 3 "" H 3400 6300 50  0000 C CNN
	1    3400 6300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 5824794E
P 2500 5700
F 0 "#PWR07" H 2500 5800 30  0001 C CNN
F 1 "VCC" H 2500 5800 30  0000 C CNN
F 2 "" H 2500 5700 60  0001 C CNN
F 3 "" H 2500 5700 60  0001 C CNN
	1    2500 5700
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 58249AB1
P 7450 3000
F 0 "C7" V 7300 2950 50  0000 L CNN
F 1 "100nF" V 7600 2900 50  0000 L CNN
F 2 "kicad-libraries:C0603E" H 7450 3000 60  0001 C CNN
F 3 "" H 7450 3000 60  0001 C CNN
	1    7450 3000
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 58249E96
P 7900 1800
F 0 "R3" V 7980 1800 50  0000 C CNN
F 1 "10k" V 7900 1800 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 7900 1800 60  0001 C CNN
F 3 "" H 7900 1800 60  0000 C CNN
	1    7900 1800
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5824A0C5
P 7900 2350
F 0 "R4" V 7980 2350 50  0000 C CNN
F 1 "2.2k" V 7900 2350 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 7900 2350 60  0001 C CNN
F 3 "" H 7900 2350 60  0000 C CNN
	1    7900 2350
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5824A182
P 7900 2850
F 0 "R5" V 8000 2850 50  0000 C CNN
F 1 "10k" V 7900 2850 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 7900 2850 60  0001 C CNN
F 3 "" H 7900 2850 60  0000 C CNN
	1    7900 2850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 5824AA12
P 7450 2150
F 0 "#PWR08" H 7450 2250 30  0001 C CNN
F 1 "VCC" H 7450 2250 30  0000 C CNN
F 2 "" H 7450 2150 60  0001 C CNN
F 3 "" H 7450 2150 60  0001 C CNN
	1    7450 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5824B097
P 7450 3300
F 0 "#PWR09" H 7450 3300 30  0001 C CNN
F 1 "GND" H 7450 3230 30  0001 C CNN
F 2 "" H 7450 3300 60  0001 C CNN
F 3 "" H 7450 3300 60  0001 C CNN
	1    7450 3300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 5824B66D
P 7900 1500
F 0 "#PWR010" H 7900 1600 30  0001 C CNN
F 1 "VCC" H 7900 1600 30  0000 C CNN
F 2 "" H 7900 1500 60  0001 C CNN
F 3 "" H 7900 1500 60  0001 C CNN
	1    7900 1500
	1    0    0    -1  
$EndComp
$Comp
L TVS D5
U 1 1 5824DDEB
P 9050 2300
F 0 "D5" H 9000 2400 40  0000 C CNN
F 1 "SMAJ24CA" H 9050 2200 40  0000 C CNN
F 2 "kicad-libraries:DO-214AC" H 9050 2300 60  0001 C CNN
F 3 "" H 9050 2300 60  0000 C CNN
	1    9050 2300
	0    1    1    0   
$EndComp
$Comp
L TVS D4
U 1 1 5824E8CD
P 8850 2900
F 0 "D4" H 8800 3000 40  0000 C CNN
F 1 "SMAJ24CA" H 8850 2800 40  0000 C CNN
F 2 "kicad-libraries:DO-214AC" H 8850 2900 60  0001 C CNN
F 3 "" H 8850 2900 60  0000 C CNN
	1    8850 2900
	0    1    1    0   
$EndComp
$Comp
L R_PACK4 RP2
U 1 1 5825121A
P 5850 2750
F 0 "RP2" H 5850 3200 50  0000 C CNN
F 1 "10k" H 5850 2700 50  0000 C CNN
F 2 "kicad-libraries:0603X4" H 5850 2750 50  0001 C CNN
F 3 "" H 5850 2750 50  0000 C CNN
	1    5850 2750
	1    0    0    -1  
$EndComp
Text GLabel 5450 2400 0    60   Output ~ 0
485-RX
Text GLabel 5450 2500 0    60   Input ~ 0
485-~RE
Text GLabel 5450 2600 0    60   Input ~ 0
485-DE
Text GLabel 5450 2700 0    60   Input ~ 0
485-TX
Text Notes 5100 4050 0    39   ~ 0
SPI Slave\nP1.1 : USIC0_CH1-DX2E : SEL\nP1.2 : USIC0_CH1-DX0B : MOSI\nP1.3 : USIC0_CH1-DX1A : CLK\nP1.6 : USIC0_CH1-DOUT0 : MISO
Text Notes 5300 7250 0    39   ~ 0
ASC\nP2.12 : USIC1_CH1.DOUT0\nP3.0 : USIC1_CH1.DX0E
Text GLabel 3750 5700 0    60   Input ~ 0
485-RX
Text GLabel 5650 6650 0    60   Output ~ 0
485-~RE
Text GLabel 5650 6550 0    60   Output ~ 0
485-DE
Text GLabel 5650 6750 0    60   Output ~ 0
485-TX
$Comp
L C C8
U 1 1 58274693
P 2550 4550
F 0 "C8" V 2400 4500 50  0000 L CNN
F 1 "10pF" V 2700 4500 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2550 4550 60  0001 C CNN
F 3 "" H 2550 4550 60  0001 C CNN
	1    2550 4550
	0    1    1    0   
$EndComp
$Comp
L C C9
U 1 1 582748D4
P 2550 5150
F 0 "C9" V 2400 5100 50  0000 L CNN
F 1 "10pF" V 2700 5100 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 2550 5150 60  0001 C CNN
F 3 "" H 2550 5150 60  0001 C CNN
	1    2550 5150
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 58275257
P 2350 5300
F 0 "#PWR011" H 2350 5300 30  0001 C CNN
F 1 "GND" H 2350 5230 30  0001 C CNN
F 2 "" H 2350 5300 60  0001 C CNN
F 3 "" H 2350 5300 60  0001 C CNN
	1    2350 5300
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 58275F18
P 3550 4900
F 0 "R9" V 3630 4900 50  0000 C CNN
F 1 "0" V 3550 4900 50  0000 C CNN
F 2 "kicad-libraries:R0402F" H 3550 4900 60  0001 C CNN
F 3 "" H 3550 4900 60  0000 C CNN
	1    3550 4900
	0    1    1    0   
$EndComp
$Comp
L CRYSTAL_3225 X1
U 1 1 58276FBA
P 3100 4850
F 0 "X1" V 2850 4650 60  0000 C CNN
F 1 "16MHz" V 3550 4850 60  0000 C CNN
F 2 "kicad-libraries:CRYSTAL_3225" H 3100 4850 60  0001 C CNN
F 3 "" H 3100 4850 60  0000 C CNN
	1    3100 4850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR012
U 1 1 5827815F
P 2350 4700
F 0 "#PWR012" H 2350 4700 30  0001 C CNN
F 1 "GND" H 2350 4630 30  0001 C CNN
F 2 "" H 2350 4700 60  0001 C CNN
F 3 "" H 2350 4700 60  0001 C CNN
	1    2350 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 58278535
P 3400 5100
F 0 "#PWR013" H 3400 5100 30  0001 C CNN
F 1 "GND" H 3400 5030 30  0001 C CNN
F 2 "" H 3400 5100 60  0001 C CNN
F 3 "" H 3400 5100 60  0001 C CNN
	1    3400 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5828358D
P 3850 6650
F 0 "#PWR014" H 3850 6650 30  0001 C CNN
F 1 "GND" H 3850 6580 30  0001 C CNN
F 2 "" H 3850 6650 60  0001 C CNN
F 3 "" H 3850 6650 60  0001 C CNN
	1    3850 6650
	0    -1   -1   0   
$EndComp
NoConn ~ 4050 6650
NoConn ~ 5800 6450
NoConn ~ 5800 6350
NoConn ~ 5800 6250
NoConn ~ 5800 6150
NoConn ~ 5800 6050
NoConn ~ 5800 5950
NoConn ~ 5800 5850
NoConn ~ 5800 5750
NoConn ~ 5800 5650
NoConn ~ 5800 5550
NoConn ~ 5800 4950
NoConn ~ 5800 4850
NoConn ~ 5800 4450
NoConn ~ 4000 3800
NoConn ~ 4000 3900
NoConn ~ 4000 4000
NoConn ~ 4000 4100
NoConn ~ 4000 4200
NoConn ~ 4000 4300
NoConn ~ 4000 4400
NoConn ~ 4000 4500
NoConn ~ 4000 4600
NoConn ~ 4000 4700
NoConn ~ 4000 5000
NoConn ~ 4000 5100
NoConn ~ 4000 5200
NoConn ~ 3600 5950
NoConn ~ 3200 5950
Text Notes 2750 4200 0    39   ~ 0
TSX-3225 16.0000MF18X-AC0\nno C - 1,00017\n3pF - 1,00008\n4.7pF - 1,00005\n9pF - 1,00001\n10pF - 1,00000MHz
NoConn ~ 1350 1700
$Comp
L ADM3485 U6
U 1 1 58A492B5
P 7000 2550
F 0 "U6" H 6850 2800 60  0000 C CNN
F 1 "ADM3485" H 7000 2300 60  0000 C CNN
F 2 "kicad-libraries:SOIC8" H 7000 2550 60  0001 C CNN
F 3 "" H 7000 2550 60  0000 C CNN
	1    7000 2550
	1    0    0    -1  
$EndComp
$Comp
L WE-SL L1
U 1 1 58A4963B
P 8400 2050
F 0 "L1" H 8200 2260 40  0000 C CNN
F 1 "WE-SL" H 8400 1950 40  0000 C CNN
F 2 "kicad-libraries:WE-SL" H 8400 2050 60  0001 C CNN
F 3 "" H 8400 2050 60  0000 C CNN
	1    8400 2050
	1    0    0    -1  
$EndComp
$Comp
L WE-SL L1
U 2 1 58A4982A
P 8400 2600
F 0 "L1" H 8200 2810 40  0000 C CNN
F 1 "WE-SL" H 8400 2500 40  0000 C CNN
F 2 "kicad-libraries:WE-SL" H 8400 2600 60  0001 C CNN
F 3 "" H 8400 2600 60  0000 C CNN
	2    8400 2600
	1    0    0    -1  
$EndComp
$Comp
L WE-SL L1
U 3 1 58A498B5
P 8400 3150
F 0 "L1" H 8200 3360 40  0000 C CNN
F 1 "WE-SL" H 8400 3050 40  0000 C CNN
F 2 "kicad-libraries:WE-SL" H 8400 3150 60  0001 C CNN
F 3 "" H 8400 3150 60  0000 C CNN
	3    8400 3150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58A5CC97
P 9950 2100
F 0 "R1" V 10030 2100 50  0000 C CNN
F 1 "120" V 9950 2100 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 9950 2100 60  0001 C CNN
F 3 "" H 9950 2100 60  0000 C CNN
	1    9950 2100
	1    0    0    -1  
$EndComp
$Comp
L SS-2P2T-08 SW1
U 1 1 58A5C876
P 10300 1700
F 0 "SW1" H 10300 1900 60  0000 C CNN
F 1 "TER" H 10300 1500 60  0000 C CNN
F 2 "kicad-libraries:SLIDE_SWITCH" H 10300 1700 60  0001 C CNN
F 3 "" H 10300 1700 60  0000 C CNN
	1    10300 1700
	1    0    0    -1  
$EndComp
NoConn ~ 10050 1800
NoConn ~ 10550 1800
NoConn ~ 10550 1700
NoConn ~ 10550 1600
Text Notes 9900 1400 0    39   ~ 0
Bus termination if last slave
$Comp
L DMXCON_2x3 P3
U 1 1 58A479A2
P 10850 2700
F 0 "P3" H 10676 3080 39  0000 C CNN
F 1 "DMXCON_2x3" V 11096 2700 39  0000 C CNN
F 2 "kicad-libraries:DMX_IN_OUT_2x3POL" H 10846 2850 39  0001 C CNN
F 3 "" H 10846 2850 39  0000 C CNN
	1    10850 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 58A6D55E
P 7350 2750
F 0 "#PWR015" H 7350 2750 30  0001 C CNN
F 1 "GND" H 7350 2680 30  0001 C CNN
F 2 "" H 7350 2750 60  0001 C CNN
F 3 "" H 7350 2750 60  0001 C CNN
	1    7350 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 58A71B64
P 7900 3300
F 0 "#PWR016" H 7900 3300 30  0001 C CNN
F 1 "GND" H 7900 3230 30  0001 C CNN
F 2 "" H 7900 3300 60  0001 C CNN
F 3 "" H 7900 3300 60  0001 C CNN
	1    7900 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 58A71BE4
P 8050 3300
F 0 "#PWR017" H 8050 3300 30  0001 C CNN
F 1 "GND" H 8050 3230 30  0001 C CNN
F 2 "" H 8050 3300 60  0001 C CNN
F 3 "" H 8050 3300 60  0001 C CNN
	1    8050 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2450 1000 2900
Wire Wire Line
	2350 1800 1350 1800
Wire Wire Line
	1450 1900 1450 1150
Wire Wire Line
	2350 1600 2350 1850
Wire Wire Line
	1600 1800 1600 1600
Connection ~ 1600 1800
Wire Wire Line
	4000 2250 3550 2250
Wire Wire Line
	3550 2200 3550 2300
Wire Wire Line
	4000 1650 3550 1650
Wire Wire Line
	3550 1600 3550 1800
Wire Wire Line
	3900 2200 3900 2350
Connection ~ 3900 2250
Wire Wire Line
	3550 1750 4000 1750
Wire Wire Line
	3900 1750 3900 1800
Connection ~ 3550 1750
Connection ~ 3900 1750
Wire Wire Line
	3900 2350 4000 2350
Wire Wire Line
	3550 3200 4000 3200
Wire Wire Line
	3900 3200 3900 3150
Wire Wire Line
	3550 2700 4000 2700
Wire Wire Line
	3900 2700 3900 2750
Wire Wire Line
	3550 3150 3550 3250
Connection ~ 3900 3200
Wire Wire Line
	4000 2600 3550 2600
Wire Wire Line
	3550 2550 3550 2750
Connection ~ 3550 2700
Connection ~ 3900 2700
Connection ~ 3550 3200
Connection ~ 3550 2250
Connection ~ 3550 2600
Connection ~ 3550 1650
Connection ~ 2350 1800
Wire Wire Line
	1350 2000 1550 2000
Wire Wire Line
	1350 2100 1550 2100
Wire Wire Line
	1350 2200 1550 2200
Wire Wire Line
	1350 2300 1550 2300
Wire Wire Line
	1950 2300 2150 2300
Wire Wire Line
	1950 2200 2150 2200
Wire Wire Line
	1950 2100 2150 2100
Wire Wire Line
	1950 2000 2150 2000
Wire Wire Line
	5450 2400 5650 2400
Wire Wire Line
	5650 2500 5450 2500
Wire Wire Line
	5450 2600 5650 2600
Wire Wire Line
	5650 2700 5450 2700
Wire Wire Line
	3300 5150 3300 4900
Wire Wire Line
	3300 4800 4000 4800
Wire Wire Line
	3300 4550 3300 4800
Wire Wire Line
	4000 4900 3800 4900
Wire Wire Line
	2750 4550 3300 4550
Wire Wire Line
	2750 5150 3300 5150
Connection ~ 3100 5150
Connection ~ 3100 4550
Wire Wire Line
	2350 5300 2350 5150
Wire Wire Line
	2350 4700 2350 4550
Wire Wire Line
	3400 5100 3400 5000
Wire Wire Line
	5650 6750 5800 6750
Wire Wire Line
	5450 4550 5800 4550
Wire Wire Line
	5450 4650 5800 4650
Wire Wire Line
	5450 4750 5800 4750
Wire Wire Line
	5450 5050 5800 5050
Wire Wire Line
	5650 6550 5800 6550
Wire Wire Line
	5800 6650 5650 6650
Wire Wire Line
	3050 6400 3050 6250
Wire Wire Line
	3050 6250 3200 6250
Wire Wire Line
	3900 6350 4050 6350
Wire Wire Line
	3600 6250 3800 6250
Wire Wire Line
	3800 6250 3800 6450
Wire Wire Line
	3800 6450 4050 6450
Wire Wire Line
	2500 5700 2500 6400
Wire Wire Line
	2500 5800 2650 5800
Wire Wire Line
	2500 6100 2650 6100
Connection ~ 2500 5800
Wire Wire Line
	2500 6400 2650 6400
Connection ~ 2500 6100
Wire Wire Line
	4000 5300 3900 5300
Wire Wire Line
	3900 5300 3900 6050
Wire Wire Line
	3200 6150 3150 6150
Wire Wire Line
	3150 6150 3150 6100
Wire Wire Line
	3150 6100 3050 6100
Wire Wire Line
	3600 6150 3900 6150
Wire Wire Line
	3900 6150 3900 6350
Wire Wire Line
	3750 6650 3850 6650
Wire Wire Line
	4050 6550 3750 6550
Wire Wire Line
	3200 6050 3200 6000
Wire Wire Line
	3200 6000 3100 6000
Wire Wire Line
	3100 6000 3100 5800
Wire Wire Line
	3100 5800 3050 5800
Wire Wire Line
	3900 6050 3600 6050
Wire Wire Line
	1350 1900 1450 1900
Wire Wire Line
	7350 2600 8050 2600
Wire Wire Line
	7750 2500 7350 2500
Wire Wire Line
	7750 2050 7750 2500
Wire Wire Line
	8750 2600 10450 2600
Wire Wire Line
	9650 2050 9650 2500
Wire Wire Line
	9650 2500 10450 2500
Wire Wire Line
	10450 2400 10350 2400
Wire Wire Line
	10450 2800 10350 2800
Connection ~ 10350 2800
Wire Wire Line
	10250 2500 10250 2900
Wire Wire Line
	10250 2900 10450 2900
Connection ~ 10250 2500
Wire Wire Line
	10150 2600 10150 3000
Wire Wire Line
	10150 3000 10450 3000
Connection ~ 10150 2600
Wire Wire Line
	7450 2150 7450 2800
Wire Wire Line
	7450 2400 7350 2400
Connection ~ 7450 2400
Wire Wire Line
	7450 3200 7450 3300
Wire Wire Line
	9950 1850 9950 1700
Wire Wire Line
	9950 1700 10050 1700
Wire Wire Line
	10050 1600 9800 1600
Wire Wire Line
	9800 1600 9800 2600
Connection ~ 9800 2600
Wire Wire Line
	9950 2350 9950 2500
Connection ~ 9950 2500
Wire Wire Line
	7750 2050 8050 2050
Wire Wire Line
	8750 2050 9650 2050
Connection ~ 9050 2050
Wire Wire Line
	9050 3150 9050 2550
Wire Wire Line
	6050 2400 6650 2400
Wire Wire Line
	6050 2500 6650 2500
Wire Wire Line
	6050 2600 6650 2600
Wire Wire Line
	6050 2700 6650 2700
Wire Wire Line
	7350 2700 7350 2750
Wire Wire Line
	10350 2150 10350 3150
Wire Wire Line
	7900 1500 7900 1550
Wire Wire Line
	7900 2100 7900 2050
Connection ~ 7900 2050
Connection ~ 7900 2600
Wire Wire Line
	7900 3100 7900 3300
Wire Wire Line
	8050 3150 8050 3300
Wire Wire Line
	10350 3150 8750 3150
Connection ~ 8850 3150
Wire Wire Line
	8850 2650 8850 2600
Connection ~ 8850 2600
Connection ~ 9050 3150
$Comp
L R_PACK4 RP4
U 1 1 590C8267
P 1750 2350
F 0 "RP4" H 1750 2800 50  0000 C CNN
F 1 "82" H 1750 2300 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 1750 2350 50  0001 C CNN
F 3 "" H 1750 2350 50  0000 C CNN
	1    1750 2350
	-1   0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 590C8A49
P 1450 2650
F 0 "C10" H 1500 2750 50  0000 L CNN
F 1 "220pF" H 1500 2550 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 1450 2650 60  0001 C CNN
F 3 "" H 1450 2650 60  0000 C CNN
	1    1450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2450 1450 2300
Connection ~ 1450 2300
$Comp
L GND #PWR018
U 1 1 590C9041
P 1450 2900
F 0 "#PWR018" H 1450 2900 30  0001 C CNN
F 1 "GND" H 1450 2830 30  0001 C CNN
F 2 "" H 1450 2900 60  0001 C CNN
F 3 "" H 1450 2900 60  0001 C CNN
	1    1450 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 590C90C1
P 1000 2900
F 0 "#PWR019" H 1000 2900 30  0001 C CNN
F 1 "GND" H 1000 2830 30  0001 C CNN
F 2 "" H 1000 2900 60  0001 C CNN
F 3 "" H 1000 2900 60  0001 C CNN
	1    1000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2850 1450 2900
Wire Wire Line
	1450 1150 2550 1150
Wire Wire Line
	2350 1200 2350 1150
Connection ~ 2350 1150
Wire Wire Line
	1600 1200 1600 1150
Connection ~ 1600 1150
Wire Wire Line
	4050 5950 3800 5950
Wire Wire Line
	3800 5950 3800 5700
Wire Wire Line
	3800 5700 3750 5700
NoConn ~ 5800 6850
$Comp
L R R2
U 1 1 598D6E06
P 10750 2150
F 0 "R2" V 10830 2150 50  0000 C CNN
F 1 "DNP" V 10750 2150 50  0000 C CNN
F 2 "kicad-libraries:R1206" H 10750 2150 60  0001 C CNN
F 3 "" H 10750 2150 60  0000 C CNN
	1    10750 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	11000 3150 11150 3150
Wire Wire Line
	11150 3150 11150 2150
Wire Wire Line
	11150 2150 11000 2150
Connection ~ 11000 2150
Wire Wire Line
	11000 2150 11000 2250
Wire Wire Line
	10500 2150 10350 2150
Connection ~ 10350 2400
$EndSCHEMATC
