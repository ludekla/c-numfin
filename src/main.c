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
	EurOption call;
	euroption_init(&call, call_payoff, call_strike, expiry);

	// Put Option
	EurOption put;
	euroption_init(&put, put_payoff, put_strike, expiry);

	double call_price = price_by_crr(&bm, &call);
	double put_price = price_by_crr(&bm, &put);

	printf("Binomial Market Model\n");
	printf(
		"spot: %.3f uptick: %.5f downtick: %.5f rate: %.5f\n",
		bm.spot, bm.uptick, bm.downtick, bm.rate
	);
	printf(
		"expiry: %d call strike: %.2f put strike: %.2f\n",
		expiry, call.strike, put.strike
	);
	printf("Call: %.3f Put: %.3f\n", call_price, put_price);

	return 0;
}
