/*
 * interrupts.c
 *
 * Created: 10/10/2020 7:06:13 PM
 *  Author: ar725
 */ 

#include "interrupts.h"
extern uint8_t counter1;
ISR(TIMER2_COMPA_vect) {
	if(textBlinkingCounter >= TEXT_BLINKING_COUNT) {
		textBlinkingFlag = !textBlinkingFlag;
		textBlinkingCounter = 0;
	}
	textBlinkingCounter++;
	
	if(LCDPrintingCounter >= LCD_PRINTING_COUNT) {
		LCDPrintingFlag = !LCDPrintingFlag;
		LCDPrintingCounter = 0;
	}
	LCDPrintingCounter++;
}

ISR(TIMER1_COMPA_vect) {
	if( ++TIM1_extraTime >= TIM1_EXTRA_DELAY ) {
		Buttons_enable();
		TIM1_extraTime = 0;
	}
}

ISR(PCINT0_vect) {
	if(!ButtonsEnablingState) {
		return;
	}
	
	if(~PINB & SH(buttonMenu.PORTxx) ) {
		Button_press(&buttonMenu);
		return;
		} else {
		Button_unPress(&buttonMenu);
	}
	
	if(~PINB & SH(buttonLeft.PORTxx) ) {
		Button_press(&buttonLeft);
		return;
	} else {
		Button_unPress(&buttonLeft);
	}
	
	if(~PINB & SH(buttonRight.PORTxx) ) {
		Button_press(&buttonRight);
		return;
	} else {
		Button_unPress(&buttonRight);
	}
	
	if(~PINB & SH(buttonUp.PORTxx) ) {
		Button_press(&buttonUp);
		return;
	} else {
		Button_unPress(&buttonUp);
	}
	
	if(~PINB & SH(buttonDown.PORTxx) ) {
		Button_press(&buttonDown);
		return;
	} else {
		Button_unPress(&buttonDown);
	}
}