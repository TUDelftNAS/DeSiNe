#ifndef NEWMIRAALGORITHM_H
#define NEWMIRAALGORITHM_H
/******************************************************************************

    header file NewMIRAAlgorithm.h for class: NewMIRAAlgorithm

    This function performs the NewMIRA calculation on a graph.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "IO/Tag.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
using Types::TString;
#include <sstream>

class NewMIRAAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Algorithms using NewMIRA
    friend class TEDBAlgorithm;

    // Constanst(s)

    // Variable(s
    protected:
    Algorithm* routing_alg;

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor NewMIRAAlgorithm();
//
//  Constructs NewMIRAAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    NewMIRAAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~NewMIRAAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~NewMIRAAlgorithm();


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
#endif //NEWMIRAALGORITHM_H
