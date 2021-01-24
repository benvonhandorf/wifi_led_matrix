EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L Device:C_Small C6
U 1 1 60111396
P 5950 3100
F 0 "C6" H 6042 3146 50  0000 L CNN
F 1 "0.1uF" H 6042 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5950 3100 50  0001 C CNN
F 3 "~" H 5950 3100 50  0001 C CNN
	1    5950 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 6011139C
P 5250 3100
F 0 "C5" H 5342 3146 50  0000 L CNN
F 1 "4.7uF" H 5342 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5250 3100 50  0001 C CNN
F 3 "~" H 5250 3100 50  0001 C CNN
	1    5250 3100
	1    0    0    -1  
$EndComp
Text GLabel 5250 2950 2    50   Input ~ 0
Vcap
$Comp
L power:GND #PWR0101
U 1 1 601113A3
P 5250 3250
F 0 "#PWR0101" H 5250 3000 50  0001 C CNN
F 1 "GND" H 5255 3077 50  0000 C CNN
F 2 "" H 5250 3250 50  0001 C CNN
F 3 "" H 5250 3250 50  0001 C CNN
	1    5250 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3250 5250 3200
Wire Wire Line
	5250 3000 5250 2950
$Comp
L power:+3.3V #PWR0102
U 1 1 601113AB
P 5950 2950
F 0 "#PWR0102" H 5950 2800 50  0001 C CNN
F 1 "+3.3V" H 5965 3123 50  0000 C CNN
F 2 "" H 5950 2950 50  0001 C CNN
F 3 "" H 5950 2950 50  0001 C CNN
	1    5950 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 601113B1
P 5950 3250
F 0 "#PWR0103" H 5950 3000 50  0001 C CNN
F 1 "GND" H 5955 3077 50  0000 C CNN
F 2 "" H 5950 3250 50  0001 C CNN
F 3 "" H 5950 3250 50  0001 C CNN
	1    5950 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3250 5950 3200
Wire Wire Line
	5950 2950 5950 3000
$Comp
L Device:C_Small C7
U 1 1 601113B9
P 6350 3100
F 0 "C7" H 6442 3146 50  0000 L CNN
F 1 "0.1uF" H 6442 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6350 3100 50  0001 C CNN
F 3 "~" H 6350 3100 50  0001 C CNN
	1    6350 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 601113BF
P 6750 3100
F 0 "C8" H 6842 3146 50  0000 L CNN
F 1 "0.1uF" H 6842 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6750 3100 50  0001 C CNN
F 3 "~" H 6750 3100 50  0001 C CNN
	1    6750 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 601113C5
P 7150 3100
F 0 "C9" H 7242 3146 50  0000 L CNN
F 1 "0.1uF" H 7242 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7150 3100 50  0001 C CNN
F 3 "~" H 7150 3100 50  0001 C CNN
	1    7150 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 601113CB
P 7550 3100
F 0 "C10" H 7642 3146 50  0000 L CNN
F 1 "0.1uF" H 7642 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7550 3100 50  0001 C CNN
F 3 "~" H 7550 3100 50  0001 C CNN
	1    7550 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3000 6350 3000
Connection ~ 5950 3000
Connection ~ 6350 3000
Wire Wire Line
	6350 3000 6750 3000
Connection ~ 6750 3000
Wire Wire Line
	6750 3000 7150 3000
Connection ~ 7150 3000
Wire Wire Line
	7150 3000 7550 3000
Wire Wire Line
	7550 3200 7150 3200
Connection ~ 5950 3200
Connection ~ 6350 3200
Wire Wire Line
	6350 3200 5950 3200
Connection ~ 6750 3200
Wire Wire Line
	6750 3200 6350 3200
Connection ~ 7150 3200
Wire Wire Line
	7150 3200 6750 3200
$Comp
L power:+3.3V #PWR0104
U 1 1 601113E1
P 10000 3000
F 0 "#PWR0104" H 10000 2850 50  0001 C CNN
F 1 "+3.3V" H 10015 3173 50  0000 C CNN
F 2 "" H 10000 3000 50  0001 C CNN
F 3 "" H 10000 3000 50  0001 C CNN
	1    10000 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C14
U 1 1 601113E7
P 10500 3150
F 0 "C14" H 10592 3196 50  0000 L CNN
F 1 "0.1uF" H 10592 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10500 3150 50  0001 C CNN
F 3 "~" H 10500 3150 50  0001 C CNN
	1    10500 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead_Small FB2
U 1 1 601113ED
P 10250 3050
F 0 "FB2" V 10013 3050 50  0000 C CNN
F 1 "100 Ohm" V 10104 3050 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" V 10180 3050 50  0001 C CNN
F 3 "~" H 10250 3050 50  0001 C CNN
	1    10250 3050
	0    1    1    0   
$EndComp
$Comp
L power:+3.3VA #PWR0105
U 1 1 601113F3
P 10800 3000
F 0 "#PWR0105" H 10800 2850 50  0001 C CNN
F 1 "+3.3VA" H 10815 3173 50  0000 C CNN
F 2 "" H 10800 3000 50  0001 C CNN
F 3 "" H 10800 3000 50  0001 C CNN
	1    10800 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 601113F9
