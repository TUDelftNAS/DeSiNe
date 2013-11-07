#ifndef UNIFORMVAR_H
#define UNIFORMVAR_H
/******************************************************************************

    header file UniformVar.h for class: UniformVar

	This class implements the base-class RandomVar for a Uniform distribution
	ranging from [min, max).

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include <ostream>
using std::ostream;


class UniformVar : public RandomVar
{
    // Constanst(s)

    // Variable(s)
    private:
    double min, range;

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor UniformVar();
//
//  Constructs UniformVar.
//  Input : min and max of distribution
//  Output:
//
//------------------------------------------------------------------------------
    UniformVar(RandomNumberGenerator* rng, const double &min, const double &max);


//------------------------------------------------------------------------------
//
//  destructor ~UniformVar()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~UniformVar();


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

        return (rng->generate() * range + min);
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
#endif //UNIFORMVAR_H
