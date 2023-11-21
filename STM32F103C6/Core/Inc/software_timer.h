/*
 * software_timer.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "global.h"

#define NUM_OF_TIMERS 3

extern int timer_flag[NUM_OF_TIMERS];

void setTimer(int flagNo, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
