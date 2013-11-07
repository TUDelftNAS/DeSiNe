/******************************************************************************

    source file WSDijkstraAlgorithm.cpp for class: WSDijkstraAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : August 2004

******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/WSDijkstraAlgorithm.h"
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
//  constructor WSDijkstraAlgorithm::WSDijkstraAlgorithm()
//------------------------------------------------------------------------------
WSDijkstraAlgorithm::WSDijkstraAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("WSDijkstraAlgorithm::WSDijkstraAlgorithm -->");
    rng = RandomNumberGenerator::getRandomNumberGenerator();
    TRACE("WSDijkstraAlgorithm::WSDijkstraAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor DijkstraAlgorithm::~DijkstraAlgorithm()
//------------------------------------------------------------------------------
WSDijkstraAlgorithm::~WSDijkstraAlgorithm()
{
    TRACE("WSDijkstraAlgorithm::~WSDijkstraAlgorithm -->");
    // Empty
    TRACE("WSDijkstraAlgorithm::~WSDijkstraAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path WSDijkstraAlgorithm::compute()
//------------------------------------------------------------------------------
Path WSDijkstraAlgorithm::compute(const int &flow_source,
                                  const int &flow_destination,
                                  Topology* topology)
{
    TRACE("WSDijkstraAlgorithm::compute -->");

    Path result;

    const int number_of_nodes = topology->getNumNodes();

    struct NodeLabel
    {
        int     predecessor;
        bool    visited;
        double  length;
        double  mrb;
    };
    NodeLabel* state = new NodeLabel[number_of_nodes];

    // Initialization
    for (int counter = 0; counter < number_of_nodes; ++counter)
    {
        // CHANGED FROM 0 TO (N+1) BECAUSE TOPOLOGY STARTS COUNTING AT NODE 0
        state[counter].predecessor = number_of_nodes + 1;
        state[counter].visited  = false;
        state[counter].length = DBL_MAX;
        state[counter].mrb = DBL_MAX;
    }
    int worknode = flow_source; // First worknode is the wource
    state[worknode].length = 0.0;
    state[worknode].visited  = true;

    // Repeat until destination has been visited
    while(!state[flow_destination].visited && worknode != -1)
    {
        // Find all adjacent nodes to worknode and update length
        for (LinkListIterator worklink = topology->getLinkIterator(worknode);
            worklink(); ++worklink)
        {
//            (*worklink)->print(logid);
            int destination = (*worklink)->getDestination();
            double metric = (*worklink)->metric;
            double rescap = (*worklink)->getReservableCapacity();
            if ( (metric >= 0.0) && !state[destination].visited)
            {
                if (state[worknode].length + metric < state[destination].length)
                {
                    state[destination].predecessor = worknode;
                    state[destination].length = state[worknode].length + metric;
                    state[destination].mrb = (rescap < state[worknode].mrb) ?
                        rescap : state[worknode].mrb;
                } else
                if (state[worknode].length + metric == state[destination].length)
                {
                    double newmrb = (rescap < state[worknode].mrb) ?
                        rescap : state[worknode].mrb;
                    if (newmrb > state[destination].mrb)
                    {
                        state[destination].predecessor = worknode;
                        state[destination].mrb = newmrb;
                    }
                } // end else if (state[worknode]....
            } // end if
        }// end for LinkListIterator

        // Find node with minimum length that has not been visited yet and has
        // largest mrb
        double min = DBL_MAX;
        double max = 0.0;
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
                    max = state[iter].mrb;
                } else // Find largest mrb
                if ( (state[iter].length == min) && !worknodes.empty() )
                {
                    if ( state[iter].mrb == max )
                    {
                        worknodes.push_back(iter);
                    } else
                    if ( state[iter].mrb > max )
                    {
                        worknodes.clear();
                        worknodes.push_back(iter);
                        max = state[iter].mrb;
                    }
                } // end if (state[].length
            } // end if (state[].visited
        } // end for

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
    worknode = flow_destination;

    if (state[worknode].predecessor != (number_of_nodes+1)) // A path was found
    {
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

    TRACE("WSDijkstraAlgorithm::compute <--");
    return result;
}
