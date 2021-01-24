EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F4:STM32F411RETx U?
U 1 1 60147752
P 3200 4650
AR Path="/60147752" Ref="U?"  Part="1" 
AR Path="/6011C2E8/60147752" Ref="U2"  Part="1" 
F 0 "U2" H 3200 4650 50  0000 C CNN
F 1 "STM32F411RETx" H 3200 4450 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 2600 2950 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00115249.pdf" H 3200 4650 50  0001 C CNN
	1    3200 4650
	1    0    0    -1  
$EndComp
Text GLabel 2500 4250 0    50   Input ~ 0
OSC_IN
Text GLabel 2500 4350 0    50   Input ~ 0
OSC_OUT
Text GLabel 2500 3150 0    50   Input ~ 0
~RESET
Text GLabel 2500 3550 0    50   Input ~ 0
30
$Comp
L power:+3.3VA #PWR?
U 1 1 6014775C
P 3500 2900
AR Path="/6014775C" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/6014775C" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 3500 2750 50  0001 C CNN
F 1 "+3.3VA" H 3515 3073 50  0000 C CNN
F 2 "" H 3500 2900 50  0001 C CNN
F 3 "" H 3500 2900 50  0001 C CNN
	1    3500 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60147762
P 3200 2900
AR Path="/60147762" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/60147762" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 3200 2750 50  0001 C CNN
F 1 "+3.3V" H 3215 3073 50  0000 C CNN
F 2 "" H 3200 2900 50  0001 C CNN
F 3 "" H 3200 2900 50  0001 C CNN
	1    3200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2900 3200 2950
Wire Wire Line
	3200 2950 3300 2950
Connection ~ 3200 2950
Connection ~ 3300 2950
Wire Wire Line
	3300 2950 3400 2950
Wire Wire Line
	3200 2950 3100 2950
Connection ~ 3100 2950
Wire Wire Line
	3100 2950 3000 2950
Wire Wire Line
	3500 2950 3500 2900
Text GLabel 3950 4450 2    50   Input ~ 0
SWDIO
Text GLabel 3950 4550 2    50   Input ~ 0
SWCLK
Wire Wire Line
	3950 4550 3900 4550
Wire Wire Line
	3900 4450 3950 4450
Text GLabel 4000 4850 2    50   Input ~ 0
PB0
Text GLabel 4000 4950 2    50   Input ~ 0
PB1
Text GLabel 4000 5050 2    50   Input ~ 0
PB2
Text GLabel 4000 5150 2    50   Input ~ 0
PB3
Text GLabel 4000 5250 2    50   Input ~ 0
PB4
Text GLabel 4000 5350 2    50   Input ~ 0
PB5
Text GLabel 4000 5450 2    50   Input ~ 0
PB6
Text GLabel 4000 5550 2    50   Input ~ 0
PB7
Text GLabel 4000 5650 2    50   Input ~ 0
PB8
Text GLabel 4000 5750 2    50   Input ~ 0
PB9
Text GLabel 4000 5850 2    50   Input ~ 0
PB10
Text GLabel 4000 5950 2    50   Input ~ 0
PB12
Text GLabel 4000 6050 2    50   Input ~ 0
PB13
Text GLabel 4000 6150 2    50   Input ~ 0
PB14
Text GLabel 4000 6250 2    50   Input ~ 0
PB15
Text GLabel 3200 6550 3    50   Input ~ 0
47
Wire Wire Line
	3200 6550 3200 6450
Text GLabel 3100 6550 3    50   Input ~ 0
31
Wire Wire Line
	3100 6550 3100 6450
$Comp
L power:GND #PWR?
U 1 1 60147788
P 3300 6800
AR Path="/60147788" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/60147788" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 3300 6550 50  0001 C CNN
F 1 "GND" H 3305 6627 50  0000 C CNN
F 2 "" H 3300 6800 50  0001 C CNN
F 3 "" H 3300 6800 50  0001 C CNN
	1    3300 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 6800 3300 6750
Wire Wire Line
	3400 6750 3300 6750
Connection ~ 3300 6750
Wire Wire Line
	3300 6750 3300 6450
Wire Wire Line
	3300 6750 3000 6750
Wire Wire Line
	3000 6750 3000 6450
Wire Wire Line
	3400 6450 3400 6750
