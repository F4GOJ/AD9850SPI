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

#include <AD9850SPI.h>
#include <SPI.h>

AD9850SPI DDS;

AD9850SPI::AD9850SPI() {
	SPI.begin();
}

void AD9850SPI::begin(int w_clk, int fq_ud, int reset) {
	W_CLK = w_clk;
	FQ_UD = fq_ud;
	RESET = reset;
	deltaphase = 0;
	phase = 0;
	calibFreq = 125000000;
	begin_priv();
}

void AD9850SPI::begin_priv() {
	pinMode(W_CLK, OUTPUT);
	pinMode(FQ_UD, OUTPUT);
	pinMode(RESET, OUTPUT);
	
	SPI.setClockDivider(SPI_CLOCK_DIV4);
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(SPI_MODE0);

	pulse(RESET);
	pulse(W_CLK);
	pulse(FQ_UD);
}

void AD9850SPI::update() {

	for (int i=0; i<4; i++, deltaphase>>=8) {
		SPI.transfer(deltaphase & 0xFF);
	}
	SPI.transfer(phase & 0xFF);
	pulse(FQ_UD);
}


void AD9850SPI::setfreq(double f, uint8_t p) {
	deltaphase = f * 4294967296.0 / calibFreq;
	phase = p << 3;
	update();
}


void AD9850SPI::down() {
	pulse(FQ_UD);
	SPI.transfer(0x04);
	pulse(FQ_UD);
}
    

void AD9850SPI::up() {
	update();
}


void AD9850SPI::calibrate(double TrimFreq)
{
	calibFreq = TrimFreq;
}

void AD9850SPI::powerOn(){
  pinMode(11, OUTPUT);
  delay(100);  
  wakeUp();
  delay(100);
  update();
}

void AD9850SPI::powerOff(){
 pinMode(11, INPUT);
}

void AD9850SPI::wakeUp()
{
 pulse(RESET);
 pulse(W_CLK);
 pulse(FQ_UD); 
}

void AD9850SPI::pulse(int pin) {
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}

void AD9850SPI::vna(unsigned long DS_FTW,uint8_t Mode) {
 deltaphase=(double) DS_FTW;
 phase=Mode;
 update();
}
