/******************************************************************************

    source file SMIRAAlgorithm.cpp for class: SMIRAAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/DijkstraAlgorithm.h"
#include "Algorithm/SMIRAAlgorithm.h"
#include "Algorithm/WSDijkstraAlgorithm.h"
#include "Network/Flow.h"
#include "Network/Link.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Timer.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include "Utils/Utils.h"
#include "prf/types_pr.h"
#include <cfloat>
#include <cmath>
#include <cstring>
#include <map>
using Types::IntVector;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor SMIRAAlgorithm::SMIRAAlgorithm()
//------------------------------------------------------------------------------
SMIRAAlgorithm::SMIRAAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("SMIRAAlgorithm::SMIRAAlgorithm -->");
    dijkstra_alg   = new DijkstraAlgorithm(args);
    wsdijkstra_alg = new WSDijkstraAlgorithm(args);
    TRACE("SMIRAAlgorithm::SMIRAAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor SMIRAAlgorithm::~SMIRAAlgorithm()
//------------------------------------------------------------------------------
SMIRAAlgorithm::~SMIRAAlgorithm()
{
    TRACE("SMIRAAlgorithm::~SMIRAAlgorithm -->");
    delete dijkstra_alg;
    delete wsdijkstra_alg;
    TRACE("SMIRAAlgorithm::~SMIRAAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path* SMIRAAlgorithm::compute(Flow* flow)
//------------------------------------------------------------------------------
Path SMIRAAlgorithm::compute(const Flow &flow)
{
    TRACE("SMIRAAlgorithm::compute -->");

    const int a = 1;
    const int w = 2;
    const int K = 4;
    const int f_dst = flow.getDestination();
    const int f_src = flow.getSource();
    Topology *topology = flow.getTopology();
    int number_of_nodes = topology->getNumNodes();

    typedef map<int, double> IntDoubleMap;
    IntDoubleMap* coeffs = new IntDoubleMap[number_of_nodes];
    // Initializing multiplicative coeffs
    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        Link* link = *iter;
        coeffs[link->getSource()][link->getDestination()] = 1.0;
    } // end: for (LinkListIterator iter

    // Start timer
#ifndef NO_TIMER
    Timer timer;
    timer.start();
#endif // NO_TIMER

    const IntVector edge_nodes = topology->getEdgeNodes();

    for (IntVector::const_iterator s_iter = edge_nodes.begin();
                                   s_iter != edge_nodes.end(); ++s_iter)
    {
        for (IntVector::const_iterator d_iter = edge_nodes.begin();
                                       d_iter != edge_nodes.end(); ++d_iter)
        {
            if (*s_iter != *d_iter && !(f_src == *s_iter && f_dst == *d_iter))
            {
                // Reset static link costs
                for (LinkListIterator iter = topology->getLinkIterator();
                     iter(); ++iter)
                {
                    Link* link = *iter;
                    link->metric = link->getCapacity() > 0 ? 1.0 : -1.0;
                } // end: for (LinkListIterator iter

                int k = 0;
                do
                {
                    Path wsd = wsdijkstra_alg->compute(*s_iter, *d_iter, topology);
                    if (wsd.size() > 0)
                    {
                        // Find smallest link (bottleneck)
                        double btl = DBL_MAX;
                        for (int ix = wsd.size() - 1 ; ix > 0; --ix)
                        {
                            double cap = topology->link(wsd[ix],
                                         wsd[ix - 1])->getReservableCapacity();
                            btl = cap < btl ? cap : btl;
                        } // end: for (int ix
                        for (int ix = wsd.size() - 1 ; ix > 0; --ix)
                        {
                            Link* link = topology->link(wsd[ix], wsd[ix - 1]);
                            double cap = link->getReservableCapacity();
                            // Updating link multiplicative coefficients
                            coeffs[link->getSource()][link->getDestination()] +=
                                w * a * (K-k) / K * btl * cap;
                            // Remove bottleneck links from topology
                            if (cap == btl) link->metric = -1.0;
                        } // end: for (int ix
                        ++k;
                    } // end: if (wsd.size()
                    else
                    {
                        // Break do-loop
                        k = K;
                    }
                } while (k < K); // end: do
            } // end: if (*s_iter
        } // end: for (IntVector::const_iterator
    } // end: for (IntVector::const_iterator

    // Now pruning links with insuff. bandwidth
    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        Link* link = *iter;
        link->metric =
            link->getReservableCapacity() < flow.getRequestedCapacity() ?
            -1.0 : coeffs[link->getSource()][link->getDestination()];
    } // end: for (LinkListIterator iter

    // invoking Dijkstra
    Path result(dijkstra_alg->compute(flow));
#ifndef NO_TIMER
    const_cast<Flow&>(flow).setTime(timer.read());
#endif // NO_TIMER

    delete [] coeffs;

    TRACE("SMIRAAlgorithm::compute <--");
    return result;
}
