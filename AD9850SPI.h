/********************************************************************************************
 * Arduino library for AD9850
 * Created 23/08/2014
 * Christophe Caiveau f4goj@free.fr 
 * Upgrade to SPI Anthony F4GOH
 *
 * This library uses the Serial Peripheral Interface (SPI) to accelerate the update
 * of the AD9850 from 700µs in software serial to 90µs (54µs for the deltaphase
 * calculation and 36µs for the transfert)
 *
 * Use this library freely
 *
 * Hardware connections : 
 * W_CLK   -> D13 arduino UNO/NANO, D52 MEGA
 * FQ_UD   -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
 * DATA/D7 -> D11 arduino UNO/NANO, D51 MEGA
 * RESET   -> any pin except 10 and 12 UNO/NANO, 50 and 53 MEGA
 *
 * Functions :
 * DDS.begin(W_CLK pin, FQ_UD pin, RESET pin); Initialize the output pins and master reset the AD9850 
 * DDS.calibrate(frequency); Compensation of crystal oscillator frequency
 * DDS.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
 * DDS.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
 * DDS.up(); wake-up the AD9850
 *
 * AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf
 *
 *******************************************************************************************/
 
 
#ifndef AD9850SPI_H
#define AD9850SPI_H
#include <Arduino.h>

class AD9850SPI
{
	public:
		AD9850SPI();

		void begin(int w_clk, int fq_ud, int reset);
		void setfreq(double f, uint8_t p);
		void down();
		void up();
		void calibrate(double TrimFreq);
		void powerOn();
		void powerOff();
		void vna(unsigned long DS_FTW, uint8_t Mode);
	
	private:
		int W_CLK;
		int FQ_UD;
		int RESET;
		uint32_t deltaphase;
		uint8_t phase;
		void update();
		void begin_priv();
		void pulse(int pin);
		void wakeUp();
		double calibFreq;
};

extern AD9850SPI DDS;

#endif
