/*
 * fsm_automatic.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"

void Red_Green(void);
void Red_Amber(void);
void Green_Red(void);
void Amber_Red(void);
void light_Off(void);
void fsm_automatic_run(void);

#endif /* INC_FSM_AUTOMATIC_H_ */
