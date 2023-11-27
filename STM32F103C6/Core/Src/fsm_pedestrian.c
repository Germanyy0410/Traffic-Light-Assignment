/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 22, 2023
 *      Author: ProX
 */

#include "fsm_pedestrian.h"

void PedestrianRed() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_RESET);
}

void PedestrianGreen() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_SET);
}

void PedestrianInvalid() {
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_RESET);
}

void fsm_pedestrian_run(void) {
	switch (pedestrian_status) {
	case PEDESTRIAN_INACTIVE:
		PedestrianInvalid();
		buzzer_status = OFF;

		if (isButtonPressed(4)) {
			handleButtonProcess(4);
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

		if (timer_flag[2] == 1) {
			buzzer_volume = (buzzer_volume == 0) ? 10 : 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);

			setTimer(2, 1000);
		}
		break;

	case HURRY:
		if (status != RED_AMBER && status != RED_GREEN) {
			buzzer_status = OFF;
		}

		/* INCREASE VOLUME AND DECREASE TIME FREQUENCY */
		freq += 10;		
		
		if (timer_flag[2] == 1) {
			buzzer_volume = (buzzer_volume == 0) ? (10 + freq) : 0;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);

			setTimer(2, (1000 - freq * 10));
		}

		break;
	}
}
