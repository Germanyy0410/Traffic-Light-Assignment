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
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_pedestrian.h"
#include "graphics.h"
#include "scheduler.h"
#include <stdio.h>


#define INIT 1
#define AUTOMATIC_MODE 2
#define MANUAL_MODE 3
#define TUNING_MODE 4

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
#define MAN_RED 120
#define MAN_AMBER 220
#define MAN_GREEN 320

#define READ_UART 100
#define LIGHT_1 200
#define LIGHT_2 300
#define LIGHT_3 400
#define LIGHT_4 500

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
extern int counter_lights;		// counter for switching 7 segment lights

#define MAX_BUFFER_SIZE	30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern char str[MAX_BUFFER_SIZE];	// read string from uart

void reset_to_normal_mode(void);

#endif /* INC_GLOBAL_H_ */
