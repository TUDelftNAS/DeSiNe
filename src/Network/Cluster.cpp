/******************************************************************************

    source file Cluster.cpp for class: Cluster

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/AbstractNetworkElement.h"
#include "Network/Cluster.h"
#include "Network/Topology.h"
#include "Utils/Types.h"
#include <ostream>
using std::endl;
using std::ostream;
using Types::IntVector;
using Types::IntSet;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  ClusterIterator getIterator();
//------------------------------------------------------------------------------
ClusterIterator Cluster::getIterator() const
{
    return ClusterIterator(nodes);
}

//------------------------------------------------------------------------------
//  void print(int LogManagerID)
//------------------------------------------------------------------------------
void Cluster::print(ostream& buffer) const
{
    buffer << "Cluster.start" << endl;
    buffer << "Size: " << size() << " >" << endl;
    for (IntSet::const_iterator iter = nodes.begin(); iter != nodes.end(); ++iter)
    {
        buffer << *iter << " ";
    }
    buffer << endl;
    buffer << "Cluster.end" << endl;
}


//------------------------------------------------------------------------------
//  depthFirstSearch(int source)
//------------------------------------------------------------------------------
void Cluster::depthFirstSearch(const int& source)
{
    nodes.insert(source);
    for (LinkListIterator iter = ((Topology*) topology)->getLinkIterator(source);
         iter(); ++iter)
    {
        Link* link = *iter;
        //PRINT( link->getReservableCapacity() << " ");
        if (link->getReservableCapacity()>0)
        {
            int destination = link->getDestination();
            if ( !isMember(destination) )
            {
                //PRINT( "destination " << destination << " ");
                depthFirstSearch(destination);
            }
        }
    }
}


//------------------------------------------------------------------------------
//  Cluster& operator-=(const Cluster& clust)
//------------------------------------------------------------------------------
Cluster& Cluster::operator-=(Cluster& clust)
{
    for (ClusterIterator iter = clust.getIterator(); iter(); ++iter)
    {
        nodes.erase(*iter);
    }
    return *this;
}

//------------------------------------------------------------------------------
//  Cluster& operator-=(const Cluster& clust)
//------------------------------------------------------------------------------
Cluster& Cluster::operator-=(IntVector& array)
{
    for (IntVector::const_iterator iter = array.begin(); iter != array.end();
         ++iter)
    {
        nodes.erase(*iter);
    }
    return *this;
}
