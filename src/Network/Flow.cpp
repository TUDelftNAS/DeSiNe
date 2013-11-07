/******************************************************************************

    source file Flow.cpp for class: Flow

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/Flow.h"
#include "Network/Topology.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <ostream>
#include <iomanip>
using std::endl;
using std::ostream;
using std::setw;
using Types::DblVector;
using Types::uli;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor Flow::Flow();
//------------------------------------------------------------------------------
Flow::Flow(const uli &id,
           const int &source,
           const int &dest,
           const double &reqcap,
           const DblVector &qoscons,
           const double &tstart,
           const double &tend)
{
    TRACE("Flow::Flow -->");

    this->id = id;
    this->source = source;
    this->dest = dest;
    this->req_cap = reqcap;
    this->qoscons = qoscons;
    this->tstart = tstart;
    this->tend = tend;

    TRACE("Flow::Flow <--");
}


//------------------------------------------------------------------------------
//  destructor Flow::~Flow()
//------------------------------------------------------------------------------
Flow::~Flow()
{
    //TRACE("Flow::~Flow -->");
    // Empty
    //TRACE("Flow::~Flow <--");
}


//------------------------------------------------------------------------------
//  int allocate()
//------------------------------------------------------------------------------
int Flow::allocate() const
{
    TRACE("Flow::allocate -->");

    int result = 0;
    int qos = 0;
    int path_length = path.size();
    int number_of_qos = topology->getNumQos();
    DblVector qos_sum(number_of_qos);

    for (int count = 0; count < path_length-1 && result == 0; ++count)
    {
        Link* lk = topology->link(path[count], path[count + 1]);

        // check for capacity requirement
        if (lk->getAvailableCapacity() < req_cap)
        {
            result = 1; // setup filure flag
        }

        // Check QoS requirements exist && no setup failure detected
        for (qos = 0; qos < number_of_qos && result == 0; ++qos)
        {
            qos_sum[qos] += lk->getQoS(qos);
            // checking whether QoS constraints are satisfied
            if (qos_sum[qos] > qoscons[qos])
            {
                result = 10 + qos;
            }
        } // end: for (qos

        if (result != 0)    // there is setup failure or QoS rejection
        {
            // release the resource reserved before the detection of QoS rejects
            for (int inside_count = 0; inside_count < count; ++inside_count)
            {
                try
                {
                    topology->release(path[inside_count],
                    path[inside_count + 1],req_cap);
                }
                catch(IllegalOperationException &ioe)
                {
                    ERROR("Flow::allocate::" << ioe.getName() << ": " << ioe.getMessage());
                    throw ioe;
                }
            }
        }
        else
        {
            // reserve the resource on each applicable link along the path
            try
            {
                topology->allocate(path[count],
                path[count + 1],req_cap);
            }
            catch(InsufficientCapacityException &ice)
            {
                ERROR("Flow::allocate::" << ice.getName() << ": " << ice.getMessage());
            }
        }
    } // end: for (int count

    TRACE("Flow::allocate <--");
    return result;
}


//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//------------------------------------------------------------------------------
void Flow::print(ostream &buffer) const
{
    buffer
    << "Flow> ID: " << setw(6) << id
    << "  src: "    << setw(4) << source
    << "  dst: "    << setw(4) << dest
    << "  ReqCap: " << setw(8) << req_cap
    << "  Tstart: " << setw(8) << tstart
    << "  Tend: "   << setw(8) << tend;
    for (uli qos=0; qos<qoscons.size(); ++qos)
    {
        buffer << "  QoS[" << qos << "]: " << setw(8) << qoscons[qos];
    }
    buffer << endl;
}


//------------------------------------------------------------------------------
//  void releaseFlow(Flow* flow);
//------------------------------------------------------------------------------
void Flow::release() const
{
    TRACE("Flow::release -->");

    uli path_length = path.size();
    for (uli count = 0; count < path_length-1; ++count)
    {
        try
        {
            topology->release(path[count],
            path[count + 1],req_cap);
        }
        catch(IllegalOperationException &ioe)
        {
            ERROR("Flow::release::" << ioe.getName() << ": " << ioe.getMessage());
        }
    }

    TRACE("Flow::release <--");
}
