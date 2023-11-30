/*
 * led_display.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "led_display.h"

void fsm_mode() {
	switch (status) {
	    case INIT:
	        status = AUTOMATIC_MODE;
	        break;

	    case AUTOMATIC_MODE:
	        fsm_automatic_run();
	        fsm_pedestrian_run();
	        fsm_buzzer_run();

	        break;

	    case MANUAL_MODE:
	        fsm_manual_run();
	        break;

	    case TUNING_MODE:
	        fsm_tuning_run();
	        break;

	    default:
	        break;
	    }
}

void send7SEG(void) {
    
}
