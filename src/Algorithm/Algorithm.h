#ifndef ALGORITHM_H
#define ALGORITHM_H
/******************************************************************************

    header file Algorithm.h for class: Algorithm

    This class is meant to represent the interface for algorithm
    implementations. It must be implemented by a subclass with specific details
    about the algorithm (e.g. Dijkstra). The class-group must form an adapter
    to the external classes 'Samcra'.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
#include <ostream>
using Types::TString;
using std::ostream;

class Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s)
    protected:
    TString arguments;

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor Algorithm();
//
//  Constructs Algorithm with parameters
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    Algorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~Algorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~Algorithm();


//------------------------------------------------------------------------------
//  virtual Path compute(const Flow &flow)
//
//  Computes the Path for a given flow according to the implementation of the
//  algorithm.
//  Input : the flow for which to find a path
//  Output:
//      - : the calculated path
//------------------------------------------------------------------------------
    virtual Path compute(const Flow &flow) = 0;


//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//
//  print the description of the algorithm to a buffer
//  Input : buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer);

}; //end declarations
#endif //ALGORITHM_H
