/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_automatic.h"

void Red_Green(void) {
    //TODO
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
}

void Red_Amber(void) {
    //TODO
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void Green_Red(void) {
    //TODO
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void Amber_Red(void) {
    //TODO
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

void light_Off(void) {
    //TODO
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
}

/* DO SOMEHING WHEN BUTTON IS PRESSED */
void handleButtonProcess(int index) {
    if (index == 1) {                   /* BUTTON 1 -> CHANGE MODE */
        if (status == INIT || status == RED_GREEN || status == RED_AMBER || status == GREEN_RED || status == AMBER_RED) {
            status = MAN_RED;
        } else if (status == MAN_RED) {
            status = MAN_AMBER;
        } else if (status == MAN_AMBER) {
            status = MAN_GREEN;
        } else if (status == MAN_GREEN) {
            status = INIT;
        }
    }
    else if (index == 2) {              /* BUTTON 2 -> UPDATE TIME LENGTH */
        if (status == MAN_RED) {                /* MODE 2 */
        	time_modify_counter = red_counter;
            
            if (time_modify_counter == 99000) {
                time_modify_counter = 0;
            } else {
                time_modify_counter += 1000;
            }
        } 
        else if (status == MAN_AMBER) {       /* MODE 3 */
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
        if (status == MAN_RED) {                    /* MODE 2 */
            red_counter = time_modify_counter;
        } 
        else if (status == MAN_AMBER) {             /* MODE 3 */
            amber_counter = time_modify_counter;
        } 
        else {                                      /* MODE 4 */
            green_counter = time_modify_counter;
        }

        status = INIT;
    } 
    else if (index == 4){                              /* BUTTON 4 -> PEDESTRIAN */
        if(status == RED_AMBER || status == RED_GREEN){
        	pedestrian_status = PEDESTRIAN_GREEN;
        }
        else if (status == GREEN_RED || status == AMBER_RED){
        	pedestrian_status = PEDESTRIAN_RED;
        }
        else {
        	pedestrian_status = PEDESTRIAN_INACTIVE;
        }
    }
}

void fsm_automatic_run(void) {
    /* CHANGE MODE = 2 (MAN_RED) WHEN BUTTON1 IS PRESSED */
    if (isButtonPressed(1)) {
        handleButtonProcess(1);
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

//          INVACTIVE pedestrian light when traffic light is backing to GREEN_RED mode
            pedestrian_status = PEDESTRIAN_INACTIVE;
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
        Amber_Red();

        if (timer_flag[0] == 1) {
            status = RED_GREEN;
            setTimer(0, green_counter);

//            if the pedestrian light is PEDESTRIAN_RED, change to PEDESTRIAN_GREEN when the traffic light is backing to RED_GREEN mode
//            if the pedestrian light is INACTIVE => no change
            if(pedestrian_status == PEDESTRIAN_RED){
            	pedestrian_status = PEDESTRIAN_GREEN;
            }
        }
        break;
    }
}
