/*
 * button.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define NO_BUTTONS 3

extern int button_flag[NO_BUTTONS + 1];

void initButton();
void getOneKeyInput(int buttonNo, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void getKeyInput();
void subKeyProcess(int);
int isButtonPressed(int);
    
#endif /* INC_BUTTON_H_ */
