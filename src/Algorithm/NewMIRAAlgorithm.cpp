/******************************************************************************

    source file NewMIRAAlgorithm.cpp for class: NewMIRAAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/DijkstraAlgorithm.h"
#include "Algorithm/NewMIRAAlgorithm.h"
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
#include <cmath>
#include <cstring>
using Types::IntVector;

extern "C" int maxflow(char**,node**,arc**,long**,double*,long*);

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor NewMIRAAlgorithm::NewMIRAAlgorithm()
//------------------------------------------------------------------------------
NewMIRAAlgorithm::NewMIRAAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("NewMIRAAlgorithm::NewMIRAAlgorithm -->");

    routing_alg = new DijkstraAlgorithm(args);

    TRACE("NewMIRAAlgorithm::NewMIRAAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor NewMIRAAlgorithm::~NewMIRAAlgorithm()
//------------------------------------------------------------------------------
NewMIRAAlgorithm::~NewMIRAAlgorithm()
{
    TRACE("NewMIRAAlgorithm::~NewMIRAAlgorithm -->");

    delete routing_alg;

    TRACE("NewMIRAAlgorithm::~NewMIRAAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path* NewMIRAAlgorithm::compute(Flow* flow)
//------------------------------------------------------------------------------
#define N_NODE( i ) ( (i) - ndp + nmin )
#define N_ARC( a )  ( ( a == NULL )? -1 : (a) - arp )
Path NewMIRAAlgorithm::compute(const Flow &flow)
{
    TRACE("NewMIRAAlgorithm::compute -->");

    Topology *topology = flow.getTopology();
    const int f_src = flow.getSource();
    const int f_dst = flow.getDestination();

    // if link (i,j) exists, its metric is initialized with 0 (it increases each
    // time a maxflow computation is performed) and it is added to the list that
    // feeds the maxflow function
    int numarcs = 0;
    int number_of_nodes = topology->getNumNodes();

    // data structure passed to maxflow function
    char** network = (char**) calloc(4, sizeof(char*));

    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        Link* link = *iter;
        if (link->getCapacity() > 0.0)
        {
            link->metric = 0.0;
            ++numarcs;
            network = (char**) realloc(network, (numarcs+4)*sizeof(char*));
            network[numarcs+2] = (char*) calloc(20, sizeof(char));
            sprintf(network[numarcs+2],"a %d %d %d",
                link->getSource(), link->getDestination(),
                (int) floor(link->getReservableCapacity()));
        } // end: if (link->
    } // end: for (LinkListIterator iter

    network[0] = (char*) calloc(20, sizeof(char));   // problem description
    network[1] = (char*) calloc(20, sizeof(char));   // source node
    network[2] = (char*) calloc(20, sizeof(char));   // destination node
    network[numarcs+3] = (char*) 0;       // NULL terminated array
    sprintf(network[0],"p max %d %d", number_of_nodes, numarcs);

#ifndef NO_TIMER
    Timer timer;
    timer.start();
#endif // NO_TIMER
    // Compute maxflow for each ingress-egress pair except (source,dest).
    // Each computation updates link weights

    //Timer timemaxflow;
    //timemaxflow.start();
    //int n = 0;

    const IntVector edge_nodes = topology->getEdgeNodes();

    for (IntVector::const_iterator s_iter = edge_nodes.begin();
                                   s_iter != edge_nodes.end(); ++s_iter)
    {
        for (IntVector::const_iterator d_iter = edge_nodes.begin();
                                       d_iter != edge_nodes.end(); ++d_iter)
        {
            if (*s_iter != *d_iter && !(f_src == *s_iter && f_dst == *d_iter))
            {

                //PRINTLN("s: " << *s_iter << "\td: " << *d_iter << "\tn: " << n);
                //n++;

                // complete network with current ingress-egress pair
                sprintf(network[1],"n %d s", *s_iter);
                sprintf(network[2],"n %d t", *d_iter);

                // needed by maxflow function
                node *ndp;
                arc *arp;
                long *cap;
                double mflow;
                long nmin;

                //compute maxflow
                //Timer t;
                //t.start();
                maxflow(network,&ndp,&arp,&cap,&mflow,&nmin);

                //PRINTLN("\tTimer: " << t.read());

                // update link weights
                for (node* in = ndp; in < (ndp + number_of_nodes); ++in)
                {
                    for (arc* a = in->first; a != 0; a = a->next)
                    {
                        long ni = N_NODE(in);
                        long na = N_ARC(a);
                        if ( cap[na] > 0 )
                        {
                            Link* link = topology->link(ni, N_NODE(a->head));
                            link->metric +=(cap[na] - a->r_cap) /
                                           (mflow*link->getReservableCapacity());
                        } // end: if ( cap[na] > 0 )
                    } // end: for ( arc*
                } // end: for (node*
                // free memory
                free(ndp);
                free(arp);
                free(cap);
            } // end: if ( (source
        } // end: for (int dest
    } // end: for (int source

    //PRINTLN("Timer: " << timemaxflow.read() << "\tn:" << n);

    // free memory
    for (int i=0; i<numarcs+3; ++i)
    {
        free(network[i]);
    }
    free(network);

    double f_cap = flow.getRequestedCapacity();
    // pruning of the links with insufficient bandwidth
    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        if ((*iter)->getReservableCapacity() < f_cap)
        {
            (*iter)->metric = -1.0;
        }
    }
    // invoking Dijkstra
    Path result(routing_alg->compute(flow));
#ifndef NO_TIMER
    const_cast<Flow&>(flow).setTime(timer.read());
#endif // NO_TIMER

    TRACE("NewMIRAAlgorithm::compute <--");
    return result;
}
#undef N_ARC
#undef N_NODE
