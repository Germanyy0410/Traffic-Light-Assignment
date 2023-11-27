/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_automatic.h"

void fsm_automatic_run(void) {
    /* CHANGE TO MANUAL MODE WHEN BUTTON1 IS PRESSED */
    if (isButtonPressed(1)) {
    	status = MANUAL_MODE;
		setTimer(0, 5000);				// reuse timer 0 to 5 seconds for manual event
    }

    switch (traffic_status) {
    case INIT:
        Red_Green();
        traffic_status = RED_GREEN;

        break;

    case RED_GREEN:
        Red_Green();

        if (timer_flag[0] == 1) {
            traffic_status = RED_AMBER;
            setTimer(0, amber_counter);
        }    

        break;

    case RED_AMBER:
        Red_Amber();

        if (timer_flag[0] == 1) {
            traffic_status = GREEN_RED;
            setTimer(0, green_counter);
        }

        break;

    case GREEN_RED:
        Green_Red();

        if (timer_flag[0] == 1) {
            traffic_status = AMBER_RED;
            setTimer(0, amber_counter);
        }

        break;

    case AMBER_RED:
    	Amber_Red();

        if (timer_flag[0] == 1) {
            traffic_status = RED_GREEN;
            setTimer(0, green_counter);
        }
        break;
    }
}
