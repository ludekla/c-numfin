/** @file crr.h
 *  @brief Structs and function prototypes for the CRR model.
 * 
 *  Implementation of the Cox-Ross-Rubinstein Pricer (Binomial Model).
 * 
 *  @author Lutz 
*/

#ifndef _CRR_H
#define _CRR_H

#include "option.h"

/** @struct BinModel 
 * 
 *  Holds the parameters of the binomial market model. 
 *  ion
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
*   @param bm BinModel struct.
*   @return Risk-neutral probability (aka martingale probability).
*/
double binmodel_prob(BinModel bm);

/** @fn binmodel_price 
*   @brief Computes the price of the underlying after n upticks.
*   @param bm BinModel struct.
*   @param expiry Expiry of the option.
*   @param n_upticks Number of upticks undergone by the underlying.
*/ 
double binmodel_price(BinModel bm, int expiry, int n_upticks);

/** @fn crr
*   @brief Non-public function for computing the option price by CRR
*   @param bm BinModel struct.
*   @param expiry Expiry of the option.
*   @param prices Array of prices.
*   @return Price of the option. 
*/
void crr(BinModel bm, int expiry, double * prices);

/** @fn voption_crr
*   @brief CRR pricing function for plain vanilla option.
*   @param bm BinModel struct.
*   @param opt VanillaOption struct.
*   @return Price of the option.
*/
double voption_crr(VanillaOption opt, BinModel bm);

/** @fn soption_crr
*   @brief CRR pricing function for a spread option.
*   @param bm BinModel struct.
*   @param opt SpreadOption struct.
*   @return Price of the spread option.
*/
double soption_crr(SpreadOption opt, BinModel bm);

#endif /* _CRR_H */