#ifndef MODEL_H
#define MODEL_H
/******************************************************************************

    header file Model.h for class: Model

    This class runs a single simulation.
    In each run simulates given number of iterations.


    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "Main/Data.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;

class Model
{
    // Friends

    // Constanst(s)

    // Variable(s)
    protected:
    string name;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor Model()
//  Constructs Model
//  algorithm.
//  Input :
//------------------------------------------------------------------------------
    Model(const string &name = "") : name(name)
    {
        TRACE("Model::Model -->");
        // empty
        TRACE("Model::Model <--");
    }

//------------------------------------------------------------------------------
//  destructor ~Model()
//  Destructs Model
//  Input :
//  Output:
//------------------------------------------------------------------------------
    virtual ~Model() {};


//------------------------------------------------------------------------------
//  void execute();
//
//  Perform a number of  runs on the topology. The data object is created with
//  the new information. If the data object is not empty, the newly returned data
//  contains the toal resultswith weightfactor for the number of iterations.
//
//  Input : the number of iterations to perform
    //  Output: the Data instance with the collected results
//------------------------------------------------------------------------------
    virtual Data* execute(const int &iterations) = 0;

}; //end declarations Model
#endif // MODEL_H
