/*
 * global.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "global.h"

int status = AUTOMATIC_MODE;
int pedestrian_status = PEDESTRIAN_INACTIVE;
int buzzer_status = OFF;

int time_modify_counter = 0;

int traffic_status = INIT;
int red_counter = 5000;
int amber_counter = 2000;
int green_counter = 3000;

int counter_light_1 = 1;
int counter_light_2 = 1;
int counter_lights = 1;
