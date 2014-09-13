# Arduino library for AD9850 #
Created 23/08/2014 by Christophe Caiveau f4goj@free.fr

Upgrade to SPI Anthony f4goh@orange.fr

This library uses the Serial Peripheral Interface (SPI) to accelerate the update of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase calculation and 36µs for the transfert)

AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Use this library freely.

## Installation ##
To use the **AD9850SPI** library:  
- Go to https://github.com/f4goj/AD9850SPI, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **AD9850SPI-master**.
- Rename the folder to just **AD9850SPI**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.


## Usage notes ##

To use the **AD9850SPI** library, the SPI library must also be included.
```c++
#include <AD9850SPI.h>    //http://github.com/f4goj/AD9850
#include <SPI.h>         //http://arduino.cc/en/Reference/SPI (included with Arduino IDE)
```
##### Hardware connections : #####

- W_CLK -> D13 arduino UNO/NANO, D52 MEGA
- FQ_UD -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
- DATA/D7 -> D11 arduino UNO/NANO, D51 MEGA
- RESET -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA

##### Instance : #####

AD9850SPI dds(W_CLK pin, FQ_UD pin, RESET pin);

##### Functions : #####

- dds.begin(); Initialize the output pins and master reset the AD9850
- dds.calibrate(frequency); Compensation of crystal oscillator frequency
- dds.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
- dds.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
- dds.up(); wake-up the AD9850

