# Arduino SPI library for AD9850 #
F4GOJ Christophe f4goj@free.fr

August 2014

Upgrade to SPI F4GOH Anthony f4goh@orange.fr

This library uses the Serial Peripheral Interface (SPI) to accelerate the update of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase calculation and 36µs for the transfert)

AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Use this library freely.

## Installation ##
To use the **AD9850SPI** library:  
- Go to https://github.com/F4GOJ/AD9850SPI, click the [Download ZIP](https://github.com/F4GOJ/AD9850SPI/archive/master.zip) button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **AD9850SPI-master**.
- Rename the folder to  **AD9850SPI**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.


## Usage notes ##

The **AD9850SPI** library instantiates a **DDS** object, the user does not need to do this.

To use the **AD9850SPI** library, the SPI library must also be included.

```c++
#include <AD9850SPI.h> //http://github.com/F4GOJ/AD9850SPI
#include <SPI.h>       //http://arduino.cc/en/Reference/SPI (included with Arduino IDE)
```
## Hardware connections : ##

![ad9850](https://raw.githubusercontent.com/F4GOJ/AD9850SPI/master/images/AD9850.png)![ad9850_2](https://raw.githubusercontent.com/F4GOJ/AD9850SPI/master/images/AD9850_connections_M2.png)
- W_CLK -> D13 arduino UNO/NANO, D52 MEGA
- FQ_UD -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
- DATA/D7 -> D11 arduino UNO/NANO, D51 MEGA
- RESET -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA

## Functions : ##

### begin(int w_clk_pin, int fq_ud_pin, int reset_pin)
##### Description
Initialize the output pins and master reset the AD9850
##### Syntax
`DDS.begin(w_clk, fq_ud, reset);`
##### Parameters
**w_clk :** SPI SCK output pin (13 on a UNO/NANO, 52 on a MEGA) *(int)*<br>
**fq_ud :** Frequency update pin, any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA. *(int)*<br>
**reset :** Reset output pin, any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA. *(int)*
##### Returns
None.
##### Example
```c++
void setup(){
 DDS.begin(13, 8, 9);
}
```
### calibrate(double trim_frequency)
##### Description
Compensation of crystal oscillator frequency.<br>
Can be used at any time after initialization.
##### Syntax
`DDS.calibrate(trim_freq);`
##### Parameters
**trim_freq :** Adjust around 125000000 to match the real crystal oscillator frequency. *(double)*
##### Returns
None.
##### Example
```c++
void setup(){
 DDS.begin(13, 8, 9);
}

void loop(){
 DDS.calibrate(124999000);
}
```
### setfreq(double frequency, int phase)
##### Description
Sets the output frequency of the AD9850 and the phase of the signal.
##### Syntax
`DDS.setfreq(frequency, phase);`
##### Parameters
**frequency :** Output frequency in Hz. *(double)*<br>
**phase :** Sets the phase of the output signal, coded on 5 bits allows 32 phase steps of 11,25° each. *(int)*
##### Returns
None.
##### Example
```c++
double frequency = 10000000;
int phase = 0;
DDS.setfreq(frequency, phase);
```
### down()
##### Description
Power down mode reducing the dissipated power from 380mW to 30mW at 5V
##### Syntax
`DDS.down();`
##### Parameters
None.
##### Returns
None.
##### Example
```c++
DDS.down();
```
### up()
##### Description
Wakes-up the AD9850 from power down mode.
##### Syntax
`DDS.up();`
##### Parameters
None.
##### Returns
None.
##### Example
```c++
DDS.down(); // Entering power down mode

// some code doing something

...

DDS.up(); // WAKE-UP !!! :)
```

