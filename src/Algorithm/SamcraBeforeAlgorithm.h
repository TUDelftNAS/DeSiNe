#ifndef SAMCRABEFOREALGORITHM_H
#define SAMCRABEFOREALGORITHM_H
/******************************************************************************

    header file SamcraBeforeAlgorithm.h for class: SamcraBeforeAlgorithm

    This function performs the Samcra algorithm (Samcra_before). It performs
    the capacity checks before invoking the Samcra algorithm.

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



class SamcraBeforeAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s
/*
    protected:
    Algorithm* sp_algo;
*/
    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor SamcraBeforeAlgorithm();
//
//  Constructs SamcraBeforeAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    SamcraBeforeAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~SamcraBeforeAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~SamcraBeforeAlgorithm();


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
#endif //SAMCRABEFOREALGORITHM_H
