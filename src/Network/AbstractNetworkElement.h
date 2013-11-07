#ifndef ABSTRACTNETWORKELEMENT_H
#define ABSTRACTNETWORKELEMENT_H
/******************************************************************************

    header file AbstractNetworkElement.h for class: AbstractNetworkElement

    This class is meant to represent the abstract base interface for all
    network elements.


    Author : T. Kleiberg
    Version: 1
    Date   : Dec 2004

******************************************************************************/


// Include(s)
//#include "Network/AbstractNetworkElementVisitor.h"

class AbstractNetworkElementVisitor;

class AbstractNetworkElement
{
    public:
//------------------------------------------------------------------------------
//  ~AbstractNetworkElement()
//
//  Virtual destructor declaration
//
//------------------------------------------------------------------------------
    virtual ~AbstractNetworkElement() {}


//------------------------------------------------------------------------------
//  acceptNetworkElementVisitor(AbstractNetworkElementVisitor& anev);
//
//  Accepts and executes a network element visitor
//
//------------------------------------------------------------------------------
    virtual void accept(AbstractNetworkElementVisitor& anev) = 0;

}; //end declarations
#endif //ABSTRACTNETWORKELEMENT_H
