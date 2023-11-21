/*
 * global.h
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "button.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_tuning.h"
#include "led_display.h"
#include "software_timer.h"

#define INIT            3
#define AUTOMATIC       4
#define MANUAL          5
#define TUNING          6

// * Automatic mode * //
#define RED_GREEN           50
#define RED_AMBER          60
#define GREEN_RED           70
#define AMBER_RED          80

// * Tuning mode * //
#define MAN_RED          100
#define MAN_AMBER      200
#define MAN_GREEN        300

extern int status;				// status for traffic mode
extern int status_light_1; 		// status for light 1
extern int status_light_2; 		// status for light 2
extern int red_counter;
extern int abmer_counter;
extern int green_counter;

void reset_to_normal_mode(void);


#endif /* INC_GLOBAL_H_ */
