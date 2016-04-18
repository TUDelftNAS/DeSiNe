/******************************************************************************

    source file DesineModel.cpp for class: DesineModel

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/

/******************************************************************************
*      ## no path (blocked) ## eccepted ## Rejected Setup ## Rejected QoS     *
*#############################################################################*
* tp   ## total   blocked   ## tot acc  ## tot rej_setup  ## tot rej_qos      *
* hops ##                   ## total    ## total          ## total            *
* flow ## total   blocked   ## tot acc  ## tot rej_setup  ## tot rej_qos      *
*******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Main/Data.h"
#include "Main/Desine/DesineData.h"
#include "Main/Desine/DesineModel.h"
#include "Network/Flow.h"
#include "Network/FlowManager.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Network/TopologyFactory.h"
#include "Parameter/Parameters.h"
#include "Utils/Time.h"
#include "Utils/Types.h"
#include "Utils/Utils.h"
#include <sstream>
#include <vector>
using Types::uli;
using std::ostringstream;
using std::vector;

// Constanst(s)

// Variable(s)

// Function(s) definitions


//------------------------------------------------------------------------------
//  constructor DesineModel::DesineModel(char* input)
//------------------------------------------------------------------------------
DesineModel::DesineModel(Parameters* parameters,
    Algorithm* algorithm, LinkStateUpdateVisitor* lsuv) : Model()
{
    TRACE("DesineModel::DesineModel -->");
    this->parameters = parameters;
    this->algorithm = algorithm;
    this->lsuv = lsuv;

    ostringstream description;
    algorithm->print(description);
    if (lsuv)
    {
        lsuv->print(description);
    }
    name = description.str();
    TRACE("DesineModel::DesineModel <--");
}


//------------------------------------------------------------------------------
//  destructor DesineModel::~DesineModel()
//------------------------------------------------------------------------------
DesineModel::~DesineModel()
{
    TRACE("DesineModel::~DesineModel -->");
    // Empty
    TRACE("DesineModel::~DesineModel <--");
}


//------------------------------------------------------------------------------
//  void execute();
//------------------------------------------------------------------------------
Data* DesineModel::execute(const int &iterations)
{
    TRACE("DesineModel::execute -->");

    // Initialization
    int number_of_qos = parameters->qos_cons.size();
    long flows = parameters->flows;

    Time* time = new Time();
    DesineData* result = new DesineData(name, number_of_qos, flows);
    TopologyFactory top_fct(parameters->l_capacity);

    // Start iteration
    for (int iteration = 0; iteration < iterations; ++iteration)
    {
        TRACE("DesineModel::execute: starting iteration: " << iteration);

		// Build topology
	    Topology *topology = (Topology *) 0;
	    do
	    {
	    	if (topology) delete topology;
	    	topology = (Topology *) 0;
	    	topology = top_fct.create(parameters->topology);
	    } while(!topology->isConnected());

	    // Topology accepts the lsu visitor
	    if (lsuv)
	    {
	    	lsuv->release();
	        lsuv->setTime(time);
	        topology->accept(*lsuv);
	    }
        DesineData data(name, number_of_qos, flows);
        FlowManager flow_man(parameters, topology);

        time->reset();
        flow_man.setTime(time);


        uli update_num = 0;
        uli flow_rejected_setup = 0;
        uli flow_total = 0;
        uli flow_accepted = 0;
        uli flow_blocked = 0;
        uli hop_total = 0;
        vector<uli> flow_rejected_qos(number_of_qos);

        double tp_total = 0.0;
        double tp_accepted = 0.0;
        double tp_blocked = 0.0;
        double tp_rejected_setup = 0.0;
        double tp_rejected_qos = 0.0;

        //----------------------------------------------------------------------
        //
        //   S T A R T
        //
        //----------------------------------------------------------------------
        for (long flowcounter = 0; flowcounter < flows; ++flowcounter)
        {
            bool steady(flowcounter > parameters->warmup);

            // Create flow
            Flow flow(flow_man.create());

            // update flow list to see which flows have expired
            flow_man.update();

#ifndef NO_THROUGHPUT
            //PRINTLN("\t tp:" << flow_man.getThroughput() << " fs:" << flow_man.size());
            //Update throughput
            data.throughput[flowcounter].add(flow_man.getThroughput());
            data.numflows[flowcounter].add(flow_man.size());
#endif //NO_THROUGHPUT

            // Find path for flow
            Path path(algorithm->compute(flow));
            if (path.size() > 0)   // flow is routed succesfully)
            {
                // Setup the path
                flow.setPath(path);
                int result_code = flow.allocate();

                //PRINT("\t rc:" << result_code << " ps:" <<path.size());
                switch(result_code)
                {
                    case 0: // flow accepted
                        flow_man.accept(flow);
                        if (steady)
                        {
                            flow_accepted++;
                            tp_accepted += flow.getRequestedCapacity();;
                        }
                        break;
                    case 1: // flow rejected in setup
                        if (steady)
                        {
                            flow_rejected_setup++;
                            tp_rejected_setup += flow.getRequestedCapacity();
                        }
                        break;
                    default: // flow rejected QoS
                        if (steady)
                        {
                            flow_rejected_qos[result_code-10]++;
                            tp_rejected_qos += flow.getRequestedCapacity();
                       }
                        break;
                } // end: switch
            } // end: if (path
            else // path length = 0
            {
                if (steady)
                {
                     flow_blocked++;
                     tp_blocked += flow.getRequestedCapacity();
                }
            } // end: path length

            // Get data
            if (steady)
            {
                tp_total += flow.getRequestedCapacity();
                data.time_comp.add(flow.getTime());
                flow_total++;
                hop_total += path.size();
            }
        } // end: for (flowcounter...all flows have been generated
        //----------------------------------------------------------------------
        //
        //   E N D
        //
        //----------------------------------------------------------------------
        if(lsuv)
        {
            update_num = lsuv->getUpdateNum();
            data.update_num.add(update_num);
            //lsuv->release();
        }
        data.flow_total.add(flow_total);
        data.flow_accepted.add(flow_accepted);
        data.flow_blocked.add(flow_blocked);
        data.flow_rejected_setup.add(flow_rejected_setup);
        data.hop_total.add(hop_total);
        data.tp_total.add(tp_total);
        data.tp_accepted.add(tp_accepted);
        data.tp_blocked.add(tp_blocked);
        data.tp_rejected_setup.add(tp_rejected_setup);
        data.tp_rejected_qos.add(tp_rejected_qos);

        for (uli ix = 0; ix < flow_rejected_qos.size(); ++ix)
        {
            data.flow_rejected_qos[ix].add(flow_rejected_qos[ix]);
        }

        (*result) += data;
		delete topology;
    } // end: for (int ai

    delete time;
    TRACE("DesineModel::execute <--");
    return result;
}
