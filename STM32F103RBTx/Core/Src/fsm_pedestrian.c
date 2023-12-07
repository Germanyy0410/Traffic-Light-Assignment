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

void fsm_pedestrian_run(UART_HandleTypeDef huart2) {
	switch (pedestrian_status) {
	case PEDESTRIAN_INACTIVE:
		PedestrianInvalid();
		buzzer_status = OFF;

		if (isButtonPressed(4)) {
			if (traffic_status == RED_AMBER || traffic_status == RED_GREEN) {
//				HAL_UART_Transmit(&huart2, (uint8_t *)"Pedestrian mode: GREEN\r\n", 26, 500);
				pedestrian_status = PEDESTRIAN_GREEN;
			}
			else if (traffic_status == GREEN_RED || traffic_status == AMBER_RED) {
//				HAL_UART_Transmit(&huart2, (uint8_t *)"Pedestrian mode: RED\r\n", 24, 500);
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
int timer = 50;

void fsm_buzzer_run() {
   switch(buzzer_status) {
	case OFF:
		buzzer_volume = 0;
		freq = 0;
		timer = 50;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);
		break;

	case ON:
		if (traffic_status == RED_AMBER) {
			/* INCREASE VOLUME AND DECREASE TIME FREQUENCY */
			if (timer_flag[3] == 1) {
				timer -= 1;
				freq += 5;
				buzzer_volume = (buzzer_volume == 0) ? (25 + freq) : 0;
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, buzzer_volume);

				setTimer(3, timer);
			}
		}
		break;
	}
}
