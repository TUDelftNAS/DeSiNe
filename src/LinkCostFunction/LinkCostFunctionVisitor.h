#ifndef LINKCOSTFUNCTIONVISITOR_H
#define LINKCOSTFUNCTIONVISITOR_H
/******************************************************************************

    header file LinkCostFunctionVisitor.h for class:
    LinkCostFunctionVisitor

    This class is meant to represent an instance of ANEV for link cost function


    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElement.h"
#include "Network/AbstractNetworkElementVisitor.h"
#include "Utils/TraceManager.h"
#include <string>
#include <ostream>
using std::ostream;
using std::string;

class LinkCostFunctionVisitor : public AbstractNetworkElementVisitor
{
    public:
//------------------------------------------------------------------------------
//  LinkCostFunctionVisitor()
//
//  Constructor
//
//------------------------------------------------------------------------------
    LinkCostFunctionVisitor() {}

//------------------------------------------------------------------------------
//  ~LinkCostFunctionVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    virtual ~LinkCostFunctionVisitor() {}


//------------------------------------------------------------------------------
//  double getCost();
//
//  Get the getCost
//
//------------------------------------------------------------------------------
    virtual double getCost(const AbstractNetworkElement *anev) const = 0;


//------------------------------------------------------------------------------
//  void print()
//
//  Print the visitor description to a buffer
//
//------------------------------------------------------------------------------
    void print(ostream &buffer) const
    {
        TRACE("LinkCostFunctionVisitor::print -->");
        buffer << getName();
        TRACE("LinkCostFunctionVisitor::print <--");
    }



//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    virtual string getName() const = 0;


//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("LinkCostFunctionVisitor::visitLink -->");
        //empty
        TRACE("LinkCostFunctionVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLinkList(const AbstractNetworkElement* linklist)
    {
        TRACE("LinkCostFunctionVisitor::visitLinklist -->");
        //empty
        TRACE("LinkCostFunctionVisitor::visitLinklist <--");
    }


//------------------------------------------------------------------------------
//  void visitTopology(const AbstractNetworkElement& topology)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitTopology(const AbstractNetworkElement* topology)
    {
        TRACE("LinkCostFunctionVisitor::visitTopology -->");
        //empty
        TRACE("LinkCostFunctionVisitor::visitTopology <--");
    }

}; //end declarations
#endif //LINKCOSTFUNCTIONVISITOR_H
