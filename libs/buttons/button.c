/*
 * button.c
 *
 * Created: 09.06.2020 20:44:50
 *  Author: ar725
 */ 
#include "button.h"

void Button_init(Button_TypeDef *configs) {
	SB(*configs->PORTx, configs->PORTxx);
	SB(*configs->PCMSKx, configs->PORTxx);
	SB(PCICR, configs->PCIEx);
}

void Button_press(Button_TypeDef *configs) {
	if(ButtonsEnablingState) {
		configs->pressed = 1;
	}
}

uint8_t Button_isPressed(Button_TypeDef *configs) {
	return configs->pressed && ButtonsEnablingState;
}

void Button_unPress(Button_TypeDef *configs) {
	configs->pressed = 0;
}


void Buttons_enable() {
	TIM1_Stop();
	ButtonsEnablingState = 1;
}
void Buttons_disable() {
	TIM1_Start();
	ButtonsEnablingState = 0;
}
