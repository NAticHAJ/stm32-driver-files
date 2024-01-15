/*
 * LCPRNG.h
 *
 *  Created on: Jan 15, 2024
 *      Author: NAticHAJ
 *
 *      Pseudo Random Number Generator
 *
 *      Initialize lcprng type
 *      and pass in LCPRNG_Define
 *      define properly.
 *
 *      Call LCPRNG_Next and pass
 *      lcprng to get the next
 *      "random" number.
 *
 *      For simple uses ONLY!
 */

#ifndef INC_LCPRNG_H_
#define INC_LCPRNG_H_

// Linear Congruential Pseudo Random Number Generator
typedef struct lcprng {
	unsigned int Mod;
	unsigned int Mult;
	unsigned int Add;
	unsigned int Seed;
} lcprng;

void LCPRNG_Define(lcprng *, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int LCPRNG_Next(lcprng *);

#endif /* INC_LCPRNG_H_ */