Wire Wire Line
	3900 4850 4000 4850
Wire Wire Line
	3900 4950 4000 4950
Wire Wire Line
	3900 5050 4000 5050
Wire Wire Line
	3900 5150 4000 5150
Wire Wire Line
	3900 5250 4000 5250
Wire Wire Line
	3900 5350 4000 5350
Wire Wire Line
	3900 5450 4000 5450
Wire Wire Line
	3900 5550 4000 5550
Wire Wire Line
	3900 5650 4000 5650
Wire Wire Line
	3900 5750 4000 5750
Wire Wire Line
	3900 5850 4000 5850
Wire Wire Line
	3900 5950 4000 5950
Wire Wire Line
	3900 6050 4000 6050
Wire Wire Line
	3900 6150 4000 6150
Wire Wire Line
	3900 6250 4000 6250
Text GLabel 4000 3650 2    50   Input ~ 0
SPI1_SCK
Text GLabel 4000 3750 2    50   Input ~ 0
SPI1_CIPO
Text GLabel 4000 3850 2    50   Input ~ 0
SPI1_COPI
Text GLabel 4000 3550 2    50   Input ~ 0
SPI1_NCS
Wire Wire Line
	4000 3550 3900 3550
Wire Wire Line
	3900 3650 4000 3650
Wire Wire Line
	4000 3750 3900 3750
Wire Wire Line
	3900 3850 4000 3850
Text GLabel 4000 4050 2    50   Input ~ 0
UART1_TX
Text GLabel 4000 4150 2    50   Input ~ 0
UART1_RX
Wire Wire Line
	4000 4050 3900 4050
Wire Wire Line
	3900 4150 4000 4150
Text GLabel 2500 3350 0    50   Input ~ 0
BOOT0
Text GLabel 2400 4750 0    50   Input ~ 0
PC0
Text GLabel 2400 4850 0    50   Input ~ 0
PC1
Text GLabel 2400 4950 0    50   Input ~ 0
PC2
Text GLabel 2400 5050 0    50   Input ~ 0
PC3
Text GLabel 2400 5150 0    50   Input ~ 0
PC4
Text GLabel 2400 5250 0    50   Input ~ 0
PC5
Text GLabel 2400 5350 0    50   Input ~ 0
PC6
Text GLabel 2400 5450 0    50   Input ~ 0
PC7
Text GLabel 2400 5550 0    50   Input ~ 0
PC8
Text GLabel 2400 5750 0    50   Input ~ 0
PC10
Wire Wire Line
	2400 5750 2500 5750
Wire Wire Line
	2400 5550 2500 5550
Wire Wire Line
	2400 5450 2500 5450
Wire Wire Line
	2400 5350 2500 5350
Wire Wire Line
	2400 5250 2500 5250
Wire Wire Line
	2400 5150 2500 5150
Wire Wire Line
	2400 5050 2500 5050
Wire Wire Line
	2400 4950 2500 4950
Wire Wire Line
	2400 4850 2500 4850
Wire Wire Line
	2400 4750 2500 4750
NoConn ~ 2500 6250
NoConn ~ 2500 6150
NoConn ~ 2500 6050
NoConn ~ 2500 5950
NoConn ~ 2500 5850
NoConn ~ 2500 5650
NoConn ~ 2500 4550
NoConn ~ 3900 3950
NoConn ~ 3900 4350
NoConn ~ 3900 4250
NoConn ~ 3900 4650
Text GLabel 2200 1600 0    50   Input ~ 0
BOOT0
$Comp
L Device:R_Small R?
U 1 1 601477D5
P 2300 1600
AR Path="/601477D5" Ref="R?"  Part="1" 
AR Path="/6011C2E8/601477D5" Ref="R2"  Part="1" 
F 0 "R2" V 2496 1600 50  0000 C CNN
F 1 "10k" V 2405 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2300 1600 50  0001 C CNN
F 3 "~" H 2300 1600 50  0001 C CNN
	1    2300 1600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 601477DB
P 2500 1600
AR Path="/601477DB" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/601477DB" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 2500 1350 50  0001 C CNN
F 1 "GND" H 2505 1427 50  0000 C CNN
F 2 "" H 2500 1600 50  0001 C CNN
F 3 "" H 2500 1600 50  0001 C CNN
	1    2500 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1600 2400 1600
