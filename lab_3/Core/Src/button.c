#include "button.h"


static int KeyReg0[NO_OF_BUTTONS];
static int KeyReg1[NO_OF_BUTTONS];
static int KeyReg2[NO_OF_BUTTONS];
static int KeyReg3[NO_OF_BUTTONS];
static GPIO_TypeDef* BUTTON_PORT[NO_OF_BUTTONS] = {BUTTON_1_PORT, BUTTON_2_PORT, BUTTON_3_PORT};
static uint16_t BUTTON_PIN[NO_OF_BUTTONS] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN};
static int TimeOutForKeyPress[NO_OF_BUTTONS];
static int button_flag[NO_OF_BUTTONS];


void buttonInit(){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		KeyReg0[i] = NORMAL_STATE;
		KeyReg1[i] = NORMAL_STATE;
		KeyReg2[i] = NORMAL_STATE;
		KeyReg3[i] = NORMAL_STATE;

		TimeOutForKeyPress[i] =  500;
		button_flag[i] = 0;
	}
}

int isButtonPressed(int index){
	if(index >= NO_OF_BUTTONS){
		return NORMAL_STATE;
	}
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return PRESSED_STATE;
	}
	return NORMAL_STATE;
}

void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput(){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		//Add your button here
		KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
		if (KeyReg2[i] != KeyReg3[i]){
		  KeyReg3[i] = KeyReg2[i];

		  if (KeyReg3[i] == PRESSED_STATE){
			TimeOutForKeyPress[i] = 500;
			subKeyProcess(i);
		  }
		}else{
		   TimeOutForKeyPress[i] --;
			if (TimeOutForKeyPress[i] == 0){
				TimeOutForKeyPress[i] = 500;
				subKeyProcess(i);
			}
		}
		}
	}

}

