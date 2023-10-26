/*
 * timer.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Admin
 */
#include "main.h"

static int timer7SEG_counter = 0;
static int timer7SEG_flag = 0;
static int TIMER_CYCLE = 10;
static int timerLEDBlink_counter = 0;
static int timerLEDBlink_flag = 0;
void timerInit(int scale, int period){
	TIMER_CYCLE = ((scale+1)*(period+1))/8000;
};

int getTimerFlag(int flag){
	if(flag == 0){
		return timer7SEG_flag;
	}else if(flag == 1){
		return timerLEDBlink_flag;
	}
	return 0;
};

void set7SEGTimer(int duration){
	timer7SEG_counter = duration / TIMER_CYCLE;
	timer7SEG_flag = 0;
}

void setLEDBlinkTimer(int duration){
	timerLEDBlink_counter = duration / TIMER_CYCLE;
	timerLEDBlink_flag = 0;
}

void timer_run(){
	if(timer7SEG_counter > 0){
		timer7SEG_counter--;
		if(timer7SEG_counter == 0) timer7SEG_flag = 1;
	}
	if(timerLEDBlink_counter > 0){
		timerLEDBlink_counter--;
		if(timerLEDBlink_counter == 0) timerLEDBlink_flag = 1;
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	timer_run();
}
