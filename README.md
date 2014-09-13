# Arduino library for AD9850 #
Created 23/08/2014 by Christophe Caiveau f4goj@free.fr

Upgrade to SPI Anthony f4goh@orange.fr

This library uses the Serial Peripheral Interface (SPI) to accelerate the update of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase calculation and 36µs for the transfert)

Use this library freely.

## Installation ##
To use the **AD9850** library:  
- Go to https://github.com/f4goj/AD9850, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **AD9850-master**.
- Rename the folder to just **AD9850**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.


## Usage notes ##

When using the **AD9850** library, the user is responsible for ensuring that reads and writes do not exceed the device's address space (0x00-0x12 for DS3231, 0x00-0xFF for DS3232); no bounds checking is done by the library.            

Similar to the **DS1307RTC** library, the **DS3232RTC** library instantiates an RTC object; the user does not need to do this.

To use the **AD9850SPI** library, the Wire library must also be included.
```c++
#include <AD9850SPI.h>    //http://github.com/f4goj/AD9850
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
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

AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf
