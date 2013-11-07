#ifndef SAMCRAAFTERALGORITHM_H
#define SAMCRAAFTERALGORITHM_H
/******************************************************************************

    header file SamcraAfterAlgorithm.h for class: SamcraAfterAlgorithm

    This function performs the Samcra algorithm (Samcra_after). It performs
    the capacity checks the Samcra algorithm has been performed. If the path
    found is insufficient, it will delete it.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
using Types::TString;



class SamcraAfterAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor SamcraAfterAlgorithm();
//
//  Constructs SamcraAfterAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    SamcraAfterAlgorithm(const TString &args);


    public:
//------------------------------------------------------------------------------
//
//  destructor ~SamcraAfterAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
//    ~SamcraAfterAlgorithm();


//------------------------------------------------------------------------------
//  Path compute(const Flow &flow)
//
//  Computes the Path for a given flow according to the implementation of the
//  algorithm.
//  Input : the flow for which to find a path
//  Output:
//      - : the calculated path
//------------------------------------------------------------------------------
    Path compute(const Flow &flow);

}; //end declarations
#endif //SAMCRAAFTERALGORITHM_H
