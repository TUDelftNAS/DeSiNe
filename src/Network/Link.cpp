/******************************************************************************

    source file Link.cpp for class: Link

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "IO/Tag.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <cmath>
#include <ostream>
#include <iomanip>
using std::ostream;
using std::endl;
using std::setw;
using Types::DblVector;
using Types::usi;


// Constanst(s)
const double Link::METRIC_MIN = 1.0/DBL_MAX; // to prevent metric to be 0
const double Link::METRIC_MAX = DBL_MAX;

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor Link::Link();
//------------------------------------------------------------------------------
Link::Link(const usi& source, const usi& destination, const double& capacity,
           const bool& corelink, const DblVector& qos_metrics)
{
  	TRACE("Link::Link -->");

    // Initialize variables
    this->source      = source;
    this->destination = destination;
    this->capacity    = capacity;
    this->corelink    = corelink;
    this->qos_metrics = qos_metrics;
    lcf_visitor = (LinkCostFunctionVisitor*) 0;
    lsupdate_visitor = (LinkStateUpdateVisitor*) 0;
    reset();
  	TRACE("Link::Link <--");
}


//------------------------------------------------------------------------------
//  destructor ~Link()
//------------------------------------------------------------------------------
Link::~Link()
{
	TRACE("Link::~Link -->");
	// Empty
	TRACE("Link::~Link <--");
}




//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//------------------------------------------------------------------------------
void Link::accept(AbstractNetworkElementVisitor& anev)
{
    TRACE("Link::accept -->");
    anev.visitLink(this);
    TRACE("Link::accept <--");
}


//------------------------------------------------------------------------------
//  void allocate(const double& req_capacity)
//------------------------------------------------------------------------------
void Link::allocate(const double& req_capacity)
     throw (InsufficientCapacityException &)
{
    TRACE("Link::allocate -->");
    if (avail_capacity < req_capacity)
    {
        throw
        InsufficientCapacityException("InsufficientCapacity");
    }

    //for time-sensitive LSUpdate policies (holddown timer)
    //the link state update needs to be done before the change of avail_capacity
	if (lsupdate_visitor ? lsupdate_visitor->isTimerBased() : false) lsupdate_visitor->updateLSCapacity();
    avail_capacity -= req_capacity;
	if (lsupdate_visitor ? !(lsupdate_visitor->isTimerBased()) : false) lsupdate_visitor->updateLSCapacity();
    TRACE("Link::allocate <--");

}


//------------------------------------------------------------------------------
//
//  Inlines that return some link properties
//
//------------------------------------------------------------------------------
const double& Link::getCapacity() const { return capacity; }
const usi& Link::getDestination() const { return destination; }
const usi& Link::getSource() const      { return source; }
const double Link::getCost() const
{
    double result = 0.0;
    if (!lcf_visitor)
    {
        WARNING("No Link Cost Function defined!!");
    }
    else
    {
        result = lcf_visitor->getCost(this);
    }
    return result;
}
const double& Link::getQoS(const int& qos_index) const
{
    return qos_metrics[qos_index];
}


//------------------------------------------------------------------------------
//
//  function for maximum reservable capacity. This defined as
//  the available capacity for non-updated graphs (no link-state update policy
//  is enabled) or the last update value advertised in case of a link state
//  update policy.
//
//------------------------------------------------------------------------------
const double Link::getReservableCapacity() const
{
    double result = avail_capacity;
    result = lsupdate_visitor ? lsupdate_visitor->getLSUpdateCapacity() : result;
    return result;
}

const double& Link::getAvailableCapacity() const
{
      return avail_capacity;
}



//------------------------------------------------------------------------------
//  print(ostream &buffer)
//------------------------------------------------------------------------------
void Link::print(ostream &buffer) const
{
    int prec = buffer.precision(4);
    buffer
    << "Link> src: " << setw(4) << source
    << "\tdst: "     << setw(4) << destination
    << "\tCapac: "   << setw(4) << capacity
    << "\tAvaCap: "  << setw(4) << avail_capacity
    << "\tResCap: "  << setw(4) << getReservableCapacity()
    << "\tmetric: "  << setw(4) << metric
    << endl;
    buffer.precision(prec);
}


//------------------------------------------------------------------------------
//  void release(const double& req_capacity)
//
//  Releasing requested capacity on a link.
//
//------------------------------------------------------------------------------
void Link::release(const double& req_capacity)
      throw (IllegalOperationException &)
{
    TRACE("Link::release -->");

    //for time-sensitive LSUpdate policies (holddown timer)
    //the link state update needs to be done before the change of avail_capacity
	if (lsupdate_visitor ? lsupdate_visitor->isTimerBased() : false) lsupdate_visitor->updateLSCapacity();
    avail_capacity += req_capacity;
	if (lsupdate_visitor ? !(lsupdate_visitor->isTimerBased()) : false) lsupdate_visitor->updateLSCapacity();

    TRACE("Link::release <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void Link::reset()
{
    TRACE("Link::reset -->");
    avail_capacity = capacity;
    metric = 1.0; // Set metric to 1 to ensure min-hop criterium when not using
                  // Link Cost Function
    if (lsupdate_visitor) lsupdate_visitor->reset();
    TRACE("Link::reset <--");
}

//------------------------------------------------------------------------------
//  void setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor)
//------------------------------------------------------------------------------
void Link::setLinkCostFunctionVisitor(LinkCostFunctionVisitor *visitor)
{
    TRACE("Link::setLinkCostFunctionVisitor -->");
    lcf_visitor = visitor;
    TRACE("Link::setLinkCostFunctionVisitor <--");
}


//------------------------------------------------------------------------------
//  void setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor)
//------------------------------------------------------------------------------
void Link::setLinkStateUpdatePolicy(LinkStateUpdateVisitor *visitor)
{
    TRACE("Link::setLinkStateUpdatePolicy -->");
    lsupdate_visitor = visitor;
    TRACE("Link::setLinkStateUpdatePolicy <--");
}
