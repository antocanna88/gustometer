# Assembly Instructions
In this document we summarize the steps needed to assembly the gustometer
prototype as described in the published paper "A low-cost open-architecture
taste delivery system for gustatory fMRI and BCI experiments".

## Power supplies
The prototype needs a 5Vdc power supply for the digital control of the pump 
drivers and the Arduino UNO. The easiest way to supply the 5Vdc is through a
type-B USB cable from a pc connected to the USB jack on the Arduino UNO.

In addition, at least 24W at 12Vdc are needed to drive the micropumps. We used
an external power supply connected direcly to the 220Vac line. Make sure to 
connect the GND pin of the Arduino UNO to the ground terminal of the external
power supply to have a common reference ground.

## USB to serial converter
The prototype uses two serial UART interfaces. The default one, implicitly 
connected to the pc by the type-B USB cable, is used to program
the device. The second, is used to receive the commands controlling the 
micropumps. To connect this serial interface to the pc, the USB-to-serial 
converer PL2303 is connected to the Arduino UNO. Specifically the TX pin of 
the PL2303 is connected to pin 10 of the Arduino UNO and the RX pin of the
PL2303 is connected to pin 11 of the Arduino UNO. To ensure the same ground 
level, connect the GND pin of the PL2303 to the GND pin on the Arduino UNO.
Lastly, the PL2303 is connected to the pc with a mini USB cable.

### Troubleshooting
It may be the case that when testing the command serial connection strange
characters or nothing at all is transmitted or received. In this case, 
inverting the role of the RX and TX pins of the PL2303 can solve the problem.

## L293D driver to Micropumps
Each L293D contains four half H-bridge drivers which can be used in the 
configuration of two full H-bridge driver. Each H-bridge will drive a 
micropump, hence, a single L293D drives two micropumps. The L293D needs two
power supplies, the 5Vdc for the control logic are provided by the Arduino UNO,
connecting the 5V pin of the Arduino UNO to the Vcc1 pin of the L293D. The 
12Vdc for drivers is provided by the external power supply by connecting the 
12V terminal to the Vcc2 pin of the L293D. 
Next, connect the EN1 and EN2 pins of the L293D to 5V in order to always keep
the drivers enabled. The first micropump is connected to the pins OUT1 and OUT2,
whereas the second micropump is connected to the pins OUT3 and OUT4 of the L293D.
The same connections have to be repeated for the other two L293D and the other
four micropumps. 
Next, the pins IN2 and IN4 of each L293D go connected to ground.
Finally, the pins IN1 and IN3 of each L293D are connected respectively to the
pins 2, 3, 4, 5, 6, 7 of the Arduino UNO.

### Troubleshooting
If any of the micropumps rotate in the wrong direction, i.e. it pulls the 
taste fluid away from the subject instead of pushing it towards the subject, 
it may be due to a wrong connection of the micropump to the OUT pins and can be
solved by inverting the connections.
