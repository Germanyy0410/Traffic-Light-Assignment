/*
 * fsm_manual.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_manual.h"

void fsm_manual_run(UART_HandleTypeDef huart2) {
	/* OUT OF TIME FOR MANUAL EVENTS */
	if (timer_flag[1] == 1) {
		status = AUTOMATIC_MODE;
		traffic_status = INIT;
		return;
	}

	switch (traffic_status) {
	case INIT:
		/* UART COMMUNICATION */
		HAL_UART_Transmit(&huart2, (uint8_t *)"Mode: Manual mode\r\n", 24, 500);


		// change traffic state to MAN_RED when change from AUTOMATIC to MANUAL
		traffic_status = MAN_RED;

		time_modify_counter = red_counter; // update temporary counter storing red led delay
		counter_light_1 = red_counter / 1000; 		// counter light 1 show the value of current manual light
		counter_light_2 = traffic_status;					// counter light 2 show the mode
//		counter_lights = READ_UART;					// reset counter for switching 7-seg lights

		setTimer(1, 5000);				// reuse timer 0 to 5 seconds for manual event
		setTimer(2, 500); 				// set timer 1 for led blinking
		setTimer(3, 250);				// timer 3 still counting 7-seg light

		/* UART COMMUNICATION */
		HAL_UART_Transmit(&huart2, (uint8_t *)"Mode 2: Modifying RED\r\n", 26, 500);
		HAL_UART_Transmit(&huart2, (uint8_t *)"Current time = ", 16, 500);
		HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);

		break;
	case MAN_RED:
		/* BLINK LEDs */
		if (timer_flag[2] == 1) {
			Toggle_Red();
			setTimer(2, 500);
		}

		/* CHANGE MODE = 3 (MAN_AMBER) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_AMBER;

			time_modify_counter = amber_counter;	// update temporary counter storing red led delay
			counter_light_1 = amber_counter / 1000;	// counter light 1 show the value of current manual light
			counter_light_2 = traffic_status;				// counter light 2 show the mode
//			counter_lights = READ_UART;				// reset counter for switching 7-seg lights

			setTimer(1, 5000);			// reuse timer 0 to 5 seconds for manual event
			setTimer(2, 500); 			// set timer 1 for led blinking
			setTimer(3, 250);			// timer 3 still counting 7-seg light

			/* UART COMMUNICATION */
			HAL_UART_Transmit(&huart2, (uint8_t *)"Mode 3: Modifying AMBER\r\n", 28, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)"Current time = ", 16, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			HAL_UART_Transmit(&huart2, (uint8_t *)"Updated time = ", 16, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", time_modify_counter / 1000), 500);
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			red_counter = time_modify_counter;
			green_counter = red_counter - amber_counter;
			setTimer(1, 5000);								// set 5 seconds for manual events
			counter_light_1 = red_counter / 1000; // counter light 1 show the value of current manual light
//			counter_lights = READ_UART;								// reset counter for switching 7-seg lights

			status = AUTOMATIC_MODE;
			traffic_status = INIT;

			/* UART COMMUNICATION */
			HAL_UART_Transmit(&huart2, (uint8_t *)"Upon update:\r\n", 15, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)"RED counter = ", 15, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);
		}
		break;

	case MAN_AMBER:
		/* BLINK LEDs */
		if (timer_flag[2] == 1) {
			Toggle_Amber();
			setTimer(2, 500);
		}

		/* CHANGE MODE = 4 (MAN_GREEN) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_GREEN;

			time_modify_counter = green_counter / 1000;	// update temporary counter storing red led delay
			counter_light_1 = green_counter / 1000;			// counter light 1 show the value of current manual light
			counter_light_2 = traffic_status;						// counter light 2 show the mode
//			counter_lights = READ_UART;						// reset counter for switching 7-seg lights

			setTimer(1, 5000);				// reuse timer 0 to 5 seconds for manual event
			setTimer(2, 500); 				// set timer 1 for led blinking
			setTimer(3, 250);				// timer 3 still counting 7-seg light

			/* UART COMMUNICATION */
			HAL_UART_Transmit(&huart2, (uint8_t *)"Mode 4: Modifying GREEN\r\n", 27, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)"Current time = ", 16, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			HAL_UART_Transmit(&huart2, (uint8_t *)"Updated time = ", 16, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", time_modify_counter / 1000), 500);
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			amber_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			setTimer(1, 5000);									// set 5 seconds for manual events
			counter_light_1 = amber_counter / 1000; // counter light 1 show the value of current manual light
//			counter_lights = READ_UART;									// reset counter for switching 7-seg lights

			status = AUTOMATIC_MODE;
			traffic_status = INIT;

			/* UART COMMUNICATION */
			HAL_UART_Transmit(&huart2, (uint8_t *)"Upon update:\r\n", 15, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)"AMBER counter = ", 17, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);
		}

		break;

	case MAN_GREEN:
		/* BLINK LEDs */
		if (timer_flag[2] == 1) {
			Toggle_Green();
			setTimer(2, 500);
		}
		/* CHANGE MODE = 1 (AUTOMATIC) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			HAL_UART_Transmit(&huart2, (uint8_t *)"Updated time = ", 16, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", time_modify_counter / 1000), 500);
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			green_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			setTimer(1, 5000);									// set 5 seconds for manual events
			counter_light_1 = green_counter / 1000; // counter light 1 show the value of current manual light
//			counter_lights = READ_UART;									// reset counter for switching 7-seg lights

			status = AUTOMATIC_MODE;
			traffic_status = INIT;

			/* UART COMMUNICATION */
			HAL_UART_Transmit(&huart2, (uint8_t *)"Upon update:\r\n", 15, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)"GREEN counter = ", 17, 500);
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "%d\r\n", counter_light_1), 500);
		}

		break;
	default:
		break;
	}
}
