/*
 * f411_ec11_RotaryEncoder.h
 *
 * Created on: Jul 30, 2023
 * 	   Author: NAticHAJ
 *
 * Driver for 5 pin Rotary Encoder with button.
 *
 * De-bouncing handled by code.
 * Functions return 0, 1 and -1 for no change and CW/CCW or Pressed/Held.
 *
 * Change values in source file defines section.
 */

#ifndef INC_F411_EC11_ROTARYENCODER_H_
#define INC_F411_EC11_ROTARYENCODER_H_

#include "stm32f4xx_hal.h"

int8_t ec11_PollRotation();

int8_t ec11_PollButton();

#endif /* INC_F411_EC11_ROTARYENCODER_H_ */
