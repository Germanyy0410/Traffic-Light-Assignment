/*
 * graphics.c
 *
 *  Created on: Nov 28, 2023
 *      Author: ASUS
 */

#include "graphics.h"

void resetLights()
{
	time_modify_counter = 0;
	traffic_status = INIT;

	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
}

void setRedLight1(int blink)
{
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, blink);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_SET);
}
void setGreenLight1(int blink)
{
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, blink);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, GPIO_PIN_SET);
}
void setAmberLight1(int blink)
{
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_1_GPIO_Port, LED_AMBER_1_Pin, blink);
}

void setRedLight2(int blink)
{
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, blink);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_SET);
}
void setGreenLight2(int blink)
{
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, blink);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, GPIO_PIN_SET);
}
void setAmberLight2(int blink)
{
	HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_AMBER_2_GPIO_Port, LED_AMBER_2_Pin, blink);
}

void display7SegmentLED(int number, GPIO_TypeDef *GPIOx[], uint16_t GPIO_Pins[])
{
	int num[10][7] = {
		// a  b  c  d  e  f  g
		{0, 0, 0, 0, 0, 0, 1}, // 0
		{1, 0, 0, 1, 1, 1, 1}, // 1
		{0, 0, 1, 0, 0, 1, 0}, // 2
		{0, 0, 0, 0, 1, 1, 0}, // 3
		{1, 0, 0, 1, 1, 0, 0}, // 4
		{0, 1, 0, 0, 1, 0, 0}, // 5
		{0, 1, 0, 0, 0, 0, 0}, // 6
		{0, 0, 0, 1, 1, 1, 1}, // 7
		{0, 0, 0, 0, 0, 0, 0}, // 8
		{0, 0, 0, 0, 1, 0, 0}  // 9
	};

	for (int i = 0; i < 7; i++)
	{
		HAL_GPIO_WritePin(GPIOx[i], GPIO_Pins[i], num[number][i]);
	}
}

void display7SegmentLight(UART_HandleTypeDef huart2)
{
	uint16_t GPIO_Pins[] = {SEG0_Pin, SEG1_Pin, SEG2_Pin, SEG3_Pin,
							SEG4_Pin, SEG5_Pin, SEG6_Pin};
	GPIO_TypeDef * GPIOx[] = {SEG0_GPIO_Port, SEG1_GPIO_Port, SEG2_GPIO_Port,
			SEG3_GPIO_Port, SEG4_GPIO_Port, SEG5_GPIO_Port, SEG6_GPIO_Port};
	switch (counter_lights)
	{
	case READ_UART:
		if (status == AUTOMATIC_MODE)
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "Light 1 = %d   Light 2 = %d\r\n", counter_light_1, counter_light_2), 1000);
		counter_lights = LIGHT_1;
		break;
	case LIGHT_1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SegmentLED(counter_light_1 / 10, GPIOx, GPIO_Pins); // first digit of light 1
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_2;
			setTimer(3, 250);
		}
		break;
	case LIGHT_2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SegmentLED(counter_light_1 % 10, GPIOx, GPIO_Pins); // second digit of light 1
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_3;
			setTimer(3, 250);
		}
		break;
	case LIGHT_3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SegmentLED(counter_light_2 / 10, GPIOx, GPIO_Pins); // first digit of light 2
		if (timer_flag[3] == 1)
		{
			counter_lights = LIGHT_4;
			setTimer(3, 250);
		}
		break;
	case LIGHT_4:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
		display7SegmentLED(counter_light_2 % 10, GPIOx, GPIO_Pins); // second digit of light 2
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
