/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 22, 2023
 *      Author: ProX
 */

#include "fsm_pedestrian.h"
void PedestrianRed(){
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_RESET);
}
void PedestrianGreen(){
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_SET);
}
void PedestrianInvalid(){
	HAL_GPIO_WritePin(D6_PEDESTRIAN_GPIO_Port, D6_PEDESTRIAN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PEDESTRIAN_GPIO_Port, D7_PEDESTRIAN_Pin, GPIO_PIN_RESET);
}
void fsm_pedestrian_run(void) {
    //TODO
	switch(pedestrian_status){
	case PEDESTRIAN_INACTIVE:
		PedestrianInvalid();
		if(isButtonPressed(4)){
			handleButtonProcess(4);
		}
		break;

	case PEDESTRIAN_GREEN:
		PedestrianGreen();
		break;

	case PEDESTRIAN_RED:
		PedestrianRed();
		break;
	}
}

void fsm_buzzer_run() {
    //TODO
}
