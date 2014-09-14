# Arduino SPI library for AD9850 #
Christophe Caiveau f4goj@free.fr

August 2014

Upgrade to SPI Anthony f4goh@orange.fr

This library uses the Serial Peripheral Interface (SPI) to accelerate the update of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase calculation and 36µs for the transfert)

AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Use this library freely.

## Installation ##
To use the **AD9850SPI** library:  
- Go to https://github.com/f4goj/AD9850SPI, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **AD9850SPI-master**.
- Rename the folder to  **AD9850SPI**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.


## Usage notes ##

Similar to the **RTC** library, the **AD9850SPI** library instantiates a **DDS** object; the user does not need to do this.

To use the **AD9850SPI** library, the SPI library must also be included.

```c++
#include <AD9850SPI.h>    //http://github.com/f4goj/AD9850
#include <SPI.h>          //http://arduino.cc/en/Reference/SPI (included with Arduino IDE)
```
## Hardware connections : ##

- W_CLK -> D13 arduino UNO/NANO, D52 MEGA
- FQ_UD -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
- DATA/D7 -> D11 arduino UNO/NANO, D51 MEGA
- RESET -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA

## Instance : ##

###
######Description
Create an instance of the object AD9850SPI
#####Syntax
`AD9850SPI name_of_the_instance(W_CLK pin, FQ_UD pin, RESET pin);`
#####Parameters
**name_of_the_instance :**  
#####Returns
None.
#####Example
`AD9850SPI dds(13, 8, 9);`

## Functions : ##

- dds.begin(); Initialize the output pins and master reset the AD9850
- dds.calibrate(frequency); Compensation of crystal oscillator frequency
- dds.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
- dds.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
- dds.up(); wake-up the AD9850

###get(void)
#####Description
Reads the current date and time from the RTC and returns it as a *time_t* value. Returns zero if an I2C error occurs (RTC not present, etc.).
#####Syntax
`RTC.get();`
#####Parameters
None.
#####Returns
Current date and time *(time_t)*
#####Example
```c++
#include <AD9850SPI.h>
#include <SPI.h>

AD9850 dds(13, 8, 9);

void setup(){
 dds.begin();
}

void loop(){
 dds.setfreq(14070000.0, 0);
 delay(5000);
 dds.down();
 delay(5000);
}
```
