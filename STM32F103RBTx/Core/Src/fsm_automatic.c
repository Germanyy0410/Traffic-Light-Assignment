/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_automatic.h"

void fsm_automatic_run(void) {
    /* CHANGE TO MANUAL MODE WHEN BUTTON1 IS PRESSED */
    if (isButtonPressed(1)) {
    	status = MANUAL_MODE;
		setTimer(0, 5000);				// reuse timer 0 to 5 seconds for manual event
    }

    if (timer_flag[2] == 1) {
    	counter_light_1--;
    	counter_light_2--;
        setTimer(2, 1000); // set timer 2 to 1 second to update counter light
    }

    switch (traffic_status) {
    case INIT:
    	/* INACTIVE pedestrian light when in INIT state */
    	pedestrian_status = PEDESTRIAN_INACTIVE;

        Red_Green();
        traffic_status = RED_GREEN;
        setTimer(0, green_counter);

        setTimer(2, 1000); // set timer 2 to 1 second to update counter light

        counter_light_1 = red_counter;
        counter_light_2 = green_counter;

        break;

    case RED_GREEN:
        Red_Green();

        if (timer_flag[0] == 1) {
            traffic_status = RED_AMBER;
            setTimer(0, amber_counter);

            counter_light_2 = amber_counter;
        }    

        break;

    case RED_AMBER:
        Red_Amber();

        if (timer_flag[0] == 1) {
            traffic_status = GREEN_RED;
            setTimer(0, green_counter);

            counter_light_1 = green_counter;
            counter_light_2 = red_counter;

            /* INACTIVE pedestrian light when traffic light is backing to GREEN_RED mode */
            pedestrian_status = PEDESTRIAN_INACTIVE;
        }

        break;

    case GREEN_RED:
        Green_Red();

        if (timer_flag[0] == 1) {
            traffic_status = AMBER_RED;
            setTimer(0, amber_counter);

            counter_light_1 = amber_counter;
        }

        break;

    case AMBER_RED:
    	Amber_Red();

        if (timer_flag[0] == 1) {
            traffic_status = RED_GREEN;
            setTimer(0, green_counter);

            counter_light_1 = red_counter;
            counter_light_2 = green_counter;

            /* If the pedestrian light is PEDESTRIAN_RED, change to PEDESTRIAN_GREEN when the traffic light is backing to RED_GREEN mode */
            /* If the pedestrian light is INACTIVE => no change */
            if(pedestrian_status == PEDESTRIAN_RED){
            	pedestrian_status = PEDESTRIAN_GREEN;
            }
        }
        break;
    }
}
