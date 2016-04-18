/******************************************************************************

    source file SamcraBAlgorithm.cpp for class: SamcraBAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/SamcraBAlgorithm.h"
#include "Network/Flow.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Timer.h"
#include "Utils/TraceManager.h"
#include "Utils/Utils.h"

#include <cstdlib>

extern "C" void samcra2path(int,int,int **,int *,double ***,
                           int,double *,int,int *,int *,int *,int *);


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor SamcraBAlgorithm::SamcraBAlgorithm()
//------------------------------------------------------------------------------
SamcraBAlgorithm::SamcraBAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("SamcraBAlgorithm::SamcraBAlgorithm -->");

    // Set link cost function
    // it is assumed that args second word is the linkcostfunction ID
    // if not, unexpected results may occur

    TRACE("SamcraBAlgorithm::SamcraBAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor SamcraBAlgorithm::~SamcraBAlgorithm()
//------------------------------------------------------------------------------
SamcraBAlgorithm::~SamcraBAlgorithm()
{
    TRACE("SamcraBAlgorithm::~SamcraBAlgorithm -->");
    // Empty
    TRACE("SamcraBAlgorithm::~SamcraBAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path SamcraBAlgorithm::compute(const Flow &flow)
//------------------------------------------------------------------------------
Path SamcraBAlgorithm::compute(const Flow &flow)
{
    TRACE("SamcraBAlgorithm::compute -->");

    Path result;

    Topology *topology = flow.getTopology();
    topology->setLinkCostFunction(arguments.at(1));
    int number_of_nodes = topology->getNumNodes();
    int number_of_qos = topology->getNumQos();
    int min_k = 0; int k_used = 0; // used by samcra
    int* max = (int*) calloc(number_of_nodes + 1, sizeof(int));
    int** adj = (int**) allocMatrix(number_of_nodes + 1,
                                    number_of_nodes + 1, sizeof(int));

    double* flow_qos = (double*) calloc(number_of_qos + 1, sizeof(double));
    double*** datadj = (double***) calloc(number_of_qos + 1, sizeof(double**));
    datadj[0] = (double**) allocMatrix(number_of_nodes + 1,
                                       number_of_nodes + 1, sizeof(double));
    for (int counter=1; counter <= number_of_qos; ++counter)
    {
        datadj[counter] = (double**) allocMatrix(number_of_nodes + 1,
                          number_of_nodes + 1, sizeof(double));
        flow_qos[counter] = flow.getQosCons()[counter-1];
    }

    // filling adj and datadj, while pruning links with insuf. available cap.
    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        Link* link = *iter;
        if (link->getReservableCapacity() >= flow.getRequestedCapacity())
        {
            int source = link->getSource();
            int destination = link->getDestination();
            adj[source + 1][++max[source + 1]] = destination + 1;
            for (int qos=1; qos <= number_of_qos; ++qos)
            {
                datadj[qos][source+1][max[source+1]] = link->getQoS(qos-1);
            } // end: for (qos
            datadj[0][source+1][max[source+1]] = link->getCost();
        } // end: if (link
    } // end: for (LinkListIterator

    // allocating memory for the path
    int path_length = 0;
    int* path = (int*) calloc(number_of_nodes + 1, sizeof(int));

    // invoking SAMCRA
    TRACE("SamcraBAlgorithm::compute: Invoking SAMCRA2");
#ifndef NO_TIMER
    Timer timer;
    timer.start();
#endif // NO_TIMER
    samcra2path( flow.getSource()+1, flow.getDestination()+1,
                 adj, max, datadj, number_of_qos, flow_qos,
                 number_of_nodes, path, &path_length, &min_k, &k_used);
    TRACE("SamcraBAlgorithm::compute: End SAMCRA2");

    // because function returns the path vector from the destination "d" to the
    // source "s" it is necessary to invert the array
    for (int counter=1; counter <= path_length; ++counter)
    {
        result.push_front(path[counter]-1);
    }
#ifndef NO_TIMER
    const_cast<Flow&>(flow).setTime(timer.read());
#endif // NO_TIMER

    // freeing memory
    free(path);
    for (int counter = 0; counter <= number_of_qos; ++counter)
    {
        freeMatrix((void**) datadj[counter], number_of_nodes + 1);
    }
    free(datadj);
    free(flow_qos);
    freeMatrix((void**) adj, number_of_nodes + 1);
    free(max);

    TRACE("SamcraBAlgorithm::compute <--");
    return result;
}
