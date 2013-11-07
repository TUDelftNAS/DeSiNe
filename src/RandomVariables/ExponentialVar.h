#ifndef EXPONENTIALVAR_H
#define EXPONENTIALVAR_H
/******************************************************************************

    header file ExponentialVar.h for class: ExponentialVar

	This class implements the base-class RandomVar for a Exponential distr.


    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include <cfloat>
#include <cmath>
#include <ostream>
using std::log;
using std::ostream;


class ExponentialVar : public RandomVar
{
    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor ExponentialVar();
//
//  Constructs ExponentialVar.
//  Input : 'mean' of distribution
//  Output:
//
//------------------------------------------------------------------------------
    ExponentialVar(RandomNumberGenerator* rng, const double &mean);


//------------------------------------------------------------------------------
//
//  destructor ~ExponentialVar()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~ExponentialVar();


//------------------------------------------------------------------------------
//  double generate();
//
//  Generate a new random variable according to the characteristics that were
//  given with the constructor.
//  To convert a uniform [0, 1] RV to exponential distribution with mean m,
//  invert the cdf = 1 - exp(-m*x) -> x = -1/m * ln(1.0 - y) = x = -1/m * ln(y)
//  because y is uniform over [0, 1]
//  Input :
//  Output:
//      - : the newly generated value
//
//  For more info, see Alberto Leon-Carcia - Probability and Radnom Processes
//  for EE, Appendix C.
//------------------------------------------------------------------------------
    double generate()
    {
        // In case of 0, DBL_MAX is too large. Range of rng is [0, 1)
        // In case rng produces zero, check for zero!!
#if 0
        double x = 1.0 - rng->generate();
        return x ? -mean * log(x) : DBL_MAX;
        return x ? -mean * log(x) : generate();
        return -mean * log(x);
        double x = rng->generate();
        if (x == 0.0)
        {
            WARNING("RNG produces 0!!");
            exit(-1);
        }
        return -mean * log(x);
#endif
        return -mean * log(rng->generate());
    }


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints the specs of the random variable into a readable text format
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
	void print(ostream &buffer)  const;

}; //end declarations
#endif //EXPONENTIALVAR_H
