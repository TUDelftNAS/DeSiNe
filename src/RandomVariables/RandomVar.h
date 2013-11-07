#ifndef RANDOMVAR_H
#define RANDOMVAR_H
/******************************************************************************

    header file RandomVar.h for class: RandomVar

	This class is meant to represent the interface for random varibales.
	It must be implemented by a subclass with specific details about the
	distribution of the random variable (e.g. Uniform or Exponential). The
	class-group must form an adapter to the external classes 'NewRan'.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "Utils/TraceManager.h"
#include <ostream>
using std::ostream;


class RandomVar
{
    // Constanst(s)

    // Variable(s)
	protected:
    RandomNumberGenerator* rng;
    double mean, variance;

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor RandomVar();
//
//  Constructs RandomVar and sets the random generator, mean and variance
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    RandomVar(RandomNumberGenerator* rng, const double &mean, const double &var);


//------------------------------------------------------------------------------
//
//  destructor ~RandomVar()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~RandomVar();


//------------------------------------------------------------------------------
//  double generate();
//
//  Generate a new random variable according to the characteristics that were
//  given with the constructor.
//  Input :
//  Output:
//      - : the newly generated value
//------------------------------------------------------------------------------
    virtual double generate() = 0;


//------------------------------------------------------------------------------
//  double getMean() const
//
//  Return mean of distribution
//
//------------------------------------------------------------------------------
	double getMean() const;


//------------------------------------------------------------------------------
//  double getVariance() const
//
//  Return variance of distribution
//
//------------------------------------------------------------------------------
	double getVariance() const;


    public:
//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints the specs of the random variable into a readable text format
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
	virtual void print(ostream &buffer) const = 0;

}; //end declarations
#endif //RANDOMVAR_H
