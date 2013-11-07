/******************************************************************************

    source file FlowList.cpp for class: FlowList

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/Flow.h"
#include "Network/FlowList.h"
#include "Utils/TraceManager.h"
#include <ostream>
using std::endl;
using std::ostream;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor FlowList::FlowList()
//------------------------------------------------------------------------------
FlowList::FlowList()
{
    TRACE("FlowList::FlowList -->");
    throughput = 0.0;
    TRACE("FlowList::FlowList <--");
}


//------------------------------------------------------------------------------
//  destructor FlowList::~FlowList()
//------------------------------------------------------------------------------
FlowList::~FlowList()
{
    TRACE("FlowList::~FlowList -->");
    flow_map.clear();
    TRACE("FlowList::~FlowList <--");
}


//------------------------------------------------------------------------------
//  void accept()
//------------------------------------------------------------------------------
void FlowList::accept(const Flow &flow)
{
	TRACE("FlowList::accept -->");

    flow_map.insert(std::make_pair(flow.getTend(), Flow(flow)));
    throughput += flow.getRequestedCapacity();

	TRACE("FlowList::accept <--");
}


//------------------------------------------------------------------------------
//  Link* LinkList::find(int source, int destination);
//------------------------------------------------------------------------------
FlowList::Iterator FlowList::getIterator() const
{
    TRACE("FlowList::getIterator -->");

    FlowList::Iterator result(flow_map);

    TRACE("FlowList::getIterator <--");
    return result;
}



//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//------------------------------------------------------------------------------
void FlowList::print(ostream &buffer) const
{
    buffer << "FlowList> Size: " << flow_map.size() << endl;
    for (FlowMap::const_iterator iter = flow_map.begin();
         iter != flow_map.end(); ++iter)
    {
        iter->second.print(buffer);
    }
}


//------------------------------------------------------------------------------
//  void update(double global_time)
//------------------------------------------------------------------------------
void FlowList::update(const double &global_time)
{
    TRACE("FlowList::update -->");

    // current implementation only removes flows from flowlist with:
    // flow->t_end <= global_time
    FlowMap::iterator bound = flow_map.upper_bound(global_time);

    for (FlowMap::iterator iter = flow_map.begin(); iter != bound; ++iter)
    {
        time->setTime(iter->first);
        iter->second.release();
        throughput -= iter->second.getRequestedCapacity();
    }
    flow_map.erase(flow_map.begin(), bound);
    time->setTime(global_time);

    TRACE("FlowList::update <--");
}
