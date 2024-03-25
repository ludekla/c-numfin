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
#include "option.h"

// Binomial Model functions
void binmodel_init(BinModel *bm, double s, double u, double d, double r) {
    bm->spot = s;
    bm->uptick = u;
    bm->downtick = d;
    bm->rate = r;
}

double binmodel_prob(BinModel bm) {
    return (bm.rate - bm.downtick) / (bm.uptick - bm.downtick);
}

double binmodel_price(BinModel bm, int expiry, int n_upticks) {
    double up = n_upticks * log(1.0 + bm.uptick);
    double down = (expiry - n_upticks) * log(1.0 + bm.downtick);
    return bm.spot * exp(up + down);
}

// CRR pricing functions
void crr(BinModel bm, int expiry, double * prices) {
    double dc = 1.0 / (1.0 + bm.rate);      // discount
    double q = binmodel_prob(bm);
    // CRR algorithm: beware, it's O(n^2)
    for (int s = expiry; s > 0; s--) {  // time slice
        for (int i = 0; i <= s; i++) {
            prices[i] = dc * (q * prices[i+1] + (1.0 - q) * prices[i]);
        }
    }
}

double doption_crr(DoubleOption opt, BinModel bm) {
    double * prices = (double *) malloc((opt.expiry + 1) * sizeof(double));
    // fill last time slice
    for (int i = 0; i <= opt.expiry; i++) {
        double underlying = binmodel_price(bm, opt.expiry, i);
        prices[i] = double_payoff(opt, underlying);
    }
    crr(bm, opt.expiry, prices);
    double result = prices[0];
    free(prices);
    return result;
}

double voption_crr(VanillaOption opt, BinModel bm) {
    double * prices = (double *) malloc((opt.expiry + 1) * sizeof(double));
    // fill last time slice
    for (int i = 0; i <= opt.expiry; i++) {
        double underlying = binmodel_price(bm, opt.expiry, i);
        prices[i] = opt.payoff(opt, underlying);
    }
    crr(bm, opt.expiry, prices);
    double result = prices[0];
    free(prices);
    return result;
}
