#ifndef MIXEDVAR_H
#define MIXEDVAR_H
/******************************************************************************

    header file MixedVar.h for class: MixedVar

	This class implements the base-class RandomVar for a Mixed distr.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "RandomVariables/RandomVar.h"
#include "Utils/Types.h"
#include <ostream>
using Types::usi;
using Types::DblVector;
using std::ostream;


class MixedVar : public RandomVar
{
    // Typedefs
    public:
    typedef vector<RandomVar*> RandomVarVector;

   // Constanst(s)

    // Variable(s)
    private:
    RandomVarVector ran_vars;   // used for keeping reference to RandomVar** list
    DblVector probabilities;

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor MixedVar();
//
//  Constructs MixedVar.
//  Input :
//     rng   : the random number gen
//     rvars : the distributions
//     probs : the probabilities of occurence of the distributions
//  Output:
//
//------------------------------------------------------------------------------
    MixedVar(RandomNumberGenerator* rng,
             const RandomVarVector &rvars,
             const DblVector &probs);

//------------------------------------------------------------------------------
//
//  destructor ~MixedVar()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~MixedVar();


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
        double result = -1.0;
        double bound = 0.0;
        double distr = rng->generate(); // this selects the random var
        for (usi ix = 0; result == -1.0; ++ix)
        {
            bound += probabilities[ix];
            result = (distr <= bound) ? ran_vars[ix]->generate() : result;
        }
        return result;
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
#endif //MIXEDVAR_H
