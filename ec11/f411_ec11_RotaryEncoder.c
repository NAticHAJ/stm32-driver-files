/*
 * f411_ec11_RotaryEncoder.c
 *
 *  Created on: Jul 30, 2023
 *      Author: NAticHAJ
 *
 *  Meant for 5 pin rotary encoders with push-button
 *
 *  Connect common terminal and one button pin to ground.
 *  Connect other 3 to digital inputs with pull-up resistors.
 *
 *  Change values in defines to suit application
 *
 *  Call getRotation to poll the encoder. Function will return encoder state:
 *   0: No change
 *   1: CW rotation
 *  -1: CCW rotation
 *
 *  Call getButton to poll the pushbutton. Function will return press states:
 *   0: No change
 *   1: Button pressed
 *  -1: Button held
 */

// Includes
#include <f411_ec11_RotaryEncoder.h>
#include "stm32f4xx_hal.h"


/* WARNING!!!
 *
 * The Threshold variables are declared as uint8_t.
 * Change type if values have to be greater than 255.
 *
 * Numbers indicate how many times function has to be called before latching.
 * This is mainly to prevent false positives.
 *
 */

// Defines
#define CW_PIN HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)
#define CCW_PIN HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)
#define PRESS_TH 0 // Less is more sensitive
#define HOLD_TH 255 // Less is shorter time


/*
 * Variables used for flags and counters
 * to keep track of internal state.
 */

// Variables
static volatile int8_t reDirection = 0;
static volatile uint8_t reMoving = 0;
static volatile uint8_t reTrigger = 0;
static volatile uint8_t btnCounter = 0;


// Private function used to reset internal state.
static void reset()
{
	reDirection = 0;
	reMoving = 0;
	reTrigger = 0;
}


// Function to poll to get update on rotary encoder.
int8_t ec11_PollRotation()
{
	// Initialize return value
	int8_t rtn = 0;

	//Detect rotation
	if(!reMoving)
	{
		//Prepare CW
		if(CW_PIN && !CCW_PIN && !reTrigger)
		{
			reDirection = 1;
			reMoving = 1;
		}

		//Prepare CCW
		if(!CW_PIN && CCW_PIN && !reTrigger)
		{
			reDirection = -1;
			reMoving = 1;
		}
	}

	//Latch rotation or reset
	if(reMoving && !reTrigger)
	{
		if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) && !CCW_PIN)
		{
			reTrigger = 1;
		}

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) && CCW_PIN)
		{
			reset();
		}
	}

	//Commit when in neutral position and reset
	if(reTrigger && CW_PIN && CCW_PIN)
	{
		rtn = reDirection;
		reset();
	}

	return rtn;
}


// Function to poll to get update on push button.
int8_t ec11_PollButton()
{
	// Initialize return value
	int8_t rtn = 0;

	// Ignore bouncing, detect press
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
	{
		if(btnCounter > PRESS_TH && btnCounter < HOLD_TH) rtn = 1;
		else rtn = 0;

		btnCounter = 0;
	}
	// Detect hold
	else
	{
		if(btnCounter < HOLD_TH) btnCounter++;
		if(btnCounter == HOLD_TH-1) rtn = -1;
	}

	return rtn;
}
