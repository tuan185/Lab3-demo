/*
 * fsm.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Admin
 */
#include "fsm.h"

static uint8_t red_counter = 10;
static uint8_t green_counter = 8;

static enum TrafficState{GREEN_1, YELLOW_1, GREEN_2, YELLOW_2};
static enum TrafficState trafficstate = GREEN_1;

static int time_1 = 0;
static int time_2 = 0;


static uint8_t led7state = 0;
void mode_1(void){
	if(time_1 <= 0 || time_2 <= 0){
		switch (trafficstate){
			case GREEN_1:
				HAL_GPIO_WritePin(YELLOW_2_PORT, YELLOW_2_PIN, RESET);
				HAL_GPIO_WritePin(RED_1_PORT, RED_1_PIN, RESET);
				HAL_GPIO_WritePin(GREEN_1_PORT, GREEN_1_PIN, SET);
				HAL_GPIO_WritePin(RED_2_PORT, RED_2_PIN, SET);
				trafficstate = YELLOW_1;
				time_1 = green_counter;
				time_2 = red_counter;
				//setTrafficTimer(green_counter);
				break;
			case YELLOW_1:
				HAL_GPIO_WritePin(GREEN_1_PORT, GREEN_1_PIN, RESET);
				HAL_GPIO_WritePin(YELLOW_1_PORT, YELLOW_1_PIN, SET);
				trafficstate = GREEN_2;
				time_1 = red_counter-green_counter;
				//setTrafficTimer(red_counter-green_counter);
				break;
			case GREEN_2:
				HAL_GPIO_WritePin(YELLOW_1_PORT, YELLOW_1_PIN, RESET);
				HAL_GPIO_WritePin(RED_1_PORT, RED_2_PIN, RESET);
				HAL_GPIO_WritePin(GREEN_2_PORT, GREEN_2_PIN, SET);
				HAL_GPIO_WritePin(RED_1_PORT, RED_1_PIN, SET);
				trafficstate = YELLOW_2;
				time_1 = red_counter;
				time_2 = green_counter;
				//setTrafficTimer(green_counter);
				break;
			case YELLOW_2:
				HAL_GPIO_WritePin(GREEN_2_PORT, GREEN_2_PIN, RESET);
				HAL_GPIO_WritePin(YELLOW_2_PORT, YELLOW_2_PIN, SET);
				trafficstate = GREEN_1;
				time_2 = red_counter-green_counter;
				//setTrafficTimer(yellow_counter);
				break;
		}
	}
	if(getTimerFlag(0)){
		control7SEG(led7state, time_1, time_2);
		led7state++;
		if(led7state > 3){
			led7state = 0;
			time_1--;
			time_2--;
		}
		set7SEGTimer(250);
	}
}

static enum TrafficConfigTime{RED_TIME, GREEN_TIME};
static enum TrafficConfigTime timeMode = RED_TIME;
void mode_2(void){
	switch(timeMode){
	case RED_TIME:
		setLEDBlinkTimer(250);
		set7SEGTimer(250);
		if(getTimerFlag(1)){
			HAL_GPIO_TogglePin(RED_1_PORT, RED_1_PIN);
			HAL_GPIO_TogglePin(RED_2_PORT, RED_2_PIN);
			setLEDBlinkTimer(250);
		}
		if(getTimerFlag(0)){
			control7SEG(led7state, red_counter, green_counter);
			led7state++;
			if(led7state > 3){
				led7state = 0;
			}
			set7SEGTimer(250);
		}

		break;
	case GREEN_TIME:
		break;
	}
}
