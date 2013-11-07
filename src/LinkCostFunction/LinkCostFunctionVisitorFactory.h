#ifndef LINKCOSTFUNCTIONVISITORFACTORY_H
#define LINKCOSTFUNCTIONVISITORFACTORY_H

/******************************************************************************

    header file LinkCostFunctionVisitorFactory.h for class:
            LinkCostFunctionVisitorFactoryFactory

    This forms the factory that creates the LinkSost function visitors

    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/


#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;

class LinkCostFunctionVisitorFactory
{
    // Constanst(s)

   // Variable(s)
    protected:
    // Function(s) declarations

    public:
//------------------------------------------------------------------------------
//
//  constructor LinkCostFunctionVisitorFactory();
//
//  Constructs LinkCostFunctionVisitorFactory with a specified LSUPolicy.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    LinkCostFunctionVisitorFactory();


//------------------------------------------------------------------------------
//
//  destructor ~LinkCostFunctionVisitorFactory()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LinkCostFunctionVisitorFactory();


//------------------------------------------------------------------------------
//  LinkCostFunctionVisitor* create();
//  Creates the new LinkCostFunctionVisitor
//  Input : the description of for the new lcf
//  Output:
//      - : the new LinkCostFunctionVisitor
//-----------------------------------------------------------------------------
    LinkCostFunctionVisitor* create(const string &specs);

  };
#endif//LINKCOSTFUNCTIONVISITORFACTORY_H
