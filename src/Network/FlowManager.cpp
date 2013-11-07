/******************************************************************************

    source file FlowManager.cpp for class: FlowManager

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/Flow.h"
#include "Network/FlowList.h"
#include "Network/FlowManager.h"
#include "Network/Topology.h"
#include "Parameter/Parameters.h"
#include "RandomVariables/ExponentialVar.h"
#include "RandomVariables/RandomVar.h"
#include "RandomVariables/UniformVar.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <cmath>
using Types::DblVector;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  FlowManager::FlowManager(Parameters* parameters, Topology* topology)
//------------------------------------------------------------------------------
FlowManager::FlowManager(Parameters* parameters, Topology* topology)
    : parameters(parameters), topology(topology)
{
    TRACE("FlowManager::FlowManager -->");

    flow_id = 0;
    global_time = 0;

    TRACE("FlowManager::FlowManager <--");
}


//------------------------------------------------------------------------------
//  destructor FlowManager::~FlowManager()
//------------------------------------------------------------------------------
FlowManager::~FlowManager()
{
    TRACE("FlowManager::~FlowManager -->");
    // Empty!
    TRACE("FlowManager::~FlowManager <--");
}


//------------------------------------------------------------------------------
//  Flow* FlowManager::create()
//------------------------------------------------------------------------------
Flow FlowManager::create()
{
    TRACE("FlowManager::create -->");

	int input_type = topology->getInputType();

	if (input_type == 0)
    {
    	int source = topology->getRandomEdgeNode(parameters->endpoints);
    	int dest = source;
    	while (source==dest)
    	{
        	dest = topology->getRandomEdgeNode(parameters->endpoints);
    	}

    	// QoS Constraints
    	int number_of_qos = parameters->qos_cons.size();
   		DblVector qoscons;
    	for (int counter = 0; counter < number_of_qos; ++counter)
    	{
       		qoscons.push_back(parameters->qos_cons[counter]->generate());
   		}
    	double reqc = parameters->f_bandwidth->generate();
    	// set start time of new flow, this is also the new global time
    	global_time  += parameters->f_arrival->generate();
    	double tend   = global_time + parameters->f_duration->generate();
    	Flow result(flow_id++, source, dest, reqc, qoscons, global_time, tend);
    	result.topology = topology;
    	TRACE("FlowManager::create <--");
   		return result;
    } else {
    	int num_pair_sd = topology->getNumSDpairs();
    	int index = ( (int) ceil( num_pair_sd *
                              parameters->endpoints->generate() ) );

		uli source = topology->getflowsrc(index - 1);
		uli dest = topology->getflowdest(index - 1);

		int number_of_qos = parameters->qos_cons.size();
   		DblVector qoscons;
    	for (int counter = 0; counter < number_of_qos; ++counter)
    	{
       		qoscons.push_back(parameters->qos_cons[counter]->generate());
    	}

    	double reqc = topology->getflowreqc(index - 1)/(double)parameters->splitnum; // to give a flow with a smaller scale
    	global_time += parameters->f_arrival->generate();
    	double tend = global_time + parameters->f_duration->generate();
    	Flow result(flow_id ++, source, dest, reqc, qoscons, global_time, tend);
    	result.topology = topology;
    	TRACE("FlowManager::create <--");
   		return result;
    }
}


//------------------------------------------------------------------------------
//  Flow* FlowManager::create()
//------------------------------------------------------------------------------
Flow FlowManager::create(const Flow &original) const
{
    TRACE("FlowManager::create2 -->");
    Flow result(original);
    result.topology = topology;
    TRACE("FlowManager::create2 <--");
    return result;
}

