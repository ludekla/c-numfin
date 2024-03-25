/** @file option.c
 *  @brief Option models and payoffs.
 *  
 *  Implementation of Option structs and payoff functions.
 * 
 *  @author Lutz
*/

#include "option.h"

// Vanilla Option functions
void voption_init(VanillaOption *opt, OptionType opt_type, double k, int t) {
    opt->strike = k;
    opt->expiry = t;
    switch (opt_type) {
        case CALL: opt->payoff = call_payoff; break;
        case PUT: opt->payoff = put_payoff; break;
        case DIGITAL_CALL: opt->payoff = dcall_payoff; break;
        case DIGITAL_PUT: opt->payoff = dput_payoff;
    }
}

// Double Digital Option functions
void soption_init(
    SpreadOption *opt, 
    OptionType opt_type, 
    double k_lo, 
    double k_hi, 
    int t
) {
    opt->strike_lo = k_lo;
    opt->strike_hi = k_hi;
    opt->expiry = t;
    switch (opt_type) {
    case DOUBLE_DIGIT:
        opt->payoff = double_payoff;
        break;
    case BEAR_SPREAD:
        opt->payoff = bear_payoff;
        break;
    case BULL_SPREAD:
        opt->payoff = bull_payoff;
        break;
    }
}

// payoff functions
double call_payoff(VanillaOption opt, double price) {
    return (price > opt.strike) ? price - opt.strike : 0.0;
}

double put_payoff(VanillaOption opt, double price) {
    return (price > opt.strike) ? 0.0 : opt.strike - price;
}

double dcall_payoff(VanillaOption opt, double price) {
    return (price > opt.strike) ? 1.0 : 0.0;
}

double dput_payoff(VanillaOption opt, double price) {
    return (price > opt.strike) ? 0.0 : 1.0;
}

double double_payoff(SpreadOption opt, double price) {
    return (price >= opt.strike_lo && price <= opt.strike_hi) ? 1.0 : 0.0;
}

double bear_payoff(SpreadOption opt, double price) {
    if (price < opt.strike_lo)
        return opt.strike_hi - opt.strike_lo;
    else if (price > opt.strike_hi)
        return 0.0;
    else
        return opt.strike_hi - price;
}

double bull_payoff(SpreadOption opt, double price) {
    if (price > opt.strike_lo)
        return opt.strike_hi - opt.strike_lo;
    else if (price < opt.strike_hi)
        return 0.0;
    else
        return price - opt.strike_lo;
}