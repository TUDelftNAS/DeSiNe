#ifndef LINKSTATEUPDATEVISITORFACTORY_H
#define LINKSTATEUPDATEVISITORFACTORY_H

/******************************************************************************

    header file LinkStateUpdateVisitorFactory.h for class:
            LinkStateUpdateVisitorFactoryFactory

    See header file for details

    Author : Bingjie FU
    Version: 1
    Date   : Jan 2005

******************************************************************************/


#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Utils/Types.h"
using Types::TString;

class LinkStateUpdateVisitorFactory
{

    // Constanst(s)

    // Variable(s)

    // Function(s) declarations

    public:
//------------------------------------------------------------------------------
//
//  constructor LinkStateUpdateVisitorFactory();
//
//  Constructs LinkStateUpdateVisitorFactory with a specified LSUPolicy.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    LinkStateUpdateVisitorFactory();


//------------------------------------------------------------------------------
//
//  destructor ~LinkStateUpdateVisitorFactory()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LinkStateUpdateVisitorFactory();


//------------------------------------------------------------------------------
//  LinkStateUpdateVisitor* create();
//  Creates the new LinkStateUpdateVisitor
//  Input : the descrition of for the new lsu policy
//  Output:
//      - : the new LinkStateUpdateVisitor
//-----------------------------------------------------------------------------
    LinkStateUpdateVisitor* create(const TString &specs);

  };
#endif//LINKSTATEUPDATEVISITORFACTORY_H
