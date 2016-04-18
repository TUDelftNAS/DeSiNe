#ifndef SAMCRABALGORITHM_H
#define SAMCRABALGORITHM_H
/******************************************************************************

    header file SamcraBAlgorithm.h for class: SamcraBAlgorithm

    This function performs the Samcra algorithm (Samcra2). It performs
    the capacity checks before invoking the Samcra algorithm.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"



class SamcraBAlgorithm : public Algorithm
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
//  constructor SamcraBAlgorithm();
//
//  Constructs SamcraBAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    SamcraBAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~SamcraBAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~SamcraBAlgorithm();


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
#endif //SAMCRABALGORITHM_H
