/*
 * DS18B20.h
 *
 * Created: 10/9/2020 8:29:19 PM
 *  Author: ar725
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include "../tools/tools.h"

#define THERM_CMD_CONVERTTEMP 0x44
#define THERM_CMD_RSCRATCHPAD 0xbe
#define THERM_CMD_WSCRATCHPAD 0x4e
#define THERM_CMD_CPYSCRATCHPAD 0x48
#define THERM_CMD_RECEEPROM 0xb8
#define THERM_CMD_RPWRSUPPLY 0xb4
#define THERM_CMD_SEARCHROM 0xf0
#define THERM_CMD_READROM 0x33
#define THERM_CMD_MATCHROM 0x55
#define THERM_CMD_SKIPROM 0xcc
#define THERM_CMD_ALARMSEARCH 0xec

#define DS18B20_MAX_TEMP 127
#define DS18B20_MIN_TEMP -55

typedef struct DS18B20_TypeDef {
	volatile uint8_t *DDRx;
	volatile uint8_t *PORTx;
	volatile uint8_t *PINx;
	uint8_t PORTxx;
} DS18B20_TypeDef;

typedef struct Temperature {
	int8_t digit;
	uint16_t decimal;
} Temperature;

#define THERM_DECIMAL_STEPS_12BIT 625 //.0625

#define THERM_INPUT_MODE(ds) CB(*ds->DDRx, ds->PORTxx)
#define THERM_OUTPUT_MODE(ds) SB(*ds->DDRx, ds->PORTxx)
#define THERM_LOW(ds) CB(*ds->PORTx, ds->PORTxx)
#define THERM_HIGH(ds) SB(*ds->PORTx, ds->PORTxx)
#define THERM_GET_INPUT(ds) (*ds->PINx & SH(ds->PORTxx))

#define THERM_DECIMAL_STEPS_12BIT 625 //.0625

Temperature DS18B20_read_temperature(DS18B20_TypeDef *ds);





#endif /* DS18B20_H_ */