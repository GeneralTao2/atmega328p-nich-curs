/*
 * CFile1.c
 *
 * Created: 10/9/2020 8:28:53 PM
 *  Author: ar725
 */ 

#include "DS18B20.h"

uint8_t DS18B20_reset(DS18B20_TypeDef *ds){
	uint8_t i;
	//Pull line low and wait for 480uS
	THERM_LOW(ds);
	THERM_OUTPUT_MODE(ds);
	_delay_us(480);
	//Release line and wait for 60uS
	THERM_INPUT_MODE(ds);
	_delay_us(60);
	//Store line value and wait until the completion of 480uS period
	i=THERM_GET_INPUT(ds);
	_delay_us(420);
	//Return the value read from the presence pulse (0=OK, 1=WRONG)
	return i;
}

void DS18B20_write_bit(DS18B20_TypeDef *ds, uint8_t bit){
	//Pull line low for 1uS
	THERM_LOW(ds);
	THERM_OUTPUT_MODE(ds);
	_delay_us(1);
	//If we want to write 1, release the line (if not will keep low)
	if(bit) THERM_INPUT_MODE(ds);
	//Wait for 60uS and release the line
	_delay_us(60);
	THERM_INPUT_MODE(ds);
}

uint8_t DS18B20_read_bit(DS18B20_TypeDef *ds){
	uint8_t bit=0;
	//Pull line low for 1uS
	THERM_LOW(ds);
	THERM_OUTPUT_MODE(ds);
	_delay_us(1);
	//Release line and wait for 14uS
	THERM_INPUT_MODE(ds);
	_delay_us(14);
	//Read line value
	if(THERM_GET_INPUT(ds)) bit=1;
	//Wait for 45uS to end and return read value
	_delay_us(45);
	return bit;
}
uint8_t DS18B20_read_byte(DS18B20_TypeDef *ds){
	uint8_t i=8, n=0;
	while(i--){
		//Shift one position right and store read value
		n>>=1;
		n|=(DS18B20_read_bit(ds)<<7);
	}
	return n;
}
void DS18B20_write_byte(DS18B20_TypeDef *ds, uint8_t byte){
	uint8_t i=8;
	while(i--){
		//Write actual bit and shift one position right to make the next bit ready
		DS18B20_write_bit(ds, byte&1);
		byte>>=1;
	}
}

Temperature DS18B20_read_temperature(DS18B20_TypeDef *ds){
	// Buffer length must be at least 12bytes long! ["+XXX.XXXX C"]
	uint8_t temperature[3];
	Temperature temp;
	//Reset, skip ROM and start temperature conversion
	DS18B20_reset(ds);
	DS18B20_write_byte(ds, THERM_CMD_SKIPROM);
	DS18B20_write_byte(ds, THERM_CMD_CONVERTTEMP);
	//Wait until conversion is complete
	THERM_HIGH(ds);
	_delay_us(800);
	while(!DS18B20_read_bit(ds));
	//THERM_HIGH(ds);
	//_delay_us(800);
	//Reset, skip ROM and send command to read Scratchpad
	DS18B20_reset(ds);
	DS18B20_write_byte(ds, THERM_CMD_SKIPROM);
	DS18B20_write_byte(ds, THERM_CMD_RSCRATCHPAD);
	//Read Scratchpad (only 2 first bytes)
	temperature[0]=DS18B20_read_byte(ds);
	temperature[1]=DS18B20_read_byte(ds);
	temp.a = temperature[2]=DS18B20_read_byte(ds);
	DS18B20_reset(ds);
	//Store temperature integer digits and decimal digits
	temp.digit=temperature[0]>>4;
	temp.digit|=temperature[1]<<4;
	//Store decimal digits
	temp.decimal=temperature[0]&0xf;
	temp.decimal*=THERM_DECIMAL_STEPS_12BIT;
	temp.b = temperature[0];
	temp.c = temperature[1];
	return temp;
}