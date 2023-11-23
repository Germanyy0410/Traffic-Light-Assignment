/*
 * fsm_manual.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_manual.h"

void fsm_manual_run(void) {
    switch (status) {
    case MAN_RED:
        /* TURN OFF LIGHTS */
        light_Off();
        setTimer(1, 500);

        /* BLINK LEDs */
        if (timer_flag[1] == 1) {
            HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
            HAL_GPIO_TogglePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin);
            setTimer(1, 500);
        }
        
        /* CHANGE MODE = 3 (MAN_AMBER) WHEN BUTTON1 IS PRESSED */
        if (isButtonPressed(1)) {
            handleButtonProcess(1);
        }
    
        /* MODIFY TIME LENGTH */
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
        }

        /* CONFIRM TIME LENGTH */
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }

        break;

    case MAN_AMBER:
        /* TURN OFF LIGHTS */
        light_Off();
        setTimer(1, 500);

        /* BLINK LEDs */
        if (timer_flag[1] == 1) {
            HAL_GPIO_TogglePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin);
            HAL_GPIO_TogglePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin);
            setTimer(1, 500);
        } 

        /* CHANGE MODE = 4 (MAN_GREEN) WHEN BUTTON1 IS PRESSED */
        if (isButtonPressed(1)) {
            handleButtonProcess(1);
        }

        /* MODIFY TIME LENGTH */
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
        }

        /* CONFIRM TIME LENGTH */
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }
        
        break;

    case MAN_GREEN:
        /* TURN OFF LIGHTS */
        light_Off();
        setTimer(1, 500);

        /* BLINK LEDs */
        if (timer_flag[1] == 1) {
            HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
            HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin); 
            setTimer(1, 500);
        }

        /* CHANGE MODE = 1 (AUTOMATIC) WHEN BUTTON1 IS PRESSED */
        if (isButtonPressed(1)) {
            handleButtonProcess(1);
        }

        /* MODIFY TIME LENGTH */
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
        }

        /* CONFIRM TIME LENGTH */
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }
    }
}