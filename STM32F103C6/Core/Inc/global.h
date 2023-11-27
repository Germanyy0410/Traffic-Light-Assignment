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
#include "fsm_pedestrian.h"
#include "led_display.h"
#include "software_timer.h"

#define INIT                    3
#define AUTOMATIC               4
#define MANUAL                  5
#define TUNING                  6

// * Buzzer status * //
#define ON                      7
#define HURRY                   8
#define OFF                     9

// * Automatic mode * //
#define RED_GREEN               50
#define RED_AMBER               60
#define GREEN_RED               70
#define AMBER_RED               80

// * Tuning mode * //
#define MAN_RED                 100
#define MAN_AMBER               200
#define MAN_GREEN               300

// * Pedestrian status * //
#define PEDESTRIAN_INACTIVE     400
#define PEDESTRIAN_GREEN        500
#define PEDESTRIAN_RED          600

extern int status;				// status for traffic mode
extern int pedestrian_status;   // status for pedestrian
extern int buzzer_status;
extern int red_counter;
extern int amber_counter;
extern int green_counter;

extern int time_modify_counter;     /* STORE THE TEMPORARY VALUE TO ADJUST TIME LENGTH */

void reset_to_normal_mode(void);


#endif /* INC_GLOBAL_H_ */
