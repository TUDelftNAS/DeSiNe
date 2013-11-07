#ifndef ABSTRACTNETWORKELEMENTVISITOR_H
#define ABSTRACTNETWORKELEMENTVISITOR_H
/******************************************************************************

    header file AbstractNetworkElementVisitor.h for class:
    AbstractNetworkElementVisitor

    This class is meant to represent the abstract base interface for all
    network element visitors.


    Author : T. Kleiberg
    Version: 1
    Date   : Nov 2004

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElement.h"


class AbstractNetworkElementVisitor
{
    public:
//------------------------------------------------------------------------------
//  void visit(const LinkList& linklist);
//
//  Virtual function that must be implemented by subclasses. This function is
//  called from the actual NE object.
//
//------------------------------------------------------------------------------
    virtual ~AbstractNetworkElementVisitor() {}

//------------------------------------------------------------------------------
//  void visit(const Link& linklist);
//
//  Virtual function that must be implemented by subclasses. This function is
//  called from the actual NE object.
//
//------------------------------------------------------------------------------
    virtual void visitLink(const AbstractNetworkElement* link) = 0;


//------------------------------------------------------------------------------
//  void visit(const LinkList& linklist);
//
//  Virtual function that must be implemented by subclasses. This function is
//  called from the actual NE object.
//
//------------------------------------------------------------------------------
    virtual void visitLinkList(const AbstractNetworkElement* linklist) = 0;


//------------------------------------------------------------------------------
//  void visit(const Topology& topology);
//
//  Virtual function that must be implemented by subclasses. This function is
//  called from the actual NE object.
//
//------------------------------------------------------------------------------
    virtual void visitTopology(const AbstractNetworkElement* topology) = 0;

}; //end declarations
#endif //ABSTRACTNETWORKELEMENTVISITOR_H
