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
        // turn off all lights
        light_Off();

        // led blink
        if (timer_flag[1] == 1) {
            //TODO: Toggle 2-way LED_REDs
            setTimer(1, 500);
        }
        
        // manual amber
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
            status = MAN_AMBER;
        }

        // modify time length
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }

        break;

    case MAN_AMBER:
        // turn off all lights
        light_Off();

        // led blink
        if (timer_flag[1] == 1) {
            //TODO: Toggle 2-way LED_AMBERs
            setTimer(1, 500);
        } 

        // manual amber
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
            status = MAN_GREEN;
        }

        // modify time length
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }
        
        break;

    case MAN_GREEN:
        // turn off all lights
        light_Off();
        
        if (timer_flag[1] == 1) {
            //TODO: Toggle 2-way LED_GREENs
            setTimer(1, 500);
        }

        // manual amber
        if (isButtonPressed(2)) {
            handleButtonProcess(2);
            status = MAN_GREEN;
        }

        // modify time length
        if (isButtonPressed(3)) {
            handleButtonProcess(3);
        }
    }
}