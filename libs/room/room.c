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