/*
 * ADC_manager.h
 *
 * Created: 10.06.2020 21:33:30
 *  Author: ar725
 */ 
#ifndef ADC_MANAGER_H_
#define ADC_MANAGER_H_

#include "../tools/tools.h"

#define ADC_COUNT 6
#define INIT_VAL 512

static uint16_t ADC_values[ADC_COUNT] = {INIT_VAL, INIT_VAL, INIT_VAL, INIT_VAL, INIT_VAL, INIT_VAL};
static uint8_t ADC_input_index = 0;

#define SN_TEMPERATURE_VAL ADC_values[2]

void ADC_Init();
void ADC_StartConversion();
uint8_t ADC_GetVal(uint8_t i);





#endif /* ADC_MANAGER_H_ */