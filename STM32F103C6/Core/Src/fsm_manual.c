/*
 * fsm_manual.c
 *
 *  Created on: 21 thg 11, 2023
 *      Author: ProX
 */

#include "fsm_manual.h"

int blink = 0;

void fsm_manual_run(void) {
	/* OUT OF TIME FOR MANUAL EVENTS */
	if (timer_flag[1] == 1) {
		status = AUTOMATIC_MODE;
		traffic_status = INIT;
	}

	if (timer_flag[2] == 1) { // using timer2 to blink the led
		blink = 1 - blink;
		setTimer(2, 500); // toggle every 500ms, this would get f = 2Hz for blinking the led
	}

	switch (traffic_status) {
	case INIT:
		// change traffic state to MAN_RED when change from AUTOMATIC to MANUAL
		traffic_status = MAN_RED;

		time_modify_counter = red_counter; // update temporary counter storing red led delay
		counter_light_1 = red_counter / 1000; 		// counter light 1 show the value of current manual light
		counter_light_2 = traffic_status;					// counter light 2 show the mode

        uartOneTimeFlag = 0;

		setTimer(1, 5000);				// reuse timer 0 to 5 seconds for manual event
		setTimer(2, 500); 				// set timer 1 for led blinking
		setTimer(3, 250);				// timer 3 still counting 7-seg light
		counter_lights = 1;				// reset counter for switching 7-seg lights

		break;
	case MAN_RED:
		/* BLINK LEDs */
		setRedLight1(blink);
		setRedLight2(blink);

		/* CHANGE MODE = 3 (MAN_AMBER) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_AMBER;

			time_modify_counter = amber_counter;	// update temporary counter storing red led delay
			counter_light_1 = amber_counter / 1000;	// counter light 1 show the value of current manual light
			counter_light_2 = traffic_status;				// counter light 2 show the mode

            uartOneTimeFlag = 0;

			setTimer(1, 5000);			// reuse timer 0 to 5 seconds for manual event
			setTimer(2, 500); 			// set timer 1 for led blinking
			setTimer(3, 250);			// timer 3 still counting 7-seg light
			counter_lights = 1;			// reset counter for switching 7-seg lights
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			red_counter = time_modify_counter;
			green_counter = red_counter - amber_counter;
			setTimer(1, 5000);								// set 5 seconds for manual events
			counter_light_1 = red_counter / 1000; // counter light 1 show the value of current manual light
			counter_lights = 1;								// reset counter for switching 7-seg lights
		}
		break;

	case MAN_AMBER:
		/* BLINK LEDs */
		setAmberLight1(blink);
		setAmberLight2(blink);

		/* CHANGE MODE = 4 (MAN_GREEN) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			traffic_status = MAN_GREEN;

			time_modify_counter = green_counter / 1000;	// update temporary counter storing red led delay
			counter_light_1 = green_counter / 1000;			// counter light 1 show the value of current manual light
			counter_light_2 = traffic_status;						// counter light 2 show the mode

            uartOneTimeFlag = 0;

			setTimer(1, 5000);				// reuse timer 0 to 5 seconds for manual event
			setTimer(2, 500); 				// set timer 1 for led blinking
			setTimer(3, 250);				// timer 3 still counting 7-seg light
			counter_lights = 1;				// reset counter for switching 7-seg lights
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			amber_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			setTimer(1, 5000);									// set 5 seconds for manual events
			counter_light_1 = amber_counter / 1000; // counter light 1 show the value of current manual light
			counter_lights = 1;									// reset counter for switching 7-seg lights
		}

		break;

	case MAN_GREEN:
		/* BLINK LEDs */
		setGreenLight1(blink);
		setGreenLight2(blink);

		/* CHANGE MODE = 1 (AUTOMATIC) WHEN BUTTON1 IS PRESSED */
		if (isButtonPressed(1)) {
			status = AUTOMATIC_MODE;
			traffic_status = INIT;
            uartOneTimeFlag = 0;
		}

		if (isButtonPressed(2) == 1) { // increasing 7-segment light counter
			time_modify_counter += UPDATED_TIME;
			if (time_modify_counter > MAX_TIME)
				time_modify_counter = 1000; // 1 second
			setTimer(1, 5000); // set 5 seconds for manual events
		}

		if (isButtonPressed(3) == 1) { // set the new value for 7-segment light counter
			green_counter = time_modify_counter;
			red_counter = amber_counter + green_counter;
			setTimer(1, 5000);									// set 5 seconds for manual events
			counter_light_1 = green_counter / 1000; // counter light 1 show the value of current manual light
			counter_lights = 1;									// reset counter for switching 7-seg lights
		}

		break;
	default:
		break;
	}
}
