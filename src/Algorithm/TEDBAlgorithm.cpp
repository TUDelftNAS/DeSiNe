/******************************************************************************

    source file TEDBAlgorithm.cpp for class: TEDBAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : July 2004

******************************************************************************/

// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/NewMIRAAlgorithm.h"
#include "Algorithm/ShortestPathAlgorithm.h"
#include "Algorithm/TEDBAlgorithm.h"
#include "Network/Flow.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Timer.h"
#include "Utils/TraceManager.h"
#include "Utils/Utils.h"



extern "C" void tamcrapath(int,int,int **,int *,double ***,int,double *,
                           int,int,int **,int *,int *,int *);


long tedbcnt  = 0;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor TEDBAlgorithm::TEDBAlgorithm()
//------------------------------------------------------------------------------
TEDBAlgorithm::TEDBAlgorithm(const TString &args) : Algorithm(args)
{
    TRACE("TEDBAlgorithm::TEDBAlgorithm -->");

    new_mira = new NewMIRAAlgorithm(arguments);
    TString sp_dsr;
    sp_dsr.push_back(Tag::ALG_SHORTEST_PATH);
    sp_dsr.push_back(Tag::LCF_MIN_HOP);
    shr_path = new ShortestPathAlgorithm(sp_dsr);
    TRACE("TEDBAlgorithm::TEDBAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor TEDBAlgorithm::~TEDBAlgorithm()
//------------------------------------------------------------------------------
TEDBAlgorithm::~TEDBAlgorithm()
{
    TRACE("TEDBAlgorithm::~TEDBAlgorithm -->");
    delete new_mira;
    delete shr_path;
    TRACE("TEDBAlgorithm::~TEDBAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path TEDBAlgorithm::compute(const Flow &flow)
//------------------------------------------------------------------------------
Path TEDBAlgorithm::compute(const Flow &flow)
{
    TRACE("TEDBAlgorithm::compute -->");

    // Invoking NewMIRA to compute weights f(i,j), prune off links with insuff.
    // bandwidth and determine the path with least maxflow reduction weight
    Path result = new_mira->compute(flow);
    Topology *topology = flow.getTopology();

    // path length < 2 means there is no path with enough bandwidth
    // We assume the cost of a path equal to path length: #hops - 1
	unsigned int cost = result.size();
    if(cost > 1)
    {
        double mfrw = 0;    // max flow reduction weight of least cost path

#ifndef NO_TIMER
        Timer timer;
        timer.start();
#endif // NO_TIMER

        // store the state of the links (capacity, available capacity, etc.)
        LinkListMemento* mem = topology->createLinkListMemento();

        // Set link cost fucntion MinHop
        topology->setLinkCostFunction(Tag::LCF_MIN_HOP);

        // find the least cost path: route dijkstra on the topology
        result = shr_path->compute(flow);

        // restore maxflow reduction weights
        topology->rollbackLinkListMemento(mem);

        // delete memento and result
        delete mem;

        // compute the maxflow reduction weight of the least cost path
        for (unsigned int ix = result.size()-1; ix > 0; --ix)
        {
            mfrw += topology->link(result[ix-1], result[ix])->metric;
        }

        // preparing data structures for TAMCRA
        const int number_of_nodes = topology->getNumNodes();
        const int number_of_qos = topology->getNumQos();
        int* max = (int*) calloc(number_of_nodes + 1, sizeof(int));
        int** adj = (int**) allocMatrix(number_of_nodes + 1,
                                        number_of_nodes + 1, sizeof(int));

        // there are 2 additional constraints: cost and mfrw
        double*** datadj = (double***) calloc(number_of_qos + 3, sizeof(double**));
        double* flow_qos = (double*) calloc(number_of_qos + 2, sizeof(double));
        for (int counter = 0; counter < number_of_qos + 2; ++counter)
        {
            datadj[counter + 1] = (double**) allocMatrix(number_of_nodes + 1,
                                  number_of_nodes + 1, sizeof(double));

            if(counter == number_of_qos + 1)
            {
                flow_qos[counter] = cost;
            } else
            if(counter == number_of_qos)
            {
                flow_qos[counter] = mfrw;
            }
            else
            {
                flow_qos[counter] = flow.getQosCons()[counter];
            }
        } //end: for (int counter


        // filling adj and datadj, while pruning links with insuf. available cap.
        for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
        {
            Link* link = *iter;
            if (link->getReservableCapacity() >= flow.getRequestedCapacity())
            {
                int source = link->getSource() + 1;
                adj[source][++max[source]] = link->getDestination() + 1;
                for (int qos = 0; qos < number_of_qos; ++qos)
                {
                    datadj[qos+1][source][max[source]] = link->getQoS(qos);
                } // end: for (qos
                datadj[number_of_qos+1][source][max[source]] = link->metric;
                datadj[number_of_qos+2][source][max[source]] = 1.0;
            } // end: if (link
        } // end: for (LinkListIterator

        // allocating memory for the candidate set of paths
        const int buffer = 4; int min_k = 0; int k_used = 0; // used by tamcra
        int** setpath = (int**) allocMatrix(buffer, number_of_nodes + 1, sizeof(int));
        int* hopcount = (int*) calloc(buffer, sizeof(int));

        // invoking TAMCRA
        TRACE("TEDBAlgorithm::compute: Invoking TAMCRA");
        TRACE("TEDBAlgorithm::compute: Invoking TAMCRA");
        TRACE("tedbcnt: " << tedbcnt++);
        TRACE("flow.getSource()+1  " << flow.getSource()+1);
        TRACE("flow.getDestination()+1  " << flow.getDestination()+1);
        TRACE("adj  " << adj);
        TRACE("max  " << max);
        TRACE("datadj  " << datadj);
        TRACE("number_of_qos + 2  " << number_of_qos + 2);
        TRACE("flow_qos - 1  " << flow_qos - 1);
        TRACE("number_of_nodes  " << number_of_nodes);
        TRACE("buffer  " << buffer);
        TRACE("setpath  " << setpath);
        TRACE("hopcount  " << hopcount);
        TRACE("-------------------------------------------------------------");
        //topology->print(cout);
        TRACE("=============================================================");

        tamcrapath( flow.getSource()+1, flow.getDestination()+1,
                    adj, max, datadj, number_of_qos + 2, flow_qos - 1,
                    number_of_nodes, buffer, setpath, hopcount, &min_k, &k_used);
        TRACE("TEDBAlgorithm::compute: End TAMCRA");
        TRACE("TEDBAlgorithm::compute: End TAMCRA");

	//fprintf(stderr,"mink:%i -- usedk: %i\n", min_k, k_used);

        // Set link cost fucntion TEDBlc
        topology->setLinkCostFunction(Tag::LCF_TEDB);
        // because function returns the path vector from the destination "d" to
        // the source "s" it is necessary to invert the array
        // then the least critical path is selected
	//fprintf(stderr,"s:%i -- d: %i\n", flow.getSource(), flow.getDestination());

        double max_weight = 0;
        result.clear();
        for (int path_ix = 0; path_ix < min_k; ++path_ix)
        {
            // clear the path object
            Path path;

            for (int hop_ix=1; hop_ix <= hopcount[path_ix]; ++hop_ix)
            {
                path.push_front(setpath[path_ix][hop_ix]-1);
            }
	//fprintf(stderr,"here%i\n", path_ix);

            // Compute weight
            double weight = 0.0;
            for (unsigned int ix = path.size()-1; ix > 0; --ix)
            {
	//fprintf(stderr,"%i-%i\n", path[ix-1], path[ix]);
                weight += topology->link(path[ix-1], path[ix])->getCost();
            }
	//fprintf(stderr,"\n");

            if (weight > max_weight)
            {
                max_weight = weight;
                result = path;
            }
	//fprintf(stderr,"here%i\n", path_ix);
        }  // end: for (int path_ix



//cout << "path set\n";
#ifndef NO_TIMER
        const_cast<Flow&>(flow).setTime(timer.read());
#endif // NO_TIMER

        // freeing memory
        free(hopcount);
        freeMatrix((void**) setpath, buffer);
        for (int counter = 1; counter <= number_of_qos + 2; ++counter)
        {
            freeMatrix((void**) datadj[counter], number_of_nodes + 1);
        }
        free(datadj);
        free(flow_qos);
        freeMatrix((void**) adj, number_of_nodes + 1);
        free(max);
    } // end: else path length > 0

    TRACE("TEDBAlgorithm::compute <--");
    return result;
}
