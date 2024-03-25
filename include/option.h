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
typedef enum { CALL, PUT, DIGITAL_CALL, DIGITAL_PUT } OptionType;

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

/** @struct DoubleOption
 *  
 *  Holds the strike prices of a double digital option.
 * 
 *  @var strike_lo Lower strike price.
 *  @var strike_hi Upper strike price.
 *  @var expiry Expiry of the option. 
*/
typedef struct {
    double strike_lo;
    double strike_hi;
    double expiry;
} DoubleOption;

/** @fn voption_init
*   @brief Initialise VanillaOption struct
*   @param opt Pointer to a VanillaOption struct.
*   @param k Strike price.
*   @param t Expiry of the option.
*/
void voption_init(VanillaOption *opt, OptionType opt_type, double k, int t);

/** @fn doption_init
*   @brief Initialise DoubleOption struct
*   @param opt Pointer to a DoubleOption struct.
*   @param k_lo Lower strike price.
*   @param k_hi Upper strike price.
*   @param t Expiry of the option.
*/
void doption_init(DoubleOption *opt, double k_lo, double k_hi, int t);

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
*   @return Put option price at expiry.
*/
double double_payoff(DoubleOption opt, double price);

#endif /*  _OPTION_H_ */
