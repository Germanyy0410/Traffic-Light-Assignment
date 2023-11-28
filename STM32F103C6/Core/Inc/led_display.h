/*
 * led_display.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_tuning.h"

void fsm_mode();
void send7SEG(void);

#endif /* INC_LED_DISPLAY_H_ */
