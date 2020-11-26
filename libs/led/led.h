/*
 * led.h
 *
 * Created: 11.06.2020 11:51:17
 *  Author: ar725
 */ 


#ifndef LED_H_
#define LED_H_

#include "../tools/tools.h"

typedef struct Led_TypeDef {
	volatile uint8_t *DDRx;
	volatile uint8_t *PORTx;
	uint8_t PORTxx;
} Led_TypeDef;

void LedEnable(Led_TypeDef *led);
void LedDisable(Led_TypeDef *led);
void LedOn(Led_TypeDef *led);
uint8_t LedIsOn(Led_TypeDef *led);
void LedOff(Led_TypeDef *led);
void LedToggle(Led_TypeDef *led);



#endif /* LED_H_ */