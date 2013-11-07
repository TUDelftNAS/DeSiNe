/******************************************************************************

    source file ThresholdHDTimerLSUpdateVisitor.cpp for class:
    ThresholdHDTimerLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update.

    This is a trigger and hold down timer based updated case.


    Author : Bingjie FU
    Version: 1
    Date   : June 2005

******************************************************************************/
#include "LinkStateUpdate/ThresholdHDTimerLSUpdateVisitor.h"
#include "Network/Link.h"
#include <cmath>
#include <valarray>

//------------------------------------------------------------------------------
//  ThresholdHDTimerLSUpdateVisitor
//------------------------------------------------------------------------------
ThresholdHDTimerLSUpdateVisitor::ThresholdHDTimerLSUpdateVisitor(
	const double &threshold,
	const double &holddown_time,
    const bool &is_parent) :
	LinkStateUpdateVisitor(true, is_parent),
	threshold(threshold),
	holddown_time(holddown_time)
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::ThresholdHDTimerLSUpdateVisitor1 -->");
    reset();
    TRACE("ThresholdHDTimerLSUpdateVisitor::ThresholdHDTimerLSUpdateVisitor1 <--");
}


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void ThresholdHDTimerLSUpdateVisitor::updateLSCapacity()
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::updateLSCapacity -->");
    current_known_capacity = ((Link*) link)->getReservableCapacity();

	// check the condition of time
	if (time->getTime() - last_trigger_time >= holddown_time)
    {
    	double diff = ((Link*) link)->getAvailableCapacity() - current_known_capacity;

    	// check the condition of update
    	if ( (diff >= threshold*current_known_capacity) || (diff < (0-threshold*current_known_capacity)) )
    	{
			new_value_from_update = ((Link*) link)->getAvailableCapacity();
			update_num++;
			last_trigger_time = time->getTime();
		}
	}
    else
    {
    	new_value_from_update = current_known_capacity;
    }
    TRACE("ThresholdHDTimerLSUpdateVisitor::updateLSCapacity <--");
}


//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli ThresholdHDTimerLSUpdateVisitor::getUpdateNum()
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::getUpdateNum-->");
    uli sum_update_num = 0;
    if (lsuv_vector)
    {
        for (LSUVector::iterator iter = lsuv_vector->begin();
            iter != lsuv_vector->end(); ++iter)
            {
                sum_update_num += (*iter)->getUpdateNum();
            }
    }
    else
    {
        sum_update_num = update_num;
    }
    TRACE("ThresholdHDTimerLSUpdateVisitor::getUpdateNum-->");
    return sum_update_num;
}


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void ThresholdHDTimerLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::visitLink -->");
    ThresholdHDTimerLSUpdateVisitor *clone = new ThresholdHDTimerLSUpdateVisitor(
    	threshold, holddown_time, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
    TRACE("ThresholdHDTimerLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void ThresholdHDTimerLSUpdateVisitor::reset()
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::reset -->");
    update_num = 0;
    last_trigger_time = 0.0;
    if (link)
    {
        new_value_from_update = ((Link*) link)->getCapacity();
        current_known_capacity = ((Link*) link)->getCapacity();
    }
    else
    {
        new_value_from_update = 0.0;
        current_known_capacity = 0.0;
    }
    TRACE("ThresholdHDTimerLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void ThresholdHDTimerLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("ThresholdHDTimerLSUpdateVisitor::print -->");
    buffer << "_CTHD_" << threshold << "_" << holddown_time ;
    TRACE("ThresholdHDTimerLSUpdateVisitor::print <--");
}
