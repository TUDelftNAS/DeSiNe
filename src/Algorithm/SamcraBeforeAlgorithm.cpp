/******************************************************************************

    source file SamcraBeforeAlgorithm.cpp for class: SamcraBeforeAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/SamcraBeforeAlgorithm.h"
#include "Network/Flow.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Timer.h"
#include "Utils/TraceManager.h"
#include "Utils/Utils.h"


extern "C" void samcrapath(int,int,int **,int *,double ***,
                           int,double *,int,int *,int *,int *,int *);


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor SamcraBeforeAlgorithm::SamcraBeforeAlgorithm()
//------------------------------------------------------------------------------
SamcraBeforeAlgorithm::SamcraBeforeAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("SamcraBeforeAlgorithm::SamcraBeforeAlgorithm -->");
    // Empty
    TRACE("SamcraBeforeAlgorithm::SamcraBeforeAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor SamcraBeforeAlgorithm::~SamcraBeforeAlgorithm()
//------------------------------------------------------------------------------
SamcraBeforeAlgorithm::~SamcraBeforeAlgorithm()
{
    TRACE("SamcraBeforeAlgorithm::~SamcraBeforeAlgorithm -->");
    TRACE("SamcraBeforeAlgorithm::~SamcraBeforeAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path SamcraBeforeAlgorithm::compute(const Flow &flow)
//------------------------------------------------------------------------------
Path SamcraBeforeAlgorithm::compute(const Flow &flow)
{
    TRACE("SamcraBeforeAlgorithm::compute -->");

    Path result;
    Topology *topology = flow.getTopology();
    int number_of_nodes = topology->getNumNodes();
    int number_of_qos = topology->getNumQos();
	int min_k = 0; int k_used = 0; // used by samcra
	int* max = (int*) calloc(number_of_nodes + 1, sizeof(int));
	int** adj = (int**) allocMatrix(number_of_nodes + 1,
	                                number_of_nodes + 1, sizeof(int));

	double* flow_qos = (double*) calloc(number_of_qos + 1, sizeof(double));
	double*** datadj = (double***) calloc(number_of_qos + 1, sizeof(double**));
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
		} // end: if (link
    } // end: for (LinkListIterator

	// allocating memory for the path
	int path_length = 0;
	int* path = (int*) calloc(number_of_nodes + 1, sizeof(int));

	// invoking SAMCRA
    TRACE("SamcraBeforeAlgorithm::compute: Invoking SAMCRA");
#ifndef NO_TIMER
    Timer timer;
    timer.start();
#endif // NO_TIMER
    samcrapath( flow.getSource()+1, flow.getDestination()+1,
	            adj, max, datadj, number_of_qos, flow_qos,
	            number_of_nodes, path, &path_length, &min_k, &k_used);
    TRACE("SamcraBeforeAlgorithm::compute: End SAMCRA");


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
	for (int counter = 1; counter <= number_of_qos; ++counter)
	{
		freeMatrix((void**) datadj[counter], number_of_nodes + 1);
	}
	free(datadj);
	free(flow_qos);
	freeMatrix((void**) adj, number_of_nodes + 1);
	free(max);

    TRACE("SamcraBeforeAlgorithm::compute <--");
    return result;
}
