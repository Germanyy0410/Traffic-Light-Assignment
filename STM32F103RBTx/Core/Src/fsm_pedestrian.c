/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 22, 2023
 *      Author: ProX
 */

#include "fsm_pedestrian.h"

void PedestrianRed() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, 1);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, 0);
}

void PedestrianGreen() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, 0);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, 1);
}

void PedestrianInvalid() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, 0);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, 0);
}

void fsm_pedestrian_run(void) {
	switch (pedestrian_status) {
	case PEDESTRIAN_INACTIVE:
		PedestrianInvalid();
		buzzer_status = OFF;

		if (isButtonPressed(4)) {
			if (traffic_status == RED_AMBER || traffic_status == RED_GREEN) {
				pedestrian_status = PEDESTRIAN_GREEN;
			}
			else if (traffic_status == GREEN_RED || traffic_status == AMBER_RED) {
				pedestrian_status = PEDESTRIAN_RED;
			}
			else {
				pedestrian_status = PEDESTRIAN_INACTIVE;
			}
		}
		break;

	case PEDESTRIAN_GREEN:
		PedestrianGreen();
		buzzer_status = ON;

		break;

	case PEDESTRIAN_RED:
		PedestrianRed();
		break;
	}
}

int buzzer_volume = 0;
int freq = 0;			

void fsm_buzzer_run() {
   switch(buzzer_status) {
	case OFF:
		buzzer_volume = 0;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);
		break;

	case ON:
		if (status == RED_AMBER && timer_counter[0] <= amber_counter) {
			buzzer_status = HURRY;
			buzzer_volume = 10;
		}

		if (timer_flag[3] == 1) {
			buzzer_volume = (buzzer_volume == 0) ? 10 : 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);

			setTimer(3, 1000);
		}
		break;

	case HURRY:
		if (status != RED_AMBER && status != RED_GREEN) {
			buzzer_status = OFF;
		}

		/* INCREASE VOLUME AND DECREASE TIME FREQUENCY */
		freq += 10;

		if (timer_flag[3] == 1) {
			buzzer_volume = (buzzer_volume == 0) ? (10 + freq) : 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);

			setTimer(3, (1000 - freq * 10));
		}

		break;
	}
}
