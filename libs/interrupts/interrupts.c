/*
 * interrupts.c
 *
 * Created: 10/10/2020 7:06:13 PM
 *  Author: ar725
 */ 

#include "interrupts.h"

ISR(TIMER2_COMPA_vect) {
	if(textBlinkingCounter >= TEXT_BLINKING_COUNT) {
		textBlinkingFlag = !textBlinkingFlag;
		textBlinkingCounter = 0;
	}
	textBlinkingCounter++;
	
	if(LCDPrintingCounter >= LCD_PRINTING_COUNT) {
		LCDPrintingFlag = !LCDPrintingFlag;
		LCDPrintingCounter = 0;
		LedToggle(&led1);
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
	
	if(PINB & SH(buttonLeft.PORTxx) ) {
		Button_press(&buttonLeft);
		return;
	} else {
		Button_unPress(&buttonLeft);
	}
	
	if(PINB & SH(buttonLeft.PORTxx) ) {
		Button_press(&buttonLeft);
		return;
	} else {
		Button_unPress(&buttonLeft);
	}
	
	if(PINB & SH(buttonLeft.PORTxx) ) {
		Button_press(&buttonLeft);
		return;
	} else {
		Button_unPress(&buttonLeft);
	}
	
	if(PINB & SH(buttonLeft.PORTxx) ) {
		Button_press(&buttonLeft);
		return;
	} else {
		Button_unPress(&buttonLeft);
	}
}