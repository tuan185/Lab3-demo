/*
 * button.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
# define BUTTON_IS_PRESSED GPIO_PIN_RESET
# define BUTTON_IS_RELEASED GPIO_PIN_SET

void button_reading (void) ;
unsigned char is_button_pressed (unsigned char index);
unsigned char is_button_pressed_1s (unsigned char index);
void button_hold(void);
#endif /* INC_BUTTON_H_ */
