/*
 * fsm_manual.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_manual.h"

void fsm_manual_run(void) {
	switch (traffic_status) {
	case MAN_RED:
		/* TURN OFF LIGHTS */

		/* BLINK LEDs */
		if (timer_flag[1] == 1) {
			Toggle_Red();
			setTimer(1, 500);
		}

		/* OUT OF TIME FOR MANUAL EVENTS */
		if (timer_flag[0] == 1) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		/* CHANGE MODE = 3 (MAN_AMBER) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_AMBER;
			setTimer(0, 5000);	// reuse timer 0 to 5 seconds for manual event
		}

		/* MODIFY TIME LENGTH */
		if (isButtonPressed(2)) {
			status = TUNING_MODE;
		}

		/* CONFIRM TIME LENGTH */
		if (isButtonPressed(3)) {
			red_counter = time_modify_counter;
			green_counter = red_counter - amber_counter;
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		break;

	case MAN_AMBER:
		/* TURN OFF LIGHTS */

		/* BLINK LEDs */
		if (timer_flag[1] == 1) {
			Toggle_Amber();
			setTimer(1, 500);
		}

		/* OUT OF TIME FOR MANUAL EVENTS */
		if (timer_flag[0] == 1) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		/* CHANGE MODE = 4 (MAN_GREEN) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_GREEN;
			setTimer(0, 5000);	// reuse timer 0 to 5 seconds for manual event
		}

		/* MODIFY TIME LENGTH */
		if (isButtonPressed(2)) {
			status = TUNING_MODE;
		}

		/* CONFIRM TIME LENGTH */
		if (isButtonPressed(3)) {
			amber_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		break;

	case MAN_GREEN:
		/* TURN OFF LIGHTS */

		/* BLINK LEDs */
		if (timer_flag[1] == 1) {
			Toggle_Green();
			setTimer(1, 500);
		}

		/* OUT OF TIME FOR MANUAL EVENTS */
		if (timer_flag[0] == 1) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		/* CHANGE MODE = 1 (AUTOMATIC) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		/* MODIFY TIME LENGTH */
		if (isButtonPressed(2)) {
			status = TUNING_MODE;
		}

		/* CONFIRM TIME LENGTH */
		if (isButtonPressed(3)) {
			green_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}
		break;
	default: // change traffic state to MAN_RED when change from AUTOMATIC to MANUAL
		traffic_status = MAN_RED;
		break;
	}
}
