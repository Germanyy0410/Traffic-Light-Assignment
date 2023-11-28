/*
 * fsm_tuning.c
 *
 *  Created on: Nov 28, 2023
 *      Author: ASUS
 */

#include "fsm_tuning.h"

void fsm_tuning_run(void) {
	switch (traffic_status) {
	case MAN_RED:
		time_modify_counter = red_counter;

		if (time_modify_counter == MAX_TIME) {
			time_modify_counter = 0;
		} else {
			time_modify_counter += UPDATED_TIME;
		}

		status = MANUAL_MODE;
		break;

	case MAN_AMBER:
		time_modify_counter = amber_counter;

		if (time_modify_counter == MAX_TIME) {
			time_modify_counter = 0;
		} else {
			time_modify_counter += UPDATED_TIME;
		}

		status = MANUAL_MODE;
		break;

	case MAN_GREEN:
		time_modify_counter = green_counter;

		if (time_modify_counter == MAX_TIME) {
			time_modify_counter = 0;
		} else {
			time_modify_counter += UPDATED_TIME;
		}

		status = MANUAL_MODE;
		break;

	default:
		break;
	}
}
