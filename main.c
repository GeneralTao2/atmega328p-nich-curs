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

#include <avr/eeprom.h>


volatile uint8_t counter1 = 0;

typedef enum DivaceMode_TypeDef {
	MAIN = 0,
	OPTIONS,
	SENSOR
} DivaceMode_TypeDef;

volatile DivaceMode_TypeDef currentMode = MAIN;

volatile uint8_t currentRoom = 0;
void CurrentRoomNext() {
	if(currentRoom == 0) {
		currentRoom = 1;
	} else if(currentRoom == 4) {
		currentRoom = 1;
	} else {
		currentRoom++;
	}

}
void CurrentRoomPrev() {
	if(currentRoom == 0) {
		currentRoom = 4;
	} else if(currentRoom == 1) {
		currentRoom = 4;
		} else {
		currentRoom--;
	}
}

volatile uint8_t currentOption = 0;
void CurrentOptionToggle() {
	currentOption = !currentOption;
}




#define ROOM_COUNT 4
Room_TypeDef rooms[ROOM_COUNT];
Led_TypeDef leds[ROOM_COUNT];
Led_TypeDef led_debug;

Button_TypeDef buttonLeft;
Button_TypeDef buttonRight;
Button_TypeDef buttonUp;
Button_TypeDef buttonDown;
Button_TypeDef buttonMenu;

Temperature ds_t[ROOM_COUNT];
char spaces[4] = "   ";

void init_divaces(void);
void print_main(void);
void print_options(void);
void print_sensor(void);
void getSapces(char *str, int8_t tmp);

volatile uint8_t textBlinkingFlag = 0;

volatile uint8_t LCDPrintingFlag = 0;
uint8_t LCDPrintingLastFlag = 0;
uint8_t counter = 0;

uint8_t templateDrowingMode = 1;

void onClickMenuButton() {
	if(currentMode == MAIN) {
		templateDrowingMode = 1;
		currentRoom = 0;
		currentMode = OPTIONS;
	} else if(currentMode == SENSOR) {
		Room_TempSaveToEEPROM(&rooms[currentRoom-1], currentRoom-1);
		templateDrowingMode = 1;
		currentMode = OPTIONS;
	} else if(currentMode == OPTIONS) {
		templateDrowingMode = 1;
		currentMode = MAIN;
	}
}

void onClickLeftButton() {
	if(currentMode == OPTIONS) {
		currentMode = SENSOR;
		templateDrowingMode = 1;
		currentOption = 0;
	}
	CurrentOptionToggle();
}

void onClickRightButton() {
	if(currentMode == OPTIONS) {
		currentMode = SENSOR;
		templateDrowingMode = 1;
		currentOption = 0;
	}
}

void onClickUpButton() {
	if(currentMode == OPTIONS) {
		CurrentRoomNext();
		templateDrowingMode = 1;
	}
	if(currentMode == SENSOR) {
		if(currentOption) {
			Room_minTempUp(&rooms[currentRoom-1]);
		} else {
			Room_maxTempUp(&rooms[currentRoom-1]);
		}
	}
	counter1++;
}

void onClickDownButton() {
	if(currentMode == OPTIONS) {
		CurrentRoomPrev();
		templateDrowingMode = 1;
	}
	if(currentMode == SENSOR) {
		if(currentOption) {
			Room_minTempDown(&rooms[currentRoom-1]);
		} else {
			Room_maxTempDown(&rooms[currentRoom-1]);
		}
	}
}

void Rooms_InitFromEEROM(void) {
	for(uint8_t i=0; i<4; i++) {
		Room_TempInitFromEEPROM(&rooms[i], i);
	}
}



void CompareTemeperatures() {
	for(uint8_t i=0; i<ROOM_COUNT; i++) {
		if(ds_t[i].digit < rooms[i].min_temp) {
			LedOn(&leds[i]);
		}
		if(ds_t[i].digit > rooms[i].max_temp) {
			LedOff(&leds[i]);
		}
	}
}

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
	
	for(uint8_t i=0; i<ROOM_COUNT; i++) {
		LedEnable(&leds[i]);
	}
	LedEnable(&led_debug);
	LCD_Init(); //Activate LCD
	
	sei();
	
	eeprom_write_byte(0x01, 68);
	uint8_t a = eeprom_read_byte(0x01);
	LCD_Printf("Hello, %d!", a);
	Rooms_InitFromEEROM();
	while(1) {
		if(LCDPrintingFlag != LCDPrintingLastFlag) {
			LedToggle(&led_debug);
			for(uint8_t i=0; i<ROOM_COUNT; i++) {
				_delay_ms(10);
				ds_t[i] = DS18B20_read_temperature(&rooms[i].ds);
			}
			CompareTemeperatures();
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
	
	leds[0].DDRx = &DDRD;
	leds[0].PORTx = &PORTD;
	leds[0].PORTxx = PORTD2;
	
	leds[1].DDRx = &DDRD;
	leds[1].PORTx = &PORTD;
	leds[1].PORTxx = PORTD3;
	
	leds[2].DDRx = &DDRC;
	leds[2].PORTx = &PORTC;
	leds[2].PORTxx = PORTC4;
	
	leds[3].DDRx = &DDRC;
	leds[3].PORTx = &PORTC;
	leds[3].PORTxx = PORTC5;
	
	led_debug.DDRx = &DDRB;
	led_debug.PORTx = &PORTB;
	led_debug.PORTxx = PORTB5;
	
	buttonLeft.PCIEx = PCIE0;
	buttonLeft.PCMSKx = &PCMSK0;
	buttonLeft.PORTx = &PORTB;
	buttonLeft.PORTxx = PORTB0;
	buttonLeft.onClick = onClickLeftButton;
	
	buttonUp.PCIEx = PCIE0;
	buttonUp.PCMSKx = &PCMSK0;
	buttonUp.PORTx = &PORTB;
	buttonUp.PORTxx = PORTB1;
	buttonUp.onClick = onClickUpButton;
	
	buttonMenu.PCIEx = PCIE0;
	buttonMenu.PCMSKx = &PCMSK0;
	buttonMenu.PORTx = &PORTB;
	buttonMenu.PORTxx = PORTB2;
	buttonMenu.onClick = onClickMenuButton;
	
	buttonDown.PCIEx = PCIE0;
	buttonDown.PCMSKx = &PCMSK0;
	buttonDown.PORTx = &PORTB;
	buttonDown.PORTxx = PORTB3;
	buttonDown.onClick = onClickDownButton;
	
	buttonRight.PCIEx = PCIE0;
	buttonRight.PCMSKx = &PCMSK0;
	buttonRight.PORTx = &PORTB;
	buttonRight.PORTxx = PORTB4;
	buttonRight.onClick = onClickRightButton;
}
void print_main(void) {
	if(templateDrowingMode) {
		LCD_Action(0x01);
		LCD_Printf("1:       2:");
		LCD_Action(0xC0);
		LCD_Printf("3:       4:");
		templateDrowingMode = 0;
	}
	LCD_Action(0x82);
	LCD_Printf("% d.%01u", ds_t[0].digit, ds_t[0].decimal);
	LCD_Action(0x8B);
	LCD_Printf("% d.%01u", ds_t[1].digit, ds_t[1].decimal);
		
	LCD_Action(0xC2);
	LCD_Printf("% d.%01u", ds_t[2].digit, ds_t[2].decimal);
	LCD_Action(0xCB);
	LCD_Printf("% d.%01u", ds_t[3].digit, ds_t[3].decimal);
	

}

void print_options(void) {
	if(currentRoom == 0) {
		if(templateDrowingMode) {
			LCD_Action(0x01);
			LCD_Printf("Main menu");
			LCD_Action(0xC0);
			LCD_Printf("Control t C");
			templateDrowingMode = 0;
		}
	} else {
		if(templateDrowingMode) {
			LCD_Action(0x01);
			LCD_Printf("Control t C");
			LCD_Action(0xC0);
			LCD_Printf("Room");
			templateDrowingMode = 0;
		}
		LCD_Action(0xC5);
		LCD_Printf("%d", currentRoom);
	}
}

void print_sensor(void) {
	if(templateDrowingMode) {
		LCD_Action(0x01);
		LCD_Printf("Room %d", currentRoom);
		LCD_Action(0xC0);
		LCD_Printf("Min:     Max:");
		templateDrowingMode = 0;
	}
	if(currentOption == 1) {
		LCD_Action(0xC4);
		if(textBlinkingFlag) {
			LCD_Printf("     ");
			} else {
			LCD_Printf("% d", rooms[currentRoom-1].min_temp);
		}
		LCD_Action(0xCD);
		LCD_Printf("% d", rooms[currentRoom-1].max_temp);
		} else {
		LCD_Action(0xC4);
		LCD_Printf("% d", rooms[currentRoom-1].min_temp);
		LCD_Action(0xCD);
		if(textBlinkingFlag) {
			LCD_Printf("     ");
			} else {
			LCD_Printf("% d", rooms[currentRoom-1].max_temp);
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

