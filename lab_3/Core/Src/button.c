/*
 * button.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Admin
 */

/*
 * button.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Admin
 */
#include "button.h"

// we aim to work with more than one buttons
# define N0_OF_BUTTONS 3
// timer interrupt duration is 10ms , so to pass 1 second ,
// we need to jump to the interrupt service routine 100 time
# define DURATION_FOR_AUTO_INCREASING 100

// the buffer that the final result is stored after
// debouncing

uint16_t buttons_pin[N0_OF_BUTTONS] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN};
GPIO_TypeDef* buttons_port[N0_OF_BUTTONS] = {BUTTON_1_PORT, BUTTON_2_PORT, BUTTON_3_PORT};

static GPIO_PinState buttonBuffer [N0_OF_BUTTONS];
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1 [N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2 [N0_OF_BUTTONS];
// we define a flag for a button pressed more than 1 second .
static uint8_t flagForButtonPress1s [N0_OF_BUTTONS];
// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
static uint16_t counterForButtonPress1s [N0_OF_BUTTONS];
static uint8_t preCalled[N0_OF_BUTTONS];
void button_reading (void) {
	for (uint8_t i = 0; i < N0_OF_BUTTONS; i ++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin (buttons_port[i] , buttons_pin[i]);
		if( debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
		buttonBuffer[i] = debounceButtonBuffer1[i];
		if( buttonBuffer[i] == BUTTON_IS_PRESSED ) {
		// if a button is pressed , we start counting
		if( counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING ) {
		counterForButtonPress1s[i]++;
		} else {
		// the flag is turned on when 1 second has passed
		// since the button is pressed .
		flagForButtonPress1s[i] = 1;
		}
		} else {
		counterForButtonPress1s[i] = 0;
		flagForButtonPress1s[i] = 0;
		}
	}
}

unsigned char is_button_pressed (unsigned char index){
	if(index > N0_OF_BUTTONS) return 0;
	if(preCalled[index] == buttonBuffer[index]){
		return BUTTON_IS_RELEASED;
	}
	preCalled[index] = buttonBuffer[index];
	return buttonBuffer[index];
}

unsigned char is_button_pressed_1s (unsigned char index){
	if(index > N0_OF_BUTTONS) return 0;
	return (flagForButtonPress1s[index] == BUTTON_IS_PRESSED);
};

