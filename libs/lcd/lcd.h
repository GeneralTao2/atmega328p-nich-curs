/*
 * lcd.h
 *
 * Created: 10/8/2020 11:14:35 PM
 *  Author: ar725
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../tools/tools.h"

#include <stdio.h>
#include <stdarg.h>

#define LCD_Port PORTD			//Define LCD Port (PORTA, PORTB, PORTC, PORTD)
#define LCD_DPin  DDRD			//Define 4-Bit Pins (PD4-PD7 at PORT D)
#define RSPIN PD0			//RS Pin
#define ENPIN PD1 			//E Pin

void LCD_Init (void);

void LCD_Action( unsigned char cmnd );

void LCD_Clear();

void LCD_Print (char *str);

void LCD_Printf(const char * format, ... );

//Write on a specific location
void LCD_Printpos (char row, char pos, char *str);



#endif /* LCD_H_ */