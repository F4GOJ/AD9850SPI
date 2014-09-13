Arduino library for AD9850
Created 23/08/2014 by Christophe Caiveau f4goj@free.fr
Upgrade to SPI Anthony f4goh@orange.fr

This library uses the Serial Peripheral Interface (SPI) to accelerate the update of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase calculation and 36µs for the transfert)

Use this library freely

Hardware connections :
W_CLK -> D13 arduino UNO/NANO, D52 MEGA
FQ_UD -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
DATA/D7 -> D11 arduino UNO/NANO, D51 MEGA
RESET -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA

Instance :
AD9850SPI dds(W_CLK pin, FQ_UD pin, RESET pin);

Functions :
dds.begin(); Initialize the output pins and master reset the AD9850
dds.calibrate(frequency); Compensation of crystal oscillator frequency
dds.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
dds.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
dds.up(); wake-up the AD9850

AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf
