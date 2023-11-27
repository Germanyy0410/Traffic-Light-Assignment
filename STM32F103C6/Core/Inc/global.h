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

#define INIT            				3
#define AUTOMATIC_MODE 	4
#define MANUAL_MODE      	5
#define TUNING_MODE       	6

#define MAX_TIME 			99000 	// 99 seconds
#define UPDATED_TIME 	1000 	// 1 second

// * Automatic mode * //
#define RED_GREEN           50
#define RED_AMBER          60
#define GREEN_RED           70
#define AMBER_RED          80

// * Tuning mode * //
#define MAN_RED          100
#define MAN_AMBER        200
#define MAN_GREEN        300

extern int status;					// general status
extern int traffic_status;			// status for traffic mode
extern int pedestrian_status;  // status for pedestrian
extern int red_counter;
extern int abmer_counter;
extern int green_counter;

void reset_to_normal_mode(void);


#endif /* INC_GLOBAL_H_ */
