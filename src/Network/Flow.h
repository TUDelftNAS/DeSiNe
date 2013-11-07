#ifndef FLOW_H
#define FLOW_H
/******************************************************************************

    header file Flow.h for class: Flow

	This class is used for representing a flow in the network. It can only be
	created by FlowList, which also is responsible for its destruction (after
	expiration of the flow.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Types.h"
#include <ostream>
using std::ostream;
using Types::uli;
using Types::DblVector;

class Flow
{
	friend class FlowManager;
    // Constanst(s)

    // Variable(s)
	private:
	uli id;                 // flow id
	int source;             // source node
	int dest;               // destination node
	double req_cap;         // requested capacity
	float proc_time;        // processor time spent to compute the path
	double tstart;          // flow starting time
	double tend;            // flow ending time
	DblVector qoscons;      // QoS requirements of this flow
	Path path;              // path vector for this flow

    Topology* topology;

    // Function(s) declarations
 	private:
//------------------------------------------------------------------------------
//
//  constructor Flow();
//
//  Constructs Flow. Only used by FlowList
//  Input : see variabledeclaration for info
//  Output:
//
//------------------------------------------------------------------------------
    Flow(const uli &id,
         const int &source,
         const int &dest,
         const double &reqcap,
         const DblVector &qoscons,
         const double &tstart,
         const double &tend);


	public:
//------------------------------------------------------------------------------
//
//  destructor ~Flow()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~Flow();


//------------------------------------------------------------------------------
//
//  int allocate();
//
//  This function performs the flow set-up phase (signaling). It checks the
//  resources along the path first and if the resources are available, it
//  reserves the resources.

//  Input : the flow that must be allocated
//  Output: following returnvalues are defined:
//   0  = Setup was succesful
//   1  = Setup failed due to insufficient capacity on the links
//  10+ = Setup failed due to QoS constraints:
//          10 = Setup failed due to QoS constraint 0
//          11 = Setup failed due to QoS constraint 1
//          etc.
//
//------------------------------------------------------------------------------
    int allocate() const;


//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//
//  Prints flow to the buffer
//
//  Input : buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;

//------------------------------------------------------------------------------
//
//  void release();
//
//  This function releases resources reserved by a flow in the topology.
//
//  Input : the flow that must be released
//  Output: -
//
//------------------------------------------------------------------------------
    void release() const;


//------------------------------------------------------------------------------
//
//  Inline expansion that return the flow varibales. Inline is used to boost
//  performance
//
//------------------------------------------------------------------------------
	uli getId() const { return id; }
	int getSource() const { return source; }
	int getDestination() const { return dest; }
	double getDuration() const { return (tend-tstart); }
	double getRequestedCapacity() const { return req_cap; }
	double getTstart() const { return tstart; }
	double getTend() const { return tend; }
	DblVector getQosCons() const { return qoscons; }

	Path getPath() const { return path; }
	void setPath(const Path& path) { this->path = path; }

	const float getTime() const { return proc_time; }
	void setTime(const float &proctime) { proc_time = proctime; }

    Topology* getTopology() const { return topology; }

}; //end declarations
#endif //FLOW_H
