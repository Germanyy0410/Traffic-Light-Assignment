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
#include "software_timer.h"

#define INIT 3
#define AUTOMATIC_MODE 4
#define MANUAL_MODE 5
#define TUNING_MODE 6

#define MAX_TIME 99000    // 99 seconds
#define UPDATED_TIME 1000 // 1 second

// * Buzzer status * //
#define ON 7
#define HURRY 8
#define OFF 9

// * Automatic mode * //
#define RED_GREEN 50
#define RED_AMBER 60
#define GREEN_RED 70
#define AMBER_RED 80

// * Pedestrian status * //
#define PEDESTRIAN_INACTIVE 400
#define PEDESTRIAN_GREEN 500
#define PEDESTRIAN_RED 600

// * Tuning mode * //
#define MAN_RED 100
#define MAN_AMBER 200
#define MAN_GREEN 300

extern int status;            // general status
extern int traffic_status;    // status for traffic mode

extern int pedestrian_status; // status for pedestrian
extern int buzzer_status;
extern int red_counter;
extern int amber_counter;
extern int green_counter;

extern int time_modify_counter; /* STORE THE TEMPORARY VALUE TO ADJUST TIME LENGTH */
extern int counter_light_1; 	// counter for light 1
extern int counter_light_2; 	// counter for light 2

void reset_to_normal_mode(void);

#endif /* INC_GLOBAL_H_ */
