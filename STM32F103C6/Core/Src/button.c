/*
 * button.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "button.h"

int KeyReg0[NO_BUTTONS + 1];
int KeyReg1[NO_BUTTONS + 1];
int KeyReg2[NO_BUTTONS + 1];
int KeyReg3[NO_BUTTONS + 1];

int button_flag[NO_BUTTONS + 1];
int TimerForKeyPress[NO_BUTTONS + 1];

int Button1PressCounter = 1;    /* INITIALLY, MODE = 1 */

void initButton() {
	for (int i = 1; i <= NO_BUTTONS; i++) {
		KeyReg0[i] = NORMAL_STATE;
		KeyReg1[i] = NORMAL_STATE;
		KeyReg2[i] = NORMAL_STATE;
		KeyReg3[i] = NORMAL_STATE; 
		button_flag[i] = 0;
		TimerForKeyPress[i] = 200;
	}
}

void getKeyInput() {
    for (int i = 1; i <= NO_BUTTONS; i++) {
        KeyReg0[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg2[i];

        if (i == 1) KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
        if (i == 2) KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_2_1_GPIO_Port, BUTTON_2_1_Pin);
        if (i == 3) KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
        if (i == 4) KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_PEDESTRIAN_GPIO_Port, BUTTON_PEDESTRIAN_Pin);

        if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg3[i] != KeyReg2[i]) {
                KeyReg3[i] = KeyReg2[i];

                if (KeyReg2[i] == PRESSED_STATE) {
                    subKeyProcess(i);
                    TimerForKeyPress[i] = 200;
                }
            } else {
                TimerForKeyPress[i]--;
                if (TimerForKeyPress[i] == 0) {
                    if (KeyReg2[i] == PRESSED_STATE) {
                        subKeyProcess(i);
                    }

                    TimerForKeyPress[i] = 200;
                }
            }
        }
    }
}

int isButtonPressed(int index) {
//	if (index > NO_BUTTONS)
//		return 0;

	if (button_flag[index]) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index) {
	button_flag[index] = 1;
}
