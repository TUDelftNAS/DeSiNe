/******************************************************************************

    source file PeriodLSUpdateVisitor.cpp for class:
    PeriodLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update

    This is a periodically updated case, the LSUpdate function inside allocate()
    and release() in Link class should be removed.


    Author : Bingjie FU
    Version: 1
    Date   : April 2005

******************************************************************************/
#include "LinkStateUpdate/PeriodLSUpdateVisitor.h"
#include "Network/Link.h"
#include <cmath>
//#include <valarray>

//------------------------------------------------------------------------------
//  PeriodLSUpdateVisitor
//------------------------------------------------------------------------------
PeriodLSUpdateVisitor::PeriodLSUpdateVisitor(
	const double &period,
    	const bool &is_parent) :
	LinkStateUpdateVisitor(true, is_parent),
	period(period)
{
    TRACE("PeriodLSUpdateVisitor::PeriodLSUpdateVisitor -->");
    reset();
    TRACE("PeriodLSUpdateVisitor::PeriodLSUpdateVisitor <--");
}


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void PeriodLSUpdateVisitor::updateLSCapacity()
{
    TRACE("PeriodLSUpdateVisitor::updateLSCapacity -->");
    if (lsuv_vector)
    {
        //PRINTLN("time::::" << time->getTime()<<"last_update_time"<<last_update_time);
        // check the condition of update
        if( (time->getTime() - last_update_time) >= period )
        {
	    //PRINTLN("time::::" << time->getTime()<<"last_update_time"<<last_update_time);

            for (LSUVector::iterator iter = lsuv_vector->begin();
                iter != lsuv_vector->end(); ++iter)
            {
                (*iter)->updateLSCapacity();
                last_update_time = (floor(time->getTime()/period)) * period;
            }
        }
    }
    else
    {
        new_value_from_update = ((Link*) link)->getAvailableCapacity(); //update
        //last_update_time = (floor(time->getTime()/period)) * period;
    }

    TRACE("PeriodLSUpdateVisitor::updateLSCapacity <--");
}


//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli PeriodLSUpdateVisitor::getUpdateNum()
{
    TRACE("PeriodLSUpdateVisitor::getUpdateNum-->");
    uli sum_update_num = 0;
	update_num = (uli) floor( (time->getTime()) / period );
    if (lsuv_vector)
    {
		sum_update_num = lsuv_vector->size() * update_num;
		//for (LSUVector::iterator iter = lsuv_vector->begin();
        //    iter != lsuv_vector->end(); ++iter)
        //    {
        //        sum_update_num += (uli) floor( (time->getTime()) / period );
        //    }
    }
    else
    {
        sum_update_num = update_num;
    }
    TRACE("PeriodLSUpdateVisitor::getUpdateNum-->");
    return sum_update_num;
}


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void PeriodLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("PeriodLSUpdateVisitor::visitLink -->");
    PeriodLSUpdateVisitor *clone = new PeriodLSUpdateVisitor(period, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
	//PRINT(lsuv_vector->size() << ' ');
    TRACE("PeriodLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void PeriodLSUpdateVisitor::reset()
{
    TRACE("PeriodLSUpdateVisitor::reset -->");
    update_num = 0;
    last_update_time = 0.0;
    if (link)
    {
        new_value_from_update = ((Link*) link)->getCapacity();
        //current_known_capacity = ((Link*) link)->getCapacity();
    }
    else
    {
        new_value_from_update = 0.0;
        //current_known_capacity = 0.0;
    }
    TRACE("PeriodLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void PeriodLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("PeriodLSUpdateVisitor::print -->");
    buffer << "_PER_" << period ;
    TRACE("PeriodLSUpdateVisitor::print <--");
}
