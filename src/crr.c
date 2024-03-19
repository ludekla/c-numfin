/** @file crr.c
 *  @brief Function definitions for the CRR model.
 * 
 *  Implementation of the Cox-Ross-Rubinstein Pricer (Binomial Model).
 * 
 *  @author Lutz
*/

#include <math.h>
#include <stdlib.h>

#include "crr.h"

// Binomial Model functions
void binmodel_init(BinModel *bm, double s, double u, double d, double r) {
    bm->spot = s;
    bm->uptick = u;
    bm->downtick = d;
    bm->rate = r;
}

double binmodel_prob(BinModel * bm) {
    return (bm->rate - bm->downtick) / (bm->uptick - bm->downtick);
}

double binmodel_price(BinModel *bm, int expiry, int n_upticks) {
    double up = n_upticks * log(1.0 + bm->uptick);
    double down = (expiry - n_upticks) * log(1.0 + bm->downtick);
    return bm->spot * exp(up + down);
}

// European Option functions
void euroption_init(EurOption *opt, Payoff payoff, double k, int t) {
    opt->strike = k;
    opt->expiry = t;
    opt->payoff = payoff;
}

// payoff functions
double call_payoff(double price, double strike) {
    return (price > strike) ? price - strike : 0.0;
}

double put_payoff(double price, double strike) {
    return (price > strike) ? 0.0 : strike - price;
}

// CRR pricing function
double price_by_crr(BinModel * bm, EurOption * opt) {
    int expiry = opt->expiry;
    double strike = opt->strike; 
    double * prices = (double *) malloc((expiry + 1) * sizeof(double));
    // fill last time slice
    for (int i = 0; i <= expiry; i++) {
        double underlying = binmodel_price(bm, expiry, i);
        prices[i] = opt->payoff(underlying, strike);
    }
    double dc = 1.0 / (1.0 + bm->rate);      // discount
    double q = binmodel_prob(bm);
    // CRR algorithm: beware, it's O(n^2)
    for (int s = expiry; s > 0; s--) {  // time slice
        for (int i = 0; i <= s; i++) {
            prices[i] = dc * (q * prices[i+1] + (1.0 - q) * prices[i]);
        }
    }
    double result = prices[0];
    free(prices);
    return result;
}