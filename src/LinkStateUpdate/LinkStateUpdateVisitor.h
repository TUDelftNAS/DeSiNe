#ifndef LINKSTATEUPDATEVISITOR_H
#define LINKSTATEUPDATEVISITOR_H
/******************************************************************************

    header file LinkStateUpdateVisitor.h for class:
    LinkStateUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElement.h"
#include "Network/AbstractNetworkElementVisitor.h"
#include "Utils/Time.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <vector>
#include <ostream>
using std::ostream;
using std::vector;
using Types::uli;

class LinkStateUpdateVisitor : public AbstractNetworkElementVisitor
{
    protected:
    typedef vector<LinkStateUpdateVisitor*> LSUVector;
    AbstractNetworkElement* link;
    LSUVector *lsuv_vector;
	Time* time;
    uli update_num;
    const bool timer_based; // different rules apply if true.
    const bool is_parent; // different rules apply if true.


//------------------------------------------------------------------------------
//  LinkStateUpdateVisitor()
//
//  Constructor
//
//------------------------------------------------------------------------------
    LinkStateUpdateVisitor(
    	const bool &timer_based,
    	const bool &is_parent) :
    	timer_based(timer_based),
    	is_parent(is_parent)
    {
		TRACE("LinkStateUpdateVisitor::LinkStateUpdateVisitor -->");
        link = (AbstractNetworkElement*) 0;
        lsuv_vector = (LSUVector*) 0;
        if (is_parent)
        {

        	lsuv_vector = new LSUVector();
        }
        time = (Time*) 0;
		update_num = 0;
		TRACE("LinkStateUpdateVisitor::LinkStateUpdateVisitor <--");
    }

	public:
//------------------------------------------------------------------------------
//  ~LinkStateUpdateVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
	~LinkStateUpdateVisitor()
	{
		TRACE("LinkStateUpdateVisitor::~LinkStateUpdateVisitor -->");
		if (is_parent)
		{
			release();
			delete lsuv_vector;
			lsuv_vector = (LSUVector*) 0;
		}
		TRACE("LinkStateUpdateVisitor::~LinkStateUpdateVisitor <--");
	}

	public:
//------------------------------------------------------------------------------
//  double getLSUpdateCapacity();
//
//  GEt the ....
//
//------------------------------------------------------------------------------
    virtual double getLSUpdateCapacity() = 0;


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//
//  Calculate the new Link State Update Capacity value according to the
//  update policy
//
//------------------------------------------------------------------------------
    virtual void updateLSCapacity() = 0;

//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
    virtual uli getUpdateNum() = 0;

//------------------------------------------------------------------------------
//  void reset()
//
//  Reset the visitor to its initial values
//
//------------------------------------------------------------------------------
    virtual void reset() = 0;


//------------------------------------------------------------------------------
//  void print()
//
//  Print the visitor to log files
//
//------------------------------------------------------------------------------
    virtual void print(ostream &buffer) = 0;


//------------------------------------------------------------------------------
//  void setTime(Time* t)
//------------------------------------------------------------------------------
    void setTime(Time* t)
    {
	    TRACE("LinkStateUpdateVisitor::setTime -->");
        time = t;
    	TRACE("LinkStateUpdateVisitor::setTime <--");
    }


//------------------------------------------------------------------------------
//  Returns if policy is timer based
//------------------------------------------------------------------------------
	bool isTimerBased() const
	{
		return timer_based;
	}

//------------------------------------------------------------------------------
//  Release all LSUPs that are tied to a link...necessary when LSUP is tied to
//  a new topology and old topology is deleted.
//------------------------------------------------------------------------------
	void release()
	{
		TRACE("LinkStateUpdateVisitor::release -->");
	    if (is_parent)
	    {
	        for (LSUVector::iterator iter = lsuv_vector->begin();
	            iter != lsuv_vector->end(); ++iter)
	        {
	            if (*iter) delete *iter;
	        }
	        lsuv_vector->clear();
	    }
		TRACE("LinkStateUpdateVisitor::release <--");
	}

//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("LinkStateUpdateVisitor::visitLink -->");
        //empty
        TRACE("LinkStateUpdateVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  void visitLinkList(const AbstractNetworkElement& linklist)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLinkList(const AbstractNetworkElement* linklist)
    {
        TRACE("LinkStateUpdateVisitor::visitLinklist -->");
        //empty
        TRACE("LinkStateUpdateVisitor::visitLinklist <--");
    }


//------------------------------------------------------------------------------
//  void visitTopology(const AbstractNetworkElement& topology)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitTopology(const AbstractNetworkElement* topology)
    {
        TRACE("LinkStateUpdateVisitor::visitTopology -->");
        //empty
        TRACE("LinkStateUpdateVisitor::visitTopology <--");
    }

}; //end declarations
#endif //LINKSTATEUPDATEVISITOR_H
