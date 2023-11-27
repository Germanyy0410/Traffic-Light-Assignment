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

/* 
* TIMER[0]: AUTOMATIC
* TIMER[1]: MANUAL
* TIMER[2]: BUZZER
*/

extern int timer_flag[NUM_OF_TIMERS + 1];
extern int timer_counter[NUM_OF_TIMERS + 1];

void setTimer(int flagNo, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
