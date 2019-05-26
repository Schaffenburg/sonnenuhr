EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5CEA9AD0
P 3300 3050
F 0 "A1" V 3346 2006 50  0000 R CNN
F 1 "Arduino_Nano_v3.x" V 3255 2006 50  0000 R CNN
F 2 "Module:Arduino_Nano" H 3450 2100 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3300 2050 50  0001 C CNN
	1    3300 3050
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_Array:ULN2803A U1
U 1 1 5CEAA839
P 5750 4000
F 0 "U1" H 5750 4567 50  0000 C CNN
F 1 "ULN2803A" H 5750 4476 50  0000 C CNN
F 2 "Package_DIP:DIP-18_W7.62mm_Socket_LongPads" H 5800 3350 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 5850 3800 50  0001 C CNN
	1    5750 4000
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_unipolar_5pin #M1
U 1 1 5CEAAF02
P 8000 4000
F 0 "#M1" H 7922 3767 50  0000 C CNN
F 1 "Stepper_Motor_unipolar_5pin" H 7922 3676 50  0000 C CNN
F 2 "" H 8010 3990 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 8010 3990 50  0001 C CNN
	1    8000 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5CEAC09C
P 4700 5200
F 0 "#PWR0101" H 4700 4950 50  0001 C CNN
F 1 "GND" H 4705 5027 50  0000 C CNN
F 2 "" H 4700 5200 50  0001 C CNN
F 3 "" H 4700 5200 50  0001 C CNN
	1    4700 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5CEAC59C
P 2200 1400
F 0 "#PWR0102" H 2200 1250 50  0001 C CNN
F 1 "+5V" H 2215 1573 50  0000 C CNN
F 2 "" H 2200 1400 50  0001 C CNN
F 3 "" H 2200 1400 50  0001 C CNN
	1    2200 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Female #J4
U 1 1 5CEAD4BD
P 7200 3900
F 0 "#J4" H 7092 4285 50  0000 C CNN
F 1 "Conn_01x05_Female" H 7092 4194 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 7200 3900 50  0001 C CNN
F 3 "~" H 7200 3900 50  0001 C CNN
	1    7200 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6150 3800 6750 3800
Wire Wire Line
	6150 3900 6750 3900
Wire Wire Line
	6150 4000 6750 4000
Wire Wire Line
	6150 4100 6750 4100
$Comp
L power:+3V3 #PWR0103
U 1 1 5CEDEB1A
P 1900 1500
F 0 "#PWR0103" H 1900 1350 50  0001 C CNN
F 1 "+3V3" H 1915 1673 50  0000 C CNN
F 2 "" H 1900 1500 50  0001 C CNN
F 3 "" H 1900 1500 50  0001 C CNN
	1    1900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1400 2200 2850
Wire Wire Line
	2200 2850 2300 2850
Wire Wire Line
	1900 2950 2300 2950
$Comp
L power:+5V #PWR0104
U 1 1 5CEF6C07
P 6650 3150
F 0 "#PWR0104" H 6650 3000 50  0001 C CNN
F 1 "+5V" H 6665 3323 50  0000 C CNN
F 2 "" H 6650 3150 50  0001 C CNN
F 3 "" H 6650 3150 50  0001 C CNN
	1    6650 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3700 7400 3700
Wire Wire Line
	7900 3700 7900 3650
Wire Wire Line
	7900 3650 7650 3650
Wire Wire Line
	7650 3650 7650 3800
Wire Wire Line
	7650 3800 7400 3800
Wire Wire Line
	8100 3700 8100 3600
Wire Wire Line
	8100 3600 7550 3600
Wire Wire Line
	7550 3600 7550 3900
Wire Wire Line
	7550 3900 7400 3900
Wire Wire Line
	7700 3900 7650 3900
Wire Wire Line
	7650 3900 7650 4000
Wire Wire Line
	7650 4000 7400 4000
Wire Wire Line
	7700 4100 7400 4100
$Comp
L sonnenuhr:GYML8511 #U2
U 1 1 5CF0EBF5
P 7700 1650
F 0 "#U2" H 7950 1815 50  0000 C CNN
F 1 "GYML8511" H 7950 1724 50  0000 C CNN
F 2 "sonnenuhr-pcb:GYML8511" H 7700 1650 50  0001 C CNN
F 3 "" H 7700 1650 50  0001 C CNN
	1    7700 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Female #J3
