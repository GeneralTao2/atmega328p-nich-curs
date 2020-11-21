/*
 * nich-curs.c
 *
 * Created: 10/8/2020 10:35:10 PM
 * Author : ar725
 */ 

/*
4-Bit 16x2 LCD Example
More information at www.aeq-web.com
*/
#include <avr/interrupt.h>
#include "libs/lcd/lcd.h"
#include "libs/room/room.h"
#include "libs/timers/timers.h"
#include "libs/buttons/button.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum DivaceMode_TypeDef {
	MAIN,
	OPTIONS,
	SENSOR
} DivaceMode_TypeDef;

struct Indexes {
	volatile uint8_t currentRoom : 2;
	volatile uint8_t curentOption : 1;
	volatile uint8_t test;
} indexes;

#define ROOM_COUNT 4
Room_TypeDef rooms[ROOM_COUNT];
Led_TypeDef led1;
Led_TypeDef led_debug;

Button_TypeDef buttonLeft;
Button_TypeDef buttonRight;
Button_TypeDef buttonUp;
Button_TypeDef buttonDown;
Button_TypeDef buttonMenu;

Temperature ds_t[ROOM_COUNT];
char spaces[4] = "   ";
volatile DivaceMode_TypeDef currentMode = SENSOR;
void init_divaces(void);
void print_main(void);
void print_options(void);
void print_sensor(void);
void getSapces(char *str, int8_t tmp);

volatile uint8_t textBlinkingFlag = 0;

volatile uint8_t LCDPrintingFlag = 0;
uint8_t LCDPrintingLastFlag = 0;
uint8_t counter = 0;



int main()
{
	init_divaces();
	
	TIM1_Init();
	TIM2_Init();
	TIM2_Start();
	
	Button_init(&buttonLeft);
	Button_init(&buttonRight);
	Button_init(&buttonUp);
	Button_init(&buttonDown);
	Button_init(&buttonMenu);
	
	LedEnable(&led1);
	LedEnable(&led_debug);
	LCD_Init(); //Activate LCD
	
	indexes.currentRoom = 0;
	indexes.test = 0;
	uint8_t a;
	sei();
	LCD_Printf("Hello!");
	
	while(1) {
		//_delay_ms(1000);
		if(LCDPrintingFlag != LCDPrintingLastFlag) {
			//indexes.test++;
			LedToggle(&led_debug);
			a++;
			/*for(uint8_t i=0; i<ROOM_COUNT; i++) {
				_delay_ms(10);
				ds_t[i] = DS18B20_read_temperature(&rooms[i].ds);
			}*/
			switch(currentMode) {
				case MAIN:
				print_main();
				break;
				case OPTIONS:
				print_options();
				break;
				case SENSOR:
				print_sensor();
				break;
			}
			counter++;
		}
		LCDPrintingLastFlag = LCDPrintingFlag;
	}
}

void init_divaces(void) {
	rooms[0].ds.DDRx = &DDRC;
	rooms[0].ds.PORTx = &PORTC;
	rooms[0].ds.PINx = &PINC;
	rooms[0].ds.PORTxx = PORTC0;
	
	rooms[1].ds.DDRx = &DDRC;
	rooms[1].ds.PORTx = &PORTC;
	rooms[1].ds.PINx = &PINC;
	rooms[1].ds.PORTxx = PORTC1;
	
	rooms[2].ds.DDRx = &DDRC;
	rooms[2].ds.PORTx = &PORTC;
	rooms[2].ds.PINx = &PINC;
	rooms[2].ds.PORTxx = PORTC2;
	
	rooms[3].ds.DDRx = &DDRC;
	rooms[3].ds.PORTx = &PORTC;
	rooms[3].ds.PINx = &PINC;
	rooms[3].ds.PORTxx = PORTC3;
	
	led1.DDRx = &DDRD;
	led1.PORTx = &PORTD;
	led1.PORTxx = PORTD2;
	
	led_debug.DDRx = &DDRB;
	led_debug.PORTx = &PORTB;
	led_debug.PORTxx = PORTB5;
	
	buttonLeft.PCIEx = PCIE0;
	buttonLeft.PCMSKx = &PCMSK0;
	buttonLeft.PORTx = &PORTB;
	buttonLeft.PORTxx = PORTB0;
	
	buttonUp.PCIEx = PCIE0;
	buttonUp.PCMSKx = &PCMSK0;
	buttonUp.PORTx = &PORTB;
	buttonUp.PORTxx = PORTB1;
	
	buttonMenu.PCIEx = PCIE0;
	buttonMenu.PCMSKx = &PCMSK0;
	buttonMenu.PORTx = &PORTB;
	buttonMenu.PORTxx = PORTB2;
	
	buttonDown.PCIEx = PCIE0;
	buttonDown.PCMSKx = &PCMSK0;
	buttonDown.PORTx = &PORTB;
	buttonDown.PORTxx = PORTB3;
	
	buttonRight.PCIEx = PCIE0;
	buttonRight.PCMSKx = &PCMSK0;
	buttonRight.PORTx = &PORTB;
	buttonRight.PORTxx = PORTB4;
}
void print_main(void) {
	LCD_Action(0x01);
	getSapces(spaces, ds_t[0].digit);
	LCD_Printf("1:% d.%01u%s2:% d.%01u", ds_t[0].digit, ds_t[0].decimal, 
										   spaces,
										   ds_t[1].digit, ds_t[1].decimal);
	LCD_Action(0xC0);
	getSapces(spaces, ds_t[2].digit);
	LCD_Printf("1:% d.%01u%s2:% d.%01u", ds_t[2].digit, ds_t[2].decimal,
										   spaces,
										   ds_t[3].digit, ds_t[3].decimal);
}

void print_options(void) {
	LCD_Action(0x01);
	LCD_Printf("Control t C");
	LCD_Action(0xC0);
	LCD_Printf("Room %d", indexes.currentRoom+1);
}

void print_sensor(void) {
	LCD_Action(0x01);
	LCD_Printf("Room %d %d %d", indexes.currentRoom+1,counter, indexes.test);
	LCD_Action(0xC0);
	getSapces(spaces, rooms->min_temp);
	if(indexes.curentOption) {
		if(textBlinkingFlag) {
			LCD_Printf("Min:    %sMax:% d",	spaces,
											rooms->max_temp);
		} else {
			LCD_Printf("Min:% d%sMax:% d",	rooms->min_temp,
											spaces,
											rooms->max_temp);
		}
	} else {
		if(textBlinkingFlag) {
			LCD_Printf("Min:% d%sMax:% d",	rooms->min_temp,
											spaces,
											rooms->max_temp);
			} else {
			LCD_Printf("Min:% d%sMax:     ",	rooms->min_temp,
												spaces);
		}
	}
	
}

void getSapces(char *str, int8_t tmp) {
	str[0] = ' ';
	str[1] = ' ';
	str[2] = ' ';
	int8_t tmp_abs = abs(tmp);
	if(tmp_abs > 9 && tmp_abs < 100) {
		str[2] = '\0';
	} else if(tmp_abs > 99) {
		str[1] = '\0';
	}
}



/*ISR(ADC_vect) {
	ADC_values[ADC_input_index] = ADC;
	if( ++ADC_input_index >= ADC_COUNT ) {
		ADC_input_index = 0;
	}
	ADMUX = (1 << REFS0) | ADC_input_index;
	ADC_StartConversion();
}*/
