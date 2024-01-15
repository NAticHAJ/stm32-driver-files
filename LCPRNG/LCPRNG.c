/*
 * LCPRNG.c
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

// Include header file
#include "LCPRNG.h"

/*
 * 0 < Mult & Add < Mod
 */
void LCPRNG_Define(lcprng * Generator, unsigned int Modulus, unsigned int Multiplier, unsigned int Increment, unsigned int Seed) {
	Generator->Mod = Modulus;
	Generator->Mult = Multiplier%2 == 0 ? (Multiplier-1)%Modulus : Multiplier%Modulus;
	Generator->Add = Increment%Modulus;
	Generator->Seed = (Generator->Mult*Seed+Generator->Add);
}

// Next Pseudo Random Number form specified generator
unsigned int LCPRNG_Next(lcprng * Generator) {
	Generator->Seed = Generator->Mult*Generator->Seed+Generator->Add;
	return Generator->Seed%Generator->Mod;
}