$Comp
L Switch:SW_SPST SW?
U 1 1 601477E2
P 2700 2400
AR Path="/601477E2" Ref="SW?"  Part="1" 
AR Path="/6011C2E8/601477E2" Ref="SW1"  Part="1" 
F 0 "SW1" H 2700 2635 50  0000 C CNN
F 1 "RST" H 2700 2544 50  0000 C CNN
F 2 "BVH_Switches:Tac_SMD_6.4mm_Side_SPST_NO" H 2700 2400 50  0001 C CNN
F 3 "~" H 2700 2400 50  0001 C CNN
	1    2700 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 601477E8
P 3000 2400
AR Path="/601477E8" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/601477E8" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 3000 2150 50  0001 C CNN
F 1 "GND" H 3005 2227 50  0000 C CNN
F 2 "" H 3000 2400 50  0001 C CNN
F 3 "" H 3000 2400 50  0001 C CNN
	1    3000 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2400 2900 2400
$Comp
L Device:R_Small R?
U 1 1 601477EF
P 2400 2250
AR Path="/601477EF" Ref="R?"  Part="1" 
AR Path="/6011C2E8/601477EF" Ref="R4"  Part="1" 
F 0 "R4" H 2459 2296 50  0000 L CNN
F 1 "10k" H 2459 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2400 2250 50  0001 C CNN
F 3 "~" H 2400 2250 50  0001 C CNN
	1    2400 2250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 601477F5
P 2400 2100
AR Path="/601477F5" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/601477F5" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 2400 1950 50  0001 C CNN
F 1 "+3.3V" H 2415 2273 50  0000 C CNN
F 2 "" H 2400 2100 50  0001 C CNN
F 3 "" H 2400 2100 50  0001 C CNN
	1    2400 2100
	1    0    0    -1  
$EndComp
Text GLabel 2200 2400 0    50   Input ~ 0
~RESET
Wire Wire Line
	2400 2150 2400 2100
Wire Wire Line
	2200 2400 2400 2400
Wire Wire Line
	2400 2400 2400 2350
Connection ~ 2400 2400
Wire Wire Line
	2400 2400 2500 2400
Text GLabel 4000 1950 0    50   Input ~ 0
OSC_IN
Text GLabel 4000 1550 0    50   Input ~ 0
OSC_OUT
$Comp
L Device:R_Small R?
U 1 1 60157CEB
P 4200 1550
AR Path="/60157CEB" Ref="R?"  Part="1" 
AR Path="/6011C2E8/60157CEB" Ref="R5"  Part="1" 
F 0 "R5" V 4004 1550 50  0000 C CNN
F 1 "0" V 4095 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4200 1550 50  0001 C CNN
F 3 "~" H 4200 1550 50  0001 C CNN
	1    4200 1550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60157CF1
P 5250 1750
AR Path="/60157CF1" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/60157CF1" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 5250 1500 50  0001 C CNN
F 1 "GND" H 5255 1577 50  0000 C CNN
F 2 "" H 5250 1750 50  0001 C CNN
F 3 "" H 5250 1750 50  0001 C CNN
	1    5250 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60157CF7
P 5000 1550
AR Path="/60157CF7" Ref="C?"  Part="1" 
AR Path="/6011C2E8/60157CF7" Ref="C15"  Part="1" 
F 0 "C15" V 4771 1550 50  0000 C CNN
F 1 "12pF" V 4862 1550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5000 1550 50  0001 C CNN
F 3 "~" H 5000 1550 50  0001 C CNN
	1    5000 1550
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60157CFD
P 5000 1950
AR Path="/60157CFD" Ref="C?"  Part="1" 
AR Path="/6011C2E8/60157CFD" Ref="C16"  Part="1" 
F 0 "C16" V 4771 1950 50  0000 C CNN
F 1 "12pF" V 4862 1950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5000 1950 50  0001 C CNN
F 3 "~" H 5000 1950 50  0001 C CNN
	1    5000 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 1950 5100 1700
Wire Wire Line
	5100 1700 5250 1700
Wire Wire Line
	5250 1700 5250 1750
Connection ~ 5100 1700
Wire Wire Line
	5100 1700 5100 1550
