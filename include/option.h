/** @file option.h
 *  @brief Header file for the options and payoff functions.  
 * 
 *  Implementation of Option structs and payoff function prototypes. 
 * 
 *  @author Lutz
*/

#ifndef _OPTION_H_
#define _OPTION_H_

/** @enum OptionType
 *  @brief Option type of the plain vanilla option.
*/
typedef enum {
    // plain vanilla with single strike parameter
    CALL, PUT, DIGITAL_CALL, DIGITAL_PUT,
    // options with spread: double-digital, bear and bull
    DOUBLE_DIGIT, BEAR_SPREAD, BULL_SPREAD
} OptionType;

/** @struct VanillaOption
 *  
 *  Holds the parameters of plain vanilla European (digital) 
 *  call or put option.
 * 
 *  @var opt_type Option type, call or put
 *  @var strike Strike price.
 *  @var expiry Expiry of the option.
*/
typedef struct VanillaOption_ {
    OptionType opt_type;
    double strike;
    double expiry;
    double (*payoff)(struct VanillaOption_ opt, double price);
} VanillaOption;

/** @struct SpreadOption
 *  
 *  Holds the strike prices of an double digital, bear of bull options.
 * 
 *  @var OptionType One of the 3 possible option types.
 *  @var strike_lo Lower strike price.
 *  @var strike_hi Upper strike price.
 *  @var expiry Expiry of the option. 
*/
typedef struct SpreadOption_ {
    OptionType opt_type;
    double strike_lo;
    double strike_hi;
    double expiry;
    double (*payoff)(struct SpreadOption_ opt, double price);
} SpreadOption;

/** @fn voption_init
*   @brief Initialise VanillaOption struct
*   @param opt Pointer to a VanillaOption struct.
*   @param k Strike price.
*   @param t Expiry of the option.
*/
void voption_init(VanillaOption *opt, OptionType opt_type, double k, int t);

/** @fn soption_init
*   @brief Initialise SpreadOption struct
*   @param opt Pointer to a SpreadOption struct.
*   @param opt_type Option type: double-digital, bull or bear 
*   @param k_lo Lower strike price.
*   @param k_hi Upper strike price.
*   @param t Expiry of the option.
*/
void soption_init(
    SpreadOption *opt, 
    OptionType opt_type, 
    double k_lo, 
    double k_hi, 
    int t
);

/** @fn call_payoff
*   @brief Computes the payoff of the call option at expiry.
*   @param opt VanillaOption struct.
*   @param price Current price of the underlying.
*   @return Call option price at expiry.
*/
double call_payoff(VanillaOption opt, double price);

/** @fn put_payoff
*   @brief Computes the payoff of the put option at expiry.
*   @param opt VanillaOption struct.
*   @param price Current price of the underlying.
*   @return Put option price at expiry.
*/
double put_payoff(VanillaOption opt, double price);

/** @fn dcall_payoff
*   @brief Computes the payoff of the digital call option at expiry.
*   @param price Current price of the underlying.
*   @return Call option price at expiry.
*/
double dcall_payoff(VanillaOption opt, double price);

/** @fn dput_payoff
*   @brief Computes the payoff of the digital put option at expiry.
*   @param opt VanillaOption struct.
*   @param price Current price of the underlying.
*   @return Put option price at expiry.
*/
double dput_payoff(VanillaOption opt, double price);

/** @fn double_payoff
*   @brief Computes the payoff of the double digital option at expiry.
*   @param opt DoubleOption struct.
*   @param price Current price of the underlying.
*   @return Double digital option price at expiry.
*/
double double_payoff(SpreadOption opt, double price);

/** @fn bear_payoff
*   @brief Computes the payoff of the bear spread option at expiry.
*   @param opt SpreadOption struct.
*   @param price Current price of the underlying.
*   @return bear spread option price at expiry.
*/
double bear_payoff(SpreadOption opt, double price);

/** @fn bull_payoff
*   @brief Computes the payoff of the bull spread option at expiry.
*   @param opt SpreadOption struct.
*   @param price Current price of the underlying.
*   @return bull spread option price at expiry.
*/
double bull_payoff(SpreadOption opt, double price);

#endif /*  _OPTION_H_ */