U 1 1 5CF0FF59
P 7200 1950
F 0 "#J3" H 7092 2335 50  0000 C CNN
F 1 "Conn_01x05_Female" H 7092 2244 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 7200 1950 50  0001 C CNN
F 3 "~" H 7200 1950 50  0001 C CNN
	1    7200 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 1750 7800 1750
Wire Wire Line
	7400 1850 7800 1850
Wire Wire Line
	7400 1950 7800 1950
Wire Wire Line
	7400 2050 7800 2050
Wire Wire Line
	7400 2150 7800 2150
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 5CED387B
P 6900 1950
F 0 "J1" V 6962 2194 50  0000 L CNN
F 1 "Conn_01x05_Male" V 7053 2194 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 6900 1950 50  0001 C CNN
F 3 "~" H 6900 1950 50  0001 C CNN
	1    6900 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6700 1850 3400 1850
Wire Wire Line
	3400 1850 3400 1500
$Comp
L power:+3V3 #PWR0105
U 1 1 5CF1C18D
P 3400 1500
F 0 "#PWR0105" H 3400 1350 50  0001 C CNN
F 1 "+3V3" H 3415 1673 50  0000 C CNN
F 2 "" H 3400 1500 50  0001 C CNN
F 3 "" H 3400 1500 50  0001 C CNN
	1    3400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1950 4700 1950
Wire Wire Line
	6700 2150 5050 2150
Wire Wire Line
	5050 2150 5050 3700
Wire Wire Line
	4300 3050 4700 3050
Wire Wire Line
	4300 2950 4700 2950
Wire Wire Line
	4700 2950 4700 3050
Wire Wire Line
	4700 1950 4700 2950
Connection ~ 4700 2950
Wire Wire Line
	4700 3050 4700 4950
Wire Wire Line
	4700 4950 5750 4950
Wire Wire Line
	5750 4950 5750 4700
Connection ~ 4700 3050
Wire Wire Line
	4700 4950 4700 5200
Connection ~ 4700 4950
Wire Wire Line
	6700 2050 3500 2050
Wire Wire Line
	3500 2050 3500 2550
Connection ~ 3400 1850
Wire Wire Line
	3400 1850 3400 2550
Wire Wire Line
	1900 1500 1900 2950
Wire Wire Line
	6650 3150 6650 3700
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5CEACC56
P 6950 4000
F 0 "J2" H 6922 4024 50  0000 R CNN
F 1 "Conn_01x05_Male" H 6922 3933 50  0000 R CNN
F 2 "Connector_JST:JST_PH_B5B-PH-K_1x05_P2.00mm_Vertical" H 6950 4000 50  0001 C CNN
F 3 "~" H 6950 4000 50  0001 C CNN
	1    6950 4000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6350 3700 6150 3700
Connection ~ 6650 3700
$Comp
L Device:D_Zener D1
U 1 1 5CEAB647
P 6500 3700
F 0 "D1" H 6500 3916 50  0000 C CNN
F 1 "D_Zener" H 6500 3825 50  0000 C CNN
F 2 "Diode_THT:D_T-1_P10.16mm_Horizontal" H 6500 3700 50  0001 C CNN
F 3 "~" H 6500 3700 50  0001 C CNN
	1    6500 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3700 6650 4200
Wire Wire Line
	6650 4200 6750 4200
Wire Wire Line
	3200 3550 3200 4100
Wire Wire Line
	3200 4100 5350 4100
Wire Wire Line
	3300 3550 3300 4000
Wire Wire Line
	3300 4000 5350 4000
Wire Wire Line
	3400 3550 3400 3900
Wire Wire Line
	3400 3900 5350 3900
Wire Wire Line
	3500 3550 3500 3800
Wire Wire Line
	3500 3800 5350 3800
Wire Wire Line
	3700 3700 3700 3550
Wire Wire Line
	3700 3700 5050 3700
Text Label 6700 2050 0    50   ~ 0
UVMeasure
Text Label 6700 2150 0    50   ~ 0
SensorEnable
$EndSCHEMATC
