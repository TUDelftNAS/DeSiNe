/******************************************************************************

    source file DijkstraAlgorithm.cpp for class: DijkstraAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : August 2004

******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/DijkstraAlgorithm.h"
#include "Network/Flow.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/TraceManager.h"
#include <cfloat>
#include <cmath>
#include <vector>
using std::vector;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor DijkstraAlgorithm::DijkstraAlgorithm()
//------------------------------------------------------------------------------
DijkstraAlgorithm::DijkstraAlgorithm(const TString &args) :
                   Algorithm(args)
{
    TRACE("DijkstraAlgorithm::DijkstraAlgorithm -->");
    rng = RandomNumberGenerator::getRandomNumberGenerator();
    TRACE("DijkstraAlgorithm::DijkstraAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor DijkstraAlgorithm::~DijkstraAlgorithm()
//------------------------------------------------------------------------------
DijkstraAlgorithm::~DijkstraAlgorithm()
{
    TRACE("DijkstraAlgorithm::~DijkstraAlgorithm -->");
    // Empty
    TRACE("DijkstraAlgorithm::~DijkstraAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path WSDijkstraAlgorithm::compute()
//------------------------------------------------------------------------------
Path DijkstraAlgorithm::compute(const int &flow_source,
                                const int &flow_destination,
                                Topology* topology)
{
    TRACE("DijkstraAlgorithm::compute -->");
    Path result;

    const int number_of_nodes = topology->getNumNodes();
    struct NodeLabel
    {
        int     predecessor;
        double  length;
        bool    visited;
    };
    NodeLabel* state = new NodeLabel[number_of_nodes];

    // Initialization
    for (int counter = 0; counter < number_of_nodes; ++counter)
    {
        // CHANGED FROM 0 TO (N+1) BECAUSE TOPOLOGY STARTS COUNTING AT NODE 0
        state[counter].predecessor = number_of_nodes + 1;
        state[counter].length = DBL_MAX;
        state[counter].visited  = false;
    }
    int worknode = flow_source; // First worknode is the wource
    state[worknode].length = 0.0;
    state[worknode].visited = true;

    // Repeat until destination has been visited
    while(!state[flow_destination].visited && worknode != -1)
    {
        // Find all adjacent nodes to worknode and update length
        //ERROR(worknode << ' ' << state[worknode].visited << ' ' << topology->getNodalDegree(worknode));
        for (LinkListIterator worklink = topology->getLinkIterator(worknode);
            worklink(); ++worklink)
        {
//            (*worklink)->print(logid);
            int destination = (*worklink)->getDestination();
            double metric = (*worklink)->metric;
            if ( (metric >= 0.0) && !state[destination].visited)
            {
                if (state[worknode].length + metric < state[destination].length)
                {
                    state[destination].predecessor = worknode;
                    state[destination].length = state[worknode].length + metric;
                    //ERROR("-" << destination << ' ' << state[destination].length);
                } // end if
            } // end if
        }// end for LinkListIterator

        // Find node with minimum length that has not been visited yet
        // 3-9-2006 : In case of equal nodes, a random node is picked!
        double min = DBL_MAX;
        worknode = -1;
        vector<int> worknodes;
        for (int iter = 0 ; iter < number_of_nodes; ++iter)
        {
            if (!state[iter].visited)
            {
                if (state[iter].length < min)
                {
                    worknodes.clear();
                    worknodes.push_back(iter);
                    min = state[iter].length;
                } else
                if ( (state[iter].length == min) && !worknodes.empty() )
                {
                    worknodes.push_back(iter);
                } // end if (!state[iter].
            }
        } // end for (int iter = 0

        // pick random worknode from the worknodes vector
        if (!worknodes.empty())
        {
            worknode = worknodes.at( (size_t) ceil( ((double) worknodes.size()) *
                rng->generate()) - 1);
            // Set label for new worknode
            state[worknode].visited = true;
        }
    } // end: while...

    // path calculation
    if (state[flow_destination].visited) // path was found
    {
        worknode = flow_destination;
        while (worknode != flow_source)
        {
            // add node at front because dijktra
            // calculates path in reverse order
            result.push_front(worknode);
            worknode = state[worknode].predecessor;
        }
        result.push_front(flow_source);
    }

    delete [] state;

    TRACE("DijkstraAlgorithm::compute <--");
    return result;
}
