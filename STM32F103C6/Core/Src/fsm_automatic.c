/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_automatic.h"

/* DO SOMEHING WHEN BUTTON IS PRESSED */
void handleButtonProcess(int index) {
    if (index == 1) {                   /* BUTTON 1 -> CHANGE MODE */
        if (traffic_status == INIT || traffic_status == RED_GREEN || traffic_status == RED_AMBER || traffic_status == GREEN_RED || traffic_status == AMBER_RED) {
            traffic_status = MAN_RED;
        } else if (traffic_status == MAN_RED) {
            traffic_status = MAN_AMBER;
        } else if (traffic_status == MAN_AMBER) {
            traffic_status = MAN_GREEN;
        } else if (traffic_status == MAN_GREEN) {
            traffic_status = INIT;
        }
    }
    else if (index == 2) {              /* BUTTON 2 -> UPDATE TIME LENGTH */
        if (traffic_status == MAN_RED) {                /* MODE 2 */
            time_modify_counter = red_counter;

            if (time_modify_counter == 99000) {
                time_modify_counter = 0;
            } else {
                time_modify_counter += 1000;
            }
        }
        else if (traffic_status == MAN_AMBER) {       /* MODE 3 */
            time_modify_counter = amber_counter;

            if (time_modify_counter == 99000) {
                time_modify_counter = 0;
            } else {
                time_modify_counter += 1000;
            }
        }
        else {                                /* MODE 4 */
            time_modify_counter = green_counter;

            if (time_modify_counter == 99000) {
                time_modify_counter = 0;
            } else {
                time_modify_counter += 1000;
            }
        }
    }
    else if (index == 3) {              /* BUTTON 3 -> STORE NEW TIME LENGTH */
        if (traffic_status == MAN_RED) {                    /* MODE 2 */
            red_counter = time_modify_counter;
        }
        else if (traffic_status == MAN_AMBER) {             /* MODE 3 */
            amber_counter = time_modify_counter;
        }
        else {                                      /* MODE 4 */
            green_counter = time_modify_counter;
        }

        traffic_status = INIT;
    }
    else {                              /* BUTTON 4 -> PEDESTRIAN */

    }
}

void fsm_automatic_run(void) {
    /* CHANGE MODE = 2 (MAN_RED) WHEN BUTTON1 IS PRESSED */
    if (isButtonPressed(1)) {
        handleButtonProcess(1);
    }

    switch (traffic_status) {
    case INIT:
        Red_Green();
        traffic_status = RED_GREEN;

        break;

    case RED_GREEN:
        Red_Green();

        if (timer_flag[0] == 1) {
            traffic_status = RED_AMBER;
            setTimer(0, amber_counter);
        }    

        break;

    case RED_AMBER:
        Red_Amber();

        if (timer_flag[0] == 1) {
            traffic_status = GREEN_RED;
            setTimer(0, green_counter);
        }

        break;

    case GREEN_RED:
        Green_Red();

        if (timer_flag[0] == 1) {
            traffic_status = AMBER_RED;
            setTimer(0, amber_counter);
        }

        break;

    case AMBER_RED:
    	Amber_Red();

        if (timer_flag[0] == 1) {
            traffic_status = RED_GREEN;
            setTimer(0, green_counter);
        }
        break;
    }
}
