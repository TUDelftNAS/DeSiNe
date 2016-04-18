#ifndef LINK_H
#define LINK_H
/******************************************************************************

    header file Link.h for class: Link

    This class is used for representing a Link in the network. It can only be
    created by Topology, which also is responsible for updating its values etc.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/
// Include(s)
#include "InsufficientCapacityException.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Network/AbstractNetworkElement.h"
#include "Network/AbstractNetworkElementVisitor.h"
#include "Utils/IllegalOperationException.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <cfloat>
#include <ostream>
#include <string>
// using declarations
using std::ostream;
using std::string;
using Types::usi;
using Types::DblVector;

class Link : public AbstractNetworkElement
{

    // Friends
    friend class LinkList;
    friend class LinkListMemento;
    friend class Topology;

    // Constanst(s)
    public:
    static const double METRIC_MIN;
    static const double METRIC_MAX;

    // Variable(s)
    private:
    usi source;               // source node
    usi destination;          // destination node
    bool corelink;            // 1 for corelink, 0 otherwise
    double avail_capacity;    // currently available capacity
    double capacity;          // Link's maximum capacity
    DblVector qos_metrics;    // the QoS metrics that are defined for the link
    LinkCostFunctionVisitor *lcf_visitor;// the link cost function
    LinkStateUpdateVisitor *lsupdate_visitor;   // the link state update visitor


    public:
    double metric;            // used by routing algorithms


    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor Link();
//
//  Constructs Link. Only used by Topology
//  Input : see variable declaration for info
//  Output:
//
//------------------------------------------------------------------------------
    Link(const usi& source, const usi& destination, const double& capacity,
         const bool& corelink, const DblVector& qos_metrics);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~Link()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~Link();


//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//
//  Accepts and executes a network element visitor
//
//------------------------------------------------------------------------------
    void accept(AbstractNetworkElementVisitor& anev);


//------------------------------------------------------------------------------
//
//  Inlines that return some link properties
//
//------------------------------------------------------------------------------
    const double& getCapacity() const;
    const usi& getDestination() const;
    const usi& getSource() const;
    const double getCost() const;
    const double& getQoS(const int& qos_index) const;
    const double getReservableCapacity() const;
    const double& getAvailableCapacity() const;


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints link to the buffer
//
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;


//------------------------------------------------------------------------------
//  void setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor)
//
//  Sets the link cost funtion, no check performed!!
//  Input : link_cost_func
//  Output:
//------------------------------------------------------------------------------
    void setLinkCostFunctionVisitor(LinkCostFunctionVisitor *visitor);


//------------------------------------------------------------------------------
//  void setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor)
//
//  Sets the link cost funtion, no check performed!!
//  Input : link_cost_func
//  Output:
//------------------------------------------------------------------------------
    void setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor);


    private:
//------------------------------------------------------------------------------
//  void allocate(const double& req_capacity)
//
//  Allocating requested capacity on a link. Only allowed by Topoogy.
//
//------------------------------------------------------------------------------
    void allocate(const double& req_capacity)
         throw (InsufficientCapacityException &);


//------------------------------------------------------------------------------
//  void release(const double& req_capacity)
//
//  Releasing requested capacity on a link. Only allowed by Topoogy.
//
//------------------------------------------------------------------------------
    void release(const double& req_capacity)
         throw (IllegalOperationException &);


//------------------------------------------------------------------------------
//  void reset()
//
//  Reset the link
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void reset();

}; //end declarations
#endif //LINK_H
