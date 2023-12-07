/*
 * fsm_pedestrian.h
 *
 *  Created on: Nov 22, 2023
 *      Author: ProX
 */

#ifndef INC_FSM_PEDESTRIAN_H_
#define INC_FSM_PEDESTRIAN_H_

#include "global.h"

void fsm_pedestrian_run(UART_HandleTypeDef huart2);
void fsm_buzzer_run(void);

#endif /* INC_FSM_PEDESTRIAN_H_ */
