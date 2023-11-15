/*
 * LED_control.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Admin
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_
#include "main.h"
void clearAllLED();
void display7SEG(uint8_t num);
void enable7SEG(uint8_t index);
void control7SEG(uint8_t led7state, uint8_t sec_1, uint8_t sec_2);
#endif /* INC_LED_CONTROL_H_ */
