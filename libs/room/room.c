/*
 * room.c
 *
 * Created: 10/9/2020 9:45:38 PM
 *  Author: ar725
 */ 
#include "room.h"

inline void Room_maxTempUp(Room_TypeDef *room) {
	if(room->max_temp >= DS18B20_MAX_TEMP - 1) {
		return;
	}
	room->max_temp++;
}
inline void Room_maxTempDown(Room_TypeDef *room) {
	if(room->max_temp <= DS18B20_MIN_TEMP) {
		return;
	}
	room->max_temp--;
}

inline void Room_minTempUp(Room_TypeDef *room) {
	if(room->min_temp >= DS18B20_MAX_TEMP - 1) {
		return;
	}
	room->min_temp++;
}

inline void Room_minTempDown(Room_TypeDef *room) {
	if(room->min_temp <= DS18B20_MIN_TEMP) {
		return;
	}
	room->min_temp--;
}

void Room_TempInit(Room_TypeDef *room, int8_t min, int8_t max) {
	room->min_temp = min;
	room->max_temp = max;
}

void Room_TempInitFromEEPROM(Room_TypeDef *room, uint8_t serialNumber) {
	uint8_t adress = serialNumber*2;
	Room_TempInit(room, eeprom_read_byte((const uint8_t*)adress), 
						eeprom_read_byte((const uint8_t*)(adress+1)));
}

void Room_TempSaveToEEPROM(Room_TypeDef *room, uint8_t serialNumber) {
	uint8_t adress = serialNumber*2;
	eeprom_write_byte((const uint8_t*)adress, (uint8_t)room->min_temp);
	eeprom_write_byte((const uint8_t*)(adress+1), (uint8_t)room->max_temp);
}