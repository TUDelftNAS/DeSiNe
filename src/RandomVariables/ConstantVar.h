#ifndef CONSTANTVAR_H
#define CONSTANTVAR_H
/******************************************************************************

    header file ConstantVar.h for class: ConstantVar

	This class implements the base-class RandomVar for a Constant distribution
	with constant value.

    Author : T. Kleiberg
    Version: 1
    Date   :
        July 2006

******************************************************************************/


// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include <ostream>
using std::ostream;


class ConstantVar : public RandomVar
{
    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor ConstantVar();
//
//  Constructs ConstantVar.
//  Input : constant value
//  Output:
//
//------------------------------------------------------------------------------
    ConstantVar(RandomNumberGenerator* rng, const double &val);


//------------------------------------------------------------------------------
//
//  destructor ~ConstantVar()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~ConstantVar();


//------------------------------------------------------------------------------
//  double generate();
//
//  Generate a new random variable according to the characteristics that were
//  given with the constructor.
//  Input :
//  Output:
//      - : the newly generated value
//------------------------------------------------------------------------------
    double generate()
    {
        return mean;
    }

//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints the specs of the random variable into a readable text format
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
	void print(ostream &buffer) const;

}; //end declarations
#endif //CONSTANTVAR_H
