#ifndef DESINEMODEL_H
#define DESINEMODEL_H
/******************************************************************************

    header file DesineModel.h for class: DesineModel

    This class runs a single simulation.
    In each run simulates given number of iterations.


    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Main/Data.h"
#include "Main/Model.h"
#include "Parameter/Parameters.h"

class DesineModel : public Model
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
    Parameters* parameters;
    Algorithm* algorithm;
    LinkStateUpdateVisitor* lsuv;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor DesineModel()
//  Constructs DesineModel with parameters and topology, SimulationDatabase and
//  algorithm.
//  Input :
//------------------------------------------------------------------------------
    DesineModel(Parameters* parameters, Algorithm* algorithm,
    	LinkStateUpdateVisitor* lsuv);


//------------------------------------------------------------------------------
//  destructor ~DesineModel()
//  Destructs DesineModel
//  Input :
//  Output:
//------------------------------------------------------------------------------
    virtual ~DesineModel();


//------------------------------------------------------------------------------
//  void execute();
//
//  Input : the number of iterations to perform
//  Output: the Data instance with the collected results
//------------------------------------------------------------------------------
    Data* execute(const int &iterations);

    // Private Function(s) definitions
}; //end declarations DesineModel
#endif // DESINEMODEL_H
