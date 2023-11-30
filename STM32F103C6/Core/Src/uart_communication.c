/*
 * uart_communication.c
 *
 *  Created on: Nov 30, 2023
 *      Author: ASUS
 */

#include "uart_communication.h"

void uart_communiation_fsm(UART_HandleTypeDef huart2)
{
	switch (traffic_status)
	{
	case INIT:
		if (status == AUTOMATIC_MODE)
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Mode: Automatic mode\r\n"), 1000);
		else
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Mode: Manual mode\r\n"), 1000);

		break;

	case RED_GREEN:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "RED   GREEN\r\n"), 1000);
		}

		if (countingDownFlag == 0)
		{
			countingDownFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 1000);
		}
		break;

	case RED_AMBER:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "RED   AMBER\r\n"), 1000);
		}

		if (countingDownFlag == 0)
		{
			countingDownFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 1000);
		}
		break;

	case GREEN_RED:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "GREEN   RED\r\n"), 1000);
		}

		if (countingDownFlag == 0)
		{
			countingDownFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 1000);
		}
		break;

	case AMBER_RED:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "AMBER   RED\r\n"), 1000);
		}

		if (countingDownFlag == 0)
		{
			countingDownFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 1000);
		}
		break;

	case MAN_RED:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Mode 2: Modifying RED\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Current time = %d\r\n", counter_light_1), 1000);
		}

		if (isButtonPressed(2) == 1)
		{ // increasing 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Updated time = %d\r\n", time_modify_counter / 1000), 1000);
		}

		if (isButtonPressed(3) == 1)
		{ // set the new value for 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Upon update:\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "RED counter = %d\r\n", counter_light_1), 1000);
		}

		break;

	case MAN_AMBER:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Mode 3: Modifying AMBER\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Current time = %d\r\n", counter_light_1), 1000);
		}

		if (isButtonPressed(2) == 1)
		{ // increasing 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Updated time = %d\r\n", time_modify_counter / 1000), 1000);
		}

		if (isButtonPressed(3) == 1)
		{ // set the new value for 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Upon update:\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "AMBER counter = %d\r\n", counter_light_1), 1000);
		}

		break;

	case MAN_GREEN:
		if (uartOneTimeFlag == 0)
		{
			uartOneTimeFlag = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Mode 4: Modifying GREEN\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Current time = %d\r\n", counter_light_1), 1000);
		}

		if (isButtonPressed(2) == 1)
		{ // increasing 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Updated time = %d\r\n", time_modify_counter / 1000), 1000);
		}

		if (isButtonPressed(3) == 1)
		{ // set the new value for 7-segment light counter
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Upon update:\r\n"), 1000);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "GREEN counter = %d\r\n", counter_light_1), 1000);
		}

		break;

	default:
		break;
	}
}
