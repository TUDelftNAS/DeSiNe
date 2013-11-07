/******************************************************************************

    source file DegreeDistributionVisitor.cpp for class:
    DegreeDistributionVisitor

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Nov 2004

******************************************************************************/



// Include(s)
#include "Network/DegreeDistributionVisitor.h"
#include "Network/LinkList.h"
#include "Network/Topology.h"

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//------------------------------------------------------------------------------
void DegreeDistributionVisitor::visitLinkList(const AbstractNetworkElement* linklist)
{
    TRACE("DegreeDistributionVisitor::visitLinkList -->");
    for (LinkList::IntIntLinkMap::const_iterator iter = ((LinkList*) linklist)->link_map->begin();
        iter != ((LinkList*) linklist)->link_map->end(); ++iter)
    {
        distribution.add(iter->second->size());
    }
    TRACE("DegreeDistributionVisitor::visitLinkList <--");
}


//------------------------------------------------------------------------------
//  void visitTopology(const AbstractNetworkElement& topology)
//------------------------------------------------------------------------------
void DegreeDistributionVisitor::visitTopology(const AbstractNetworkElement* topology)
{
    TRACE("DegreeDistributionVisitor::visitTopology -->");
    //Empty
    TRACE("DegreeDistributionVisitor::visitTopology <--");
}
