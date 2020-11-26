/*
 * room.h
 *
 * Created: 10/9/2020 9:45:27 PM
 *  Author: ar725
 */ 


#ifndef ROOM_H_
#define ROOM_H_
#include "../DS18B20/DS18B20.h"
#include "../led/led.h"
#include <avr/eeprom.h>

typedef struct Room_TypeDef {
	DS18B20_TypeDef ds;
	int8_t max_temp;
	int8_t min_temp;
} Room_TypeDef;

void Room_maxTempUp(Room_TypeDef *room);
void Room_maxTempDown(Room_TypeDef *room);
void Room_minTempUp(Room_TypeDef *room);
void Room_minTempDown(Room_TypeDef *room);
void Room_TempInit(Room_TypeDef *room, int8_t min, int8_t max);
void Room_TempInitFromEEPROM(Room_TypeDef *room, uint8_t serialNumber);
void Room_TempSaveToEEPROM(Room_TypeDef *room, uint8_t serialNumber);


#endif /* ROOM_H_ */