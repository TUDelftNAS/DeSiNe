#ifndef ALGORITHMFACTORY_H
#define ALGORITHMFACTORY_H
/******************************************************************************

    header file AlgorithmFactory.h for class: AlgorithmFactory

    This class is a factory for creating Algorithm objects. It follows the
    concrete factory design pattern. The arguments that define the algorithm
    to be built, are passed on as a string. The Factory then parses the string
    and constructs the object likewise.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Utils/Types.h"
using Types::TString;

class AlgorithmFactory
{

    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor AlgorithmFactory();
//
//  Constructs AlgorithmFactory
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    AlgorithmFactory();


//------------------------------------------------------------------------------
//
//  destructor ~AlgorithmFactory()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~AlgorithmFactory();


//------------------------------------------------------------------------------
//  Algorithm* create(TString* description);
//  Creates the new Algorithm
//  Input : the descrition of for the new algorithm
//  Output:
//      - : the new algorithm
//------------------------------------------------------------------------------
    Algorithm* create(const TString &description);

}; //end declarations
#endif //ALGORITHMFACTORY_H
