/** @file crr.h
 *  @brief Structs and function prototypes for the CRR model.
 * 
 *  Implementation of the Cox-Ross-Rubinstein Pricer (Binomial Model).
 * 
 *  @author Lutz 
*/

#ifndef _CRR_H
#define _CRR_H

/** @struct BinModel 
 * 
 *  Holds the parameters of the binomial market model. 
 *  
 *  @var spot Spot price of the underlying.
 *  @var uptick Relative uptick of the underlying. 
 *  @var downtick Relative downtick of the underlying.
 *  @var rate Risk-free rate (of a bond).
*/
typedef struct {
    double spot;      
    double uptick; 
    double downtick;  
    double rate;    
} BinModel;

/** @typedef Payoff 
 *  Payoff function for the contingent claim.
*/
typedef double (*Payoff)(double price, double strike);

/** @struct EurOption
 *  
 *  Holds the strike price of a European option and 
 *  a pointer to its payoff function.
 * 
 *  @var strike Strike price.
 *  @var expiry Expiry of the option. 
 *  @var payoff Function pointer to payoff function. 
*/
typedef struct {
    double strike;
    double expiry;
    Payoff payoff;
} EurOption;

/** @fn binmodel_init
*   @brief Initialise binomial model
*   @param bm Pointer to the BinModel struct to be initialised.
*   @param s Spot price of the underlying.
*   @param u Uptick parameter of the model.
*   @param d downtick parameter of the model.
*   @param r Risk-neutral probability.
*/
void binmodel_init(BinModel *bm, double s, double u, double d, double r);

/** @fn binmodel_prob 
*   @brief Computes risk-neutral probability.
*   @param bm Pointer to the BinModel struct.
*   @return Risk-neutral probability (aka martingale probability).
*/
double binmodel_prob(BinModel * bm);

/** @fn binmodel_price 
*   @brief Computes the price of the underlying after n upticks.
*   @param bm Pointer to the BinModel struct.
*   @param expiry Expiry of the option.
*   @param n_upticks Number of upticks undergone by the underlying.
*/ 
double binmodel_price(BinModel *bm, int expiry, int n_upticks);

// European Option functions
/** @brief initialise EurOption struct
*   @param opt Pointer to a EurOption struct.
*   @param payoff Function pointer to payoff function.
*   @param k Strike price.
*   @param t Expiry of the option.
*/
void euroption_init(EurOption *opt, Payoff payoff, double k, int t);

/** @fn call_payoff
*   @brief Computes the payoff of the call option at expiry.
*   @param price Current price of the underlying.
*   @param strike Strike price of the call option.
*   @return Call option price at expiry.
*/
double call_payoff(double price, double strike);

/** @fn put_payoff
*   @brief Computes the payoff of the put option at expiry.
*   @param price Current price of the underlying.
*   @param strike Strike price of the put option.
*   @return Put option price at expiry.
*/
double put_payoff(double price, double strike);

/** @fn digital_call_payoff
*   @brief Computes the payoff of the digital call option at expiry.
*   @param price Current price of the underlying.
*   @param strike Strike price of the call option.
*   @return Call option price at expiry.
*/
double digital_call_payoff(double price, double strike);

/** @fn digital_put_payoff
*   @brief Computes the payoff of the digital put option at expiry.
*   @param price Current price of the underlying.
*   @param strike Strike price of the put option.
*   @return Put option price at expiry.
*/
double digital_put_payoff(double price, double strike);

/** @fn price_by_crr
*   @brief CRR pricing function
*   @param bm Pointer to the BinModel struct.
*   @param opt Pointer to a EurOption struct.
*   @return Price of the option.
*/
double price_by_crr(BinModel * bm, EurOption * opt);

#endif /* _CRR_H */