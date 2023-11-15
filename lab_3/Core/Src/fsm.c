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

static enum MainMode{INIT, MODE_1, MODE_2, MODE_3};
static enum MainMode mode = INIT;

static int time_1 = 0;
static int time_2 = 0;

static uint8_t led7state = 0;

void resetLED(){
	HAL_GPIO_WritePin(GREEN_1_PORT, GREEN_1_PIN, RESET);
	HAL_GPIO_WritePin(GREEN_2_PORT, GREEN_2_PIN, RESET);
	HAL_GPIO_WritePin(YELLOW_1_PORT, YELLOW_1_PIN, RESET);
	HAL_GPIO_WritePin(YELLOW_2_PORT, YELLOW_2_PIN, RESET);
	HAL_GPIO_WritePin(RED_1_PORT, RED_1_PIN, RESET);
	HAL_GPIO_WritePin(RED_2_PORT, RED_2_PIN, RESET);
}


void fsm_mode(void){
	switch (mode){
	case INIT:
		resetLED();
		mode = MODE_1;
		trafficstate = GREEN_1;
		time_1 = green_counter;
		time_2 = red_counter;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		break;
	case MODE_1:
		mode_1();
		if(isButtonPressed(1) == PRESSED_STATE){
			resetLED();
			mode = MODE_2;
		}
		break;
	case MODE_2:
		configTime(0);
		if(isButtonPressed(2) == PRESSED_STATE){
			resetLED();
			mode = MODE_3;
		}
		break;
	case MODE_3:
		configTime(1);
		if(isButtonPressed(2) == PRESSED_STATE){
			resetLED();
			mode = INIT;
		}
		break;
	}
	if(isButtonPressed(0) == PRESSED_STATE){
		mode = INIT;
	}
}


void mode_1(void){
	switch (trafficstate){
		case GREEN_1:
			HAL_GPIO_WritePin(YELLOW_2_PORT, YELLOW_2_PIN, RESET);
			HAL_GPIO_WritePin(RED_1_PORT, RED_1_PIN, RESET);
			HAL_GPIO_WritePin(GREEN_1_PORT, GREEN_1_PIN, SET);
			HAL_GPIO_WritePin(RED_2_PORT, RED_2_PIN, SET);
			if(time_1 <= 0){
				trafficstate = YELLOW_1;
				time_1 = red_counter-green_counter;
			}
			break;
		case YELLOW_1:
			HAL_GPIO_WritePin(GREEN_1_PORT, GREEN_1_PIN, RESET);
			HAL_GPIO_WritePin(YELLOW_1_PORT, YELLOW_1_PIN, SET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = GREEN_2;
				time_1 = red_counter;
				time_2 = green_counter;
			}
			break;
		case GREEN_2:
			HAL_GPIO_WritePin(YELLOW_1_PORT, YELLOW_1_PIN, RESET);
			HAL_GPIO_WritePin(RED_1_PORT, RED_2_PIN, RESET);
			HAL_GPIO_WritePin(GREEN_2_PORT, GREEN_2_PIN, SET);
			HAL_GPIO_WritePin(RED_1_PORT, RED_1_PIN, SET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = YELLOW_2;
				time_2 = red_counter-green_counter;
			}
			break;
		case YELLOW_2:
			HAL_GPIO_WritePin(GREEN_2_PORT, GREEN_2_PIN, RESET);
			HAL_GPIO_WritePin(YELLOW_2_PORT, YELLOW_2_PIN, SET);
			if(time_1 <= 0 || time_2 <= 0){
				trafficstate = GREEN_1;
				time_1 = green_counter;
				time_2 = red_counter;
			}
			break;
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


void configTime(int color){
	switch(color){
	case 0: 		//config time for red
		if(getTimerFlag(1)){
			HAL_GPIO_TogglePin(RED_1_PORT, RED_1_PIN);
			HAL_GPIO_TogglePin(RED_2_PORT, RED_2_PIN);
			setLEDTimer(250);
		}
		if(getTimerFlag(0)){
			led7state++;
			if(led7state > 3){
				led7state = 0;
			}
			control7SEG(led7state, red_counter, red_counter);
			set7SEGTimer(250);
		}
		if(isButtonPressed(1) == PRESSED_STATE){
			red_counter++;
			if(red_counter == 100) red_counter = 0;
		}
		break;
	case 1:			//config time for green
		if(getTimerFlag(1)){
			HAL_GPIO_TogglePin(GREEN_1_PORT, GREEN_1_PIN);
			HAL_GPIO_TogglePin(GREEN_2_PORT, GREEN_2_PIN);
			setLEDTimer(250);
		}
		if(getTimerFlag(0)){
			led7state++;
			if(led7state > 3){
				led7state = 0;
			}
			control7SEG(led7state, green_counter, green_counter);
			set7SEGTimer(250);
		}
		if(isButtonPressed(1) == PRESSED_STATE){
			green_counter++;
			if(green_counter == 100) green_counter = 0;
		}
		break;
	default:
		break;
	}
}