P 10500 3300
F 0 "#PWR0106" H 10500 3050 50  0001 C CNN
F 1 "GND" H 10505 3127 50  0000 C CNN
F 2 "" H 10500 3300 50  0001 C CNN
F 3 "" H 10500 3300 50  0001 C CNN
	1    10500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 3300 10500 3250
Wire Wire Line
	10350 3050 10500 3050
Wire Wire Line
	10800 3050 10800 3000
Connection ~ 10500 3050
Wire Wire Line
	10500 3050 10800 3050
Wire Wire Line
	10150 3050 10000 3050
Wire Wire Line
	10000 3050 10000 3000
$Comp
L power:+5V #PWR0107
U 1 1 60111406
P 1700 2950
F 0 "#PWR0107" H 1700 2800 50  0001 C CNN
F 1 "+5V" H 1715 3123 50  0000 C CNN
F 2 "" H 1700 2950 50  0001 C CNN
F 3 "" H 1700 2950 50  0001 C CNN
	1    1700 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6011140C
P 2500 3250
F 0 "#PWR0108" H 2500 3000 50  0001 C CNN
F 1 "GND" H 2505 3077 50  0000 C CNN
F 2 "" H 2500 3250 50  0001 C CNN
F 3 "" H 2500 3250 50  0001 C CNN
	1    2500 3250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AP2112K-3.3 U1
U 1 1 60111412
P 3700 3100
F 0 "U1" H 3700 3442 50  0000 C CNN
F 1 "AP2112K-3.3" H 3700 3351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 3700 3425 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2112.pdf" H 3700 3200 50  0001 C CNN
	1    3700 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3000 3300 3100
Wire Wire Line
	3300 3100 3400 3100
Connection ~ 3300 3000
Wire Wire Line
	3300 3000 3400 3000
$Comp
L Device:C_Small C1
U 1 1 6011141C
P 2700 3100
F 0 "C1" H 2792 3146 50  0000 L CNN
F 1 "10uF" H 2792 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2700 3100 50  0001 C CNN
F 3 "~" H 2700 3100 50  0001 C CNN
	1    2700 3100
	1    0    0    -1  
$EndComp
Connection ~ 3050 3000
Wire Wire Line
	3050 3000 3300 3000
Connection ~ 2700 3000
Wire Wire Line
	2700 3000 3050 3000
$Comp
L Device:C_Small C2
U 1 1 60111426
P 3050 3100
F 0 "C2" H 3142 3146 50  0000 L CNN
F 1 "0.1uF" H 3142 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3050 3100 50  0001 C CNN
F 3 "~" H 3050 3100 50  0001 C CNN
	1    3050 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3250 2500 3200
Wire Wire Line
	2500 3200 2700 3200
Connection ~ 2700 3200
Wire Wire Line
	2700 3200 3050 3200
$Comp
L Device:C_Small C3
U 1 1 60111430
P 4200 3100
F 0 "C3" H 4292 3146 50  0000 L CNN
F 1 "10uF" H 4292 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4200 3100 50  0001 C CNN
F 3 "~" H 4200 3100 50  0001 C CNN
	1    4200 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 60111436
P 3700 3450
F 0 "#PWR0109" H 3700 3200 50  0001 C CNN
F 1 "GND" H 3705 3277 50  0000 C CNN
F 2 "" H 3700 3450 50  0001 C CNN
F 3 "" H 3700 3450 50  0001 C CNN
	1    3700 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 6011143C
P 4600 3100
F 0 "C4" H 4692 3146 50  0000 L CNN
F 1 "0.1uF" H 4692 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4600 3100 50  0001 C CNN
F 3 "~" H 4600 3100 50  0001 C CNN
	1    4600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3450 3700 3400
$Comp
L power:GND #PWR0110
U 1 1 60111443
P 4600 3250
F 0 "#PWR0110" H 4600 3000 50  0001 C CNN
F 1 "GND" H 4605 3077 50  0000 C CNN
F 2 "" H 4600 3250 50  0001 C CNN
F 3 "" H 4600 3250 50  0001 C CNN
	1    4600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3250 4600 3200
Wire Wire Line
	4600 3200 4200 3200
Connection ~ 4600 3200
$Comp
L power:+3.3V #PWR0111
U 1 1 6011144C
P 4600 2950
F 0 "#PWR0111" H 4600 2800 50  0001 C CNN
F 1 "+3.3V" H 4615 3123 50  0000 C CNN
F 2 "" H 4600 2950 50  0001 C CNN
F 3 "" H 4600 2950 50  0001 C CNN
	1    4600 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3000 4200 3000
Wire Wire Line
	4600 3000 4600 2950
Connection ~ 4600 3000
Connection ~ 4200 3000
Wire Wire Line
	4200 3000 4600 3000
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 60111457
P 900 3150
F 0 "J1" H 818 2825 50  0000 C CNN
F 1 "5V PWR" H 818 2916 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" H 900 3150 50  0001 C CNN
F 3 "~" H 900 3150 50  0001 C CNN
	1    900  3150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6011145D
