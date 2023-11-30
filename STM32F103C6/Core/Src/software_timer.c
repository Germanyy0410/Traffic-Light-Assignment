/*
 * software_timer.c
 *
 *  Created on: Oct 26, 2023
 *      Author: ASUS
 */

#include "software_timer.h"

#define TIMER_CYCLE 10

int timer_flag[NO_TIMERS + 1];
int timer_counter[NO_TIMERS + 1];

void setTimer(int flagNo, int duration) {
	timer_counter[flagNo] = duration / TIMER_CYCLE;
	timer_flag[flagNo] = 0;
}

void timerRun() {
	for (int flagNo = 1; flagNo <= NO_TIMERS; flagNo++) {
		if (timer_counter[flagNo] > 0) {
			timer_counter[flagNo]--;
			if (timer_counter[flagNo] <= 0) {
				timer_flag[flagNo] = 1;
			}
		}
	}
}
