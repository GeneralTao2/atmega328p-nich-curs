/*
 * button.h
 *
 * Created: 09.06.2020 20:45:05
 *  Author: ar725
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../tools/tools.h"
#include "../timers/timers.h"

static volatile uint8_t ButtonsEnablingState = 1;

typedef struct Button_TypeDef {
	volatile uint8_t *PORTx;
	volatile uint8_t *PCMSKx;
	uint8_t PORTxx;
	uint8_t PCIEx;
	volatile uint8_t pressed;
	void (*onClick)();
} Button_TypeDef;

void Button_init(Button_TypeDef *configs);

void Buttons_enable();
void Buttons_disable();

uint8_t Button_isPressed(Button_TypeDef *configs);

void Button_unPress(Button_TypeDef *configs);
void Button_press(Button_TypeDef *configs);


#endif /* BUTTON_H_ */