P 1350 3150
F 0 "#PWR0112" H 1350 2900 50  0001 C CNN
F 1 "GND" H 1355 2977 50  0000 C CNN
F 2 "" H 1350 3150 50  0001 C CNN
F 3 "" H 1350 3150 50  0001 C CNN
	1    1350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3150 1100 3150
$Comp
L power:+5V #PWR0113
U 1 1 60111464
P 1350 3050
F 0 "#PWR0113" H 1350 2900 50  0001 C CNN
F 1 "+5V" H 1365 3223 50  0000 C CNN
F 2 "" H 1350 3050 50  0001 C CNN
F 3 "" H 1350 3050 50  0001 C CNN
	1    1350 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3050 1100 3050
$Comp
L Device:C_Small C11
U 1 1 6011146B
P 7950 3100
F 0 "C11" H 8042 3146 50  0000 L CNN
F 1 "0.1uF" H 8042 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7950 3100 50  0001 C CNN
F 3 "~" H 7950 3100 50  0001 C CNN
	1    7950 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C12
U 1 1 60111471
P 8350 3100
F 0 "C12" H 8442 3146 50  0000 L CNN
F 1 "0.1uF" H 8442 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8350 3100 50  0001 C CNN
F 3 "~" H 8350 3100 50  0001 C CNN
	1    8350 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C13
U 1 1 60111477
P 8750 3100
F 0 "C13" H 8842 3146 50  0000 L CNN
F 1 "0.1uF" H 8842 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8750 3100 50  0001 C CNN
F 3 "~" H 8750 3100 50  0001 C CNN
	1    8750 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3000 8350 3000
Connection ~ 8350 3000
Wire Wire Line
	8350 3000 7950 3000
Wire Wire Line
	7550 3200 7950 3200
Connection ~ 7550 3200
Connection ~ 7950 3200
Wire Wire Line
	7950 3200 8350 3200
Connection ~ 8350 3200
Wire Wire Line
	8350 3200 8750 3200
$Comp
L Device:Polyfuse_Small F1
U 1 1 60111486
P 2050 3000
F 0 "F1" V 1845 3000 50  0000 C CNN
F 1 "500mA" V 1936 3000 50  0000 C CNN
F 2 "Fuse:Fuse_1210_3225Metric" H 2100 2800 50  0001 L CNN
F 3 "~" H 2050 3000 50  0001 C CNN
	1    2050 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3000 2700 3000
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 6011148D
P 2400 3000
F 0 "FB1" V 2163 3000 50  0000 C CNN
F 1 "100 Ohm" V 2254 3000 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" V 2330 3000 50  0001 C CNN
F 3 "~" H 2400 3000 50  0001 C CNN
	1    2400 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 3000 2300 3000
Wire Wire Line
	1700 2950 1700 3000
Wire Wire Line
	1700 3000 1950 3000
$Comp
L power:+5V #PWR0114
U 1 1 60111496
P 8350 3000
F 0 "#PWR0114" H 8350 2850 50  0001 C CNN
F 1 "+5V" H 8365 3173 50  0000 C CNN
F 2 "" H 8350 3000 50  0001 C CNN
F 3 "" H 8350 3000 50  0001 C CNN
	1    8350 3000
	1    0    0    -1  
$EndComp
Text Notes 4950 2850 0    50   ~ 0
Vcap not populated\nfor all processors
$Comp
L power:+3.3V #PWR?
U 1 1 6012E922
P 9800 5000
AR Path="/6012E922" Ref="#PWR?"  Part="1" 
AR Path="/600E2939/6012E922" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 9800 4850 50  0001 C CNN
F 1 "+3.3V" H 9815 5173 50  0000 C CNN
F 2 "" H 9800 5000 50  0001 C CNN
F 3 "" H 9800 5000 50  0001 C CNN
	1    9800 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 6012E928
P 9800 5150
AR Path="/6012E928" Ref="D?"  Part="1" 
AR Path="/600E2939/6012E928" Ref="D1"  Part="1" 
F 0 "D1" V 9839 5032 50  0000 R CNN
F 1 "LED" V 9748 5032 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 9800 5150 50  0001 C CNN
F 3 "~" H 9800 5150 50  0001 C CNN
	1    9800 5150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6012E92E
P 9800 5400
AR Path="/6012E92E" Ref="R?"  Part="1" 
AR Path="/600E2939/6012E92E" Ref="R1"  Part="1" 
F 0 "R1" H 9741 5354 50  0000 R CNN
F 1 "1k" H 9741 5445 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 9800 5400 50  0001 C CNN
F 3 "~" H 9800 5400 50  0001 C CNN
	1    9800 5400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6012E934
P 9800 5500
AR Path="/6012E934" Ref="#PWR?"  Part="1" 
AR Path="/600E2939/6012E934" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 9800 5250 50  0001 C CNN
F 1 "GND" H 9805 5327 50  0000 C CNN
F 2 "" H 9800 5500 50  0001 C CNN
F 3 "" H 9800 5500 50  0001 C CNN
	1    9800 5500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
