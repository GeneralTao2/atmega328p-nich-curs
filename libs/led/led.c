/*
 * led.c
 *
 * Created: 11.06.2020 11:51:40
 *  Author: ar725
 */ 
#include "led.h"

void LedEnable(Led_TypeDef *led) {
	SB(*led->DDRx, led->PORTxx);
}

void LedDisable(Led_TypeDef *led) {
	CB(*led->DDRx, led->PORTxx);
}

void LedOn(Led_TypeDef *led) {
	SB(*led->PORTx, led->PORTxx);
}

void LedOff(Led_TypeDef *led) {
	CB(*led->PORTx, led->PORTxx);
}

void LedToggle(Led_TypeDef *led) {
	TB(*led->PORTx, led->PORTxx);
}