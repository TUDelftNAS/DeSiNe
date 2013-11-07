#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H
/******************************************************************************

    header file FlowManager.h for class: FlowManager

    This class manages all flows that run in the network. It both creates and
    desctructs them.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Network/Flow.h"
#include "Network/FlowList.h"
#include "Network/Topology.h"
#include "Parameter/Parameters.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/Types.h"
#include <ostream>
using std::ostream;
using Types::uli;


class FlowManager
{
    // Constanst(s)

    // Variable(s)
    private:
    // Flows are stored in a multimap. The Tend values are used as 'key' so that
    // the (multi)map automatically stores the flows in the correct order
    uli flow_id;
    double global_time;
    FlowList flow_list;
    Parameters* parameters;
    Topology* topology;
    Time* time;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor FlowManager(Parameters* params, Topology* topol);
//
//  Constructs FlowManager
//  Input :
//     params : the parameters that were loaded form the parameter file
//     topol : the topology
//  Output:
//
//------------------------------------------------------------------------------
    FlowManager(Parameters* parameters, Topology* topology);


//------------------------------------------------------------------------------
//
//  destructor ~FlowManager()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~FlowManager();


//------------------------------------------------------------------------------
//  void accept(Flow* flow)
//
//  Accept a flow when it is accepted by the topology. It is then added to the
//  list and the counter for the accepted dlows is incremented
//
//  Input : the accepted flow
//  Output:
//------------------------------------------------------------------------------
    void accept(const Flow &flow)
    {
        flow_list.accept(flow);
    }


//------------------------------------------------------------------------------
//  Flow* create();
//
//  Generate a new Flow. If original is 0, a new flow is created, otherwise
//  it is copied from the other flow
//  Input :
//  Output:
//      - : the newly generated Flow
//------------------------------------------------------------------------------
    Flow create();
    Flow create(const Flow &original) const;


//------------------------------------------------------------------------------
//  double getThroughput()
//
//  Returns throughput
//------------------------------------------------------------------------------
    double getThroughput() const
    {
        return flow_list.getThroughput();
    }

//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//
//  Prints flowlist to the buffer
//
//  Input : buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const
    {
        flow_list.print(buffer);
    }


//------------------------------------------------------------------------------
//  int size();
//
//  Returns size of the flowlist (number of flows in the network)
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    uli size() const
    {
        return flow_list.size();
    }


//------------------------------------------------------------------------------
//  void update()
//
//  Update the flow lists: chech if flows are expired and if so, remove them.
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void update()
    {
        flow_list.update(global_time);
    }


//------------------------------------------------------------------------------
//  void setTime(Time t)
//------------------------------------------------------------------------------
    void setTime(Time* t)
    {
        TRACE("setTime-->");
        flow_list.setTime(t);
        TRACE("setTime<--");
    }
}; //end declarations
#endif //FLOWMANAGER_H