Wire Wire Line
	4100 1550 4000 1550
$Comp
L Device:Crystal_GND24 Y?
U 1 1 60157D09
P 4550 1750
AR Path="/60157D09" Ref="Y?"  Part="1" 
AR Path="/6011C2E8/60157D09" Ref="Y1"  Part="1" 
F 0 "Y1" V 4504 1994 50  0000 L CNN
F 1 "8MHz" V 4595 1994 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_5032-4Pin_5.0x3.2mm" H 4550 1750 50  0001 C CNN
F 3 "~" H 4550 1750 50  0001 C CNN
	1    4550 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 1950 4550 1950
Wire Wire Line
	4300 1550 4550 1550
Wire Wire Line
	4550 1900 4550 1950
Connection ~ 4550 1950
Wire Wire Line
	4550 1950 4900 1950
Wire Wire Line
	4550 1600 4550 1550
Connection ~ 4550 1550
Wire Wire Line
	4550 1550 4900 1550
Wire Wire Line
	4350 1750 4350 1850
Wire Wire Line
	4350 1850 4800 1850
Wire Wire Line
	4800 1850 4800 1700
Wire Wire Line
	4800 1700 5100 1700
Wire Wire Line
	4750 1750 4750 1700
Wire Wire Line
	4750 1700 4800 1700
Connection ~ 4800 1700
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J?
U 1 1 60157D1E
P 6300 1750
AR Path="/60157D1E" Ref="J?"  Part="1" 
AR Path="/6011C2E8/60157D1E" Ref="J2"  Part="1" 
F 0 "J2" H 6350 2167 50  0000 C CNN
F 1 "STMDBG" H 6350 2076 50  0000 C CNN
F 2 "BVH_Connectors_Misc:Cortex_Debug_PinSocket_2x05_P1.27mm_Vertical_SMD" H 6300 1750 50  0001 C CNN
F 3 "~" H 6300 1750 50  0001 C CNN
	1    6300 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60157D24
P 5750 1450
AR Path="/60157D24" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/60157D24" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 5750 1300 50  0001 C CNN
F 1 "+3.3V" H 5765 1623 50  0000 C CNN
F 2 "" H 5750 1450 50  0001 C CNN
F 3 "" H 5750 1450 50  0001 C CNN
	1    5750 1450
	1    0    0    -1  
$EndComp
Text GLabel 6750 1550 2    50   Input ~ 0
SWDIO
Text GLabel 6750 1650 2    50   Input ~ 0
SWCLK
Text GLabel 6750 1950 2    50   Input ~ 0
~RESET
$Comp
L power:GND #PWR?
U 1 1 60157D2D
P 5750 1950
AR Path="/60157D2D" Ref="#PWR?"  Part="1" 
AR Path="/6011C2E8/60157D2D" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 5750 1700 50  0001 C CNN
F 1 "GND" H 5755 1777 50  0000 C CNN
F 2 "" H 5750 1950 50  0001 C CNN
F 3 "" H 5750 1950 50  0001 C CNN
	1    5750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1950 6100 1950
Wire Wire Line
	5750 1950 5750 1750
Wire Wire Line
	5750 1750 6100 1750
Connection ~ 5750 1950
Wire Wire Line
	6100 1650 5750 1650
Wire Wire Line
	5750 1650 5750 1750
Connection ~ 5750 1750
Wire Wire Line
	6100 1550 5750 1550
Wire Wire Line
	5750 1550 5750 1450
NoConn ~ 6600 1750
NoConn ~ 6600 1850
NoConn ~ 6100 1850
Wire Wire Line
	6750 1550 6600 1550
Wire Wire Line
	6600 1650 6750 1650
Wire Wire Line
	6750 1950 6600 1950
Text GLabel 4000 3150 2    50   Input ~ 0
STM_PA0
Text GLabel 4000 3250 2    50   Input ~ 0
STM_PA1
Text GLabel 4000 3350 2    50   Input ~ 0
STM_PA2
Text GLabel 4000 3450 2    50   Input ~ 0
STM_PA3
Wire Wire Line
	4000 3450 3900 3450
Wire Wire Line
	3900 3350 4000 3350
Wire Wire Line
	4000 3250 3900 3250
Wire Wire Line
	3900 3150 4000 3150
$EndSCHEMATC
