/*
 * graphics.c
 *
 *  Created on: Nov 28, 2023
 *      Author: ASUS
 */

#include "graphics.h"

void Red_Green(void) {
    /* Red */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

    /* Green */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
}

void Red_Amber(void) {
    /* Red */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

    /* Amber */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);
}

void Green_Red(void) {
    /* Green */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);

    /* Red */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
}

void Amber_Red(void) {
    /* Amber */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);

    /* Red */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
}

void light_Off(void) {
    /* Off */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

    /* Off */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
}

int toggleIndex = 0;

void Toggle_Red(void) {
    if (toggleIndex == 0) {
        /* On */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

        /* On */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);

        toggleIndex = 1;
    } else {
        /* Off */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

        /* Off */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);

        toggleIndex = 0;
    }
}

void Toggle_Amber(void) {
    if (toggleIndex == 0) {
        /* On */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);

        /* On */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 1);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);

        toggleIndex = 1;
    } else {
        /* Off */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

        /* Off */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);

        toggleIndex = 0;
    }
}

void Toggle_Green(void) {
    if (toggleIndex == 0) {
        /* On */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 1);

        /* On */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 1);

        toggleIndex = 1;
    } else {
        /* Off */
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

        /* Off */
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);

        toggleIndex = 0;
    }
}
