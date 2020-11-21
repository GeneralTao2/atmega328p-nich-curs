/*
 * timers.h
 *
 * Created: 10.06.2020 12:51:30
 *  Author: ar725
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "../tools/tools.h"

#define TIM1_OCRA 1
#define TIM1_EXTRA_DELAY 100
static volatile uint16_t TIM1_extraTime = 0;
void TIM1_Init();
void TIM1_Start();
void TIM1_Stop();

#define TIM2_OCRA 125

void TIM2_Init();
void TIM2_Start();
void TIM2_Stop();




#endif /* TIMERS_H_ */