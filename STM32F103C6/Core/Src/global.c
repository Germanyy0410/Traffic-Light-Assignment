/*
 * global.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "global.h"

int status = AUTOMATIC;
int status_light_1 = INIT;
int status_light_2 = INIT;

int red_counter = 5000;
int amber_counter = 2000;
int green_counter = 3000;

void reset_to_normal_mode(void) {
    status = AUTOMATIC;
    status_light_1 = INIT;
    status_light_2 = INIT;
}