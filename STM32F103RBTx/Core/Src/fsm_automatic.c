/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_automatic.h"

void Red_Green(void) {
    //TODO
}

void Red_Amber(void) {
    //TODO
}

void Green_Red(void) {
    //TODO
}

void Amber_Red(void) {
    //TODO
}

void light_Off(void) {
    //TODO
}

void handleButtonProcess(int index) {
    if (index == 1) {
        //TODO: Button 1
    }
    else if (index == 2) {
        //TODO: Button 2
    }
    else {
        //TODO: Button 3
    }   
}

void fsm_automatic_run(void) {
    if (isButtonPressed(1)) {
        status = INIT;
    }
    
    if (isButtonPressed(2)) {
        handleButtonProcess(2);
        status = MAN_RED;
    }

    switch (status) {
    case INIT:
            Red_Green();
            status = RED_GREEN;

            break;

    case RED_GREEN:
            Red_Green();

            if (timer_flag[0] == 1) {
                status = RED_AMBER;
                setTimer(0, amber_counter);
            }    

            break;

    case RED_AMBER:
            Red_Amber();

            if (timer_flag[0] == 1) {
                status = GREEN_RED;
                setTimer(0, green_counter);
            }

            break;

    case GREEN_RED:
            Green_Red();

            if (timer_flag[0] == 1) {
                status = AMBER_RED;
                setTimer(0, amber_counter);
            }

            break;

    case AMBER_RED:
            Yellow_Red();

            if (timer_flag[0] == 1) {
                status = RED_GREEN;
                setTimer(0, green_counter);
            }
            break;
    }
}