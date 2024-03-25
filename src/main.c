/** @file main.c
 *  @brief Function definitions for the CRR model.
 * 
 *  Implementation of the Cox-Ross-Rubinstein Pricer (Binomial Model).
 * 
 *  @author Lutz
*/

#include <stdio.h>
#include <stdlib.h>

#include "crr.h"
#include "option.h"

// DO NOT FORGET THE -lm FLAG TO INCLUDE THE MATH LIB!

int main(int args, char **argv) {
	printf("Hello Cox-Ross-Rubinstein Pricer!\n");

	if (args != 4) {
		printf("Usage: bin/crr [expiry] [call strike] [put strike]\n");
		exit(1);
	} 

	int expiry = atoi(argv[1]);
	double call_strike = atof(argv[2]);
	double put_strike = atof(argv[3]);

	BinModel bm;
	binmodel_init(&bm, 100.0, 0.01, -0.01, 0.005);

	// Call Option
	VanillaOption call;
	voption_init(&call, CALL, call_strike, expiry);
	
	// Put Option
	VanillaOption put;
	voption_init(&put, PUT, put_strike, expiry);

	// Digital Options
	VanillaOption dcall;
	voption_init(&dcall, DIGITAL_CALL, call_strike, expiry);
	VanillaOption dput;
	voption_init(&dput, DIGITAL_PUT, put_strike, expiry);

	// Double Digital Option
	DoubleOption dopt;
	int put_greater = (put_strike > call_strike);
	double upstrike = put_greater ? put_strike : call_strike;
	double lostrike = put_greater ? call_strike : put_strike;
	doption_init(&dopt, lostrike, upstrike, expiry);

	// Let fly.
	double call_price = voption_crr(call, bm);
	double put_price = voption_crr(put, bm);
	double dcall_price = voption_crr(dcall, bm);
	double dput_price = voption_crr(dput, bm);
	double dopt_price = doption_crr(dopt, bm);

	printf("Binomial Market Model\n");
	printf(
		"spot: %.3f uptick: %.5f downtick: %.5f rate: %.5f\n",
		bm.spot, bm.uptick, bm.downtick, bm.rate
	);
	printf(
		"expiry: %d call strike: %.2f put strike: %.2f\n",
		expiry, call.strike, put.strike
	);
	printf("Call:        %6.3f Put:         %6.3f\n", call_price, put_price);
	printf("Digtal Call: %6.3f Digital Put: %6.3f\n", dcall_price, dput_price);
	printf("Double Digit Option: %6.3f\n", dopt_price);

	return 0;
}
