/*
 * LED_control.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Admin
 */
#include "LED_control.h"

uint8_t LED[10] = {0x3F,		//decode for 0
				0x06, 			//decode for 1
				0x5B, 			//decode for 2
				0x4F, 			//decode for 3
				0x66, 			//decode for 4
				0x6D, 			//decode for 5
				0x7D, 			//decode for 6
				0x07, 			//decode for 7
				0x7F, 			//decode for 8
				0x6F};			//decode for 9

void display7SEG(uint8_t num){
	HAL_GPIO_WritePin(SEG_PORT, SEG_A_PIN, !((LED[num]>>0)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_B_PIN, !((LED[num]>>1)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_C_PIN, !((LED[num]>>2)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_D_PIN, !((LED[num]>>3)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_E_PIN, !((LED[num]>>4)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_F_PIN, !((LED[num]>>5)&0x01));
	HAL_GPIO_WritePin(SEG_PORT, SEG_G_PIN, !((LED[num]>>6)&0x01));
}

void clearAllLED(){
	HAL_GPIO_WritePin(SEG_EN_1_PORT, SEG_EN_1_PIN, SET);
	HAL_GPIO_WritePin(SEG_EN_2_PORT, SEG_EN_2_PIN, SET);
	HAL_GPIO_WritePin(SEG_EN_3_PORT, SEG_EN_3_PIN, SET);
	HAL_GPIO_WritePin(SEG_EN_4_PORT, SEG_EN_4_PIN, SET);

}

void control7SEG(uint8_t led7state, uint8_t sec_1, uint8_t sec_2){
	clearAllLED();
	switch(led7state){
	case 0:
		display7SEG(sec_1/10);
		HAL_GPIO_WritePin(SEG_EN_1_PORT, SEG_EN_1_PIN, RESET);
		break;
	case 1:
		display7SEG(sec_1%10);
		HAL_GPIO_WritePin(SEG_EN_2_PORT, SEG_EN_2_PIN, RESET);
		break;
	case 2:
		display7SEG(sec_2/10);
		HAL_GPIO_WritePin(SEG_EN_3_PORT, SEG_EN_3_PIN, RESET);
		break;
	case 3:
		display7SEG(sec_2%10);
		HAL_GPIO_WritePin(SEG_EN_4_PORT, SEG_EN_4_PIN, RESET);
		break;
	}
};

