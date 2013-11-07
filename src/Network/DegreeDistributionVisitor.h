#ifndef DEGREEDISTRIBUTIONVISITOR_H
#define DEGREEDISTRIBUTIONVISITOR_H
/******************************************************************************

    header file DegreeDistributionVisitor.h for class:
    DegreeDistributionVisitor

    This class is meant to represent an instance of ANEV for calculating
    the (nodal) degree distribution


    Author : T. Kleiberg
    Version: 1
    Date   : Nov 2004

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElementVisitor.h"
#include "Utils/DistributedVariable.h"
#include "Utils/Types.h"
using Types::uli;


class DegreeDistributionVisitor : public AbstractNetworkElementVisitor
{
    public:
    typedef DistributedVariable<uli> DistVar;

    private:
    DistVar distribution;

    public:
//------------------------------------------------------------------------------
//  DistVar& getDistribution()
//
//  Returns the result, the distribution of the nodal degree
//
//------------------------------------------------------------------------------
    DistVar& getDistribution()
    {
        return distribution;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link) {}


//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLinkList(const AbstractNetworkElement* linklist);


//------------------------------------------------------------------------------
//  void visitTopology(const AbstractNetworkElement& topology)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitTopology(const AbstractNetworkElement* topology);

}; //end declarations
#endif //DEGREEDISTRIBUTIONVISITOR_H
