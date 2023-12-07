/*
 * graphics.c
 *
 *  Created on: Nov 28, 2023
 *      Author: ASUS
 */

#include "graphics.h"

void resetLights(void) {
    time_modify_counter = 0;
	traffic_status = INIT;

    /* Off */
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, 0);

    /* Off */
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, 0);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, 0);
}

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

void display7SegmentLight(UART_HandleTypeDef huart2)
{
	switch (counter_lights)
	{
	case INIT:
		counter_lights = READ_UART;
		setTimer(3, 250); 		// timer 3 for counting light
		break;
	case READ_UART:
		if (status == AUTOMATIC_MODE) {
			sprintf(str, "");
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 500);

		}
		counter_lights = LIGHT_1;
		break;
	case LIGHT_1:
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_2;
			setTimer(3, 250);
		}
		break;
	case LIGHT_2:
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_3;
			setTimer(3, 250);
		}
		break;
	case LIGHT_3:
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_4;
			setTimer(3, 250);
		}
		break;
	case LIGHT_4:
		if (timer_flag[3] == 1)
		{
			counter_lights = READ_UART;
			if (status == AUTOMATIC_MODE)
			{
				counter_light_1--;
				counter_light_2--;
			}
			setTimer(3, 250);
		}
		break;
	default:
		counter_lights = READ_UART;
		break;
	}
}
