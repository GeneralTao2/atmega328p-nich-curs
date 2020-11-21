/*
 * interrupts.h
 *
 * Created: 10/10/2020 7:06:28 PM
 *  Author: ar725
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/interrupt.h>
#include "../tools/tools.h"
#include "../buttons/button.h"
#include "../timers/timers.h"
#include "../led/led.h"

extern Led_TypeDef led1;

#define TEXT_BLINKING_COUNT 200
static uint8_t textBlinkingCounter = 0;
extern volatile uint8_t textBlinkingFlag;

#define  LCD_PRINTING_COUNT 100
static uint8_t LCDPrintingCounter = 0;
extern volatile uint8_t LCDPrintingFlag;

extern Button_TypeDef buttonLeft;

#endif /* INTERRUPTS_H_ */