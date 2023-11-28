/*
 * software_timer.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "global.h"

#define NO_TIMERS 4

extern int timer_flag[NO_TIMERS + 1];
extern int timer_counter[NO_TIMERS + 1];

void setTimer(int, int);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
