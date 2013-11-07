#ifndef TEDBALGORITHM_H
#define TEDBALGORITHM_H
/******************************************************************************

    header file TEDBAlgorithm.h for class: TEDBAlgorithm

    This function performs the TEDB algorithm. It performs NewMIRA before
    invoking the Tamcra algorithm.

    No arguments are accepted. The default linkcost function is TEDBlc.

    Author : T. Kleiberg
    Version: 1
    Date   : July 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
using Types::TString;



class TEDBAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s
    private:
    Algorithm* new_mira;    // Used internally
    Algorithm* shr_path;    // Used internally
    //Algorithm* tamcra;


    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor TEDBAlgorithm();
//
//  Constructs TEDBAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    TEDBAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~TEDBAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~TEDBAlgorithm();


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
#endif //TEDBALGORITHM_H
