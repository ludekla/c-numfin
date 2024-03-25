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

	// Choose strikes for spread options
	int put_greater = (put_strike > call_strike);
	double upstrike = put_greater ? put_strike : call_strike;
	double lostrike = put_greater ? call_strike : put_strike;

	// Double Digital Option
	SpreadOption dopt;
	soption_init(&dopt, DOUBLE_DIGIT, lostrike, upstrike, expiry);

	// Bull and Bear Spreads
	SpreadOption bull;
	soption_init(&bull, BULL_SPREAD, lostrike, upstrike, expiry);
	SpreadOption bear;
	soption_init(&bear, BEAR_SPREAD, lostrike, upstrike, expiry);

	// Let fly.
	double call_price = voption_crr(call, bm);
	double put_price = voption_crr(put, bm);
	double dcall_price = voption_crr(dcall, bm);
	double dput_price = voption_crr(dput, bm);
	double dopt_price = soption_crr(dopt, bm);
	double bear_price = soption_crr(bear, bm);
	double bull_price = soption_crr(bull, bm);

	printf("Binomial Market Model\n");
	printf("=====================\n");
	printf(
		"spot: %.3f uptick: %.5f downtick: %.5f rate: %.5f\n",
		bm.spot, bm.uptick, bm.downtick, bm.rate
	);
	printf("-----------------\n");
	printf("Option Parameters\n");
	printf("=================\n");
	printf(
		"expiry: %d call strike: %.2f put strike: %.2f\n",
		expiry, call.strike, put.strike
	);
	printf("-----------------\n");
	printf("Option Prices\n");
	printf("=============\n");
	printf("Call:        %9.3f | Put:         %9.3f\n", call_price, put_price);
	printf("Digtal Call: %9.3f | Digital Put: %9.3f\n", dcall_price, dput_price);
	printf("Bear Spread: %9.3f | Bull Spread: %9.3f\n", bear_price, bull_price);
	printf("Double Digit Option: %6.3f\n", dopt_price);

	return 0;
}
