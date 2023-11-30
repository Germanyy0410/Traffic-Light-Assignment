/*
 * graphics.h
 *
 *  Created on: Nov 28, 2023
 *      Author: ASUS
 */

#ifndef INC_GRAPHICS_H_
#define INC_GRAPHICS_H_

#include "global.h"

void resetLights();
void setRedLight1(int blink);
void setGreenLight1(int blink);
void setAmberLight1(int blink);
void setRedLight2(int blink);
void setGreenLight2(int blink);
void setAmberLight2(int blink);

void display7SegmentLED(int number, GPIO_TypeDef *GPIOx[], uint16_t GPIO_Pins[]);
void display7SegmentLight();

#endif /* INC_GRAPHICS_H_ */
