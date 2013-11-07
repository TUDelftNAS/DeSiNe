/******************************************************************************

    source file MovingAverageAbsoluteLSUpdateVisitor.cpp for class:
    MovingAverageAbsoluteLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : Jan 2005

******************************************************************************/
#include "MovingAverageAbsoluteLSUpdateVisitor.h"
#include "Network/Link.h"

//------------------------------------------------------------------------------
//  MovingAverageAbsoluteLSUpdateVisitor
//------------------------------------------------------------------------------
MovingAverageAbsoluteLSUpdateVisitor::MovingAverageAbsoluteLSUpdateVisitor(
	const int &window_size,
    const double &threshold,
    const bool &is_parent) :
	LinkStateUpdateVisitor(false, is_parent),
    window_size(window_size),
    threshold(threshold)
{
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::MovingAverageAbsoluteLSUpdateVisitor -->");
    reset();
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::MovingAverageAbsoluteLSUpdateVisitor <--");
}


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void MovingAverageAbsoluteLSUpdateVisitor::updateLSCapacity()
{
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::updateLSCapacity -->");
    current_known_capacity = ((Link*) link)->getReservableCapacity();
    last_N_average = ( last_N_average * (window_size - 1) +
                       (((Link*) link)->getAvailableCapacity())) / window_size;

    double thresholdCap = threshold * ((Link*) link)->getCapacity();
    // check the condition of update
    if((current_known_capacity - thresholdCap)*(last_N_average-thresholdCap) < 0.0)
    {
        new_value_from_update = ((Link*) link)->getAvailableCapacity(); //update
        update_num++;
    }
    else
    {
        new_value_from_update = current_known_capacity; //keep the former one
    }
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::updateLSCapacity <--");
}

//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli MovingAverageAbsoluteLSUpdateVisitor::getUpdateNum()
    {
        TRACE("MovingAverageAbsoluteLSUpdateVisitor::getUpdateNum-->");
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
            sum_update_num = update_num;
        TRACE("MovingAverageAbsoluteLSUpdateVisitor::getUpdateNum-->");
        return sum_update_num;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void MovingAverageAbsoluteLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::visitLink -->");
    MovingAverageAbsoluteLSUpdateVisitor *clone = new MovingAverageAbsoluteLSUpdateVisitor(
    	window_size, threshold, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void MovingAverageAbsoluteLSUpdateVisitor::reset()
{
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::reset -->");
    update_num = 0;
    if (link)
    {
        new_value_from_update = ((Link*) link)->getCapacity();
        current_known_capacity = ((Link*) link)->getCapacity();
        last_N_average = ((Link*) link)->getCapacity();
    }
    else
    {
        new_value_from_update = 0.0;
        current_known_capacity = 0.0;
        last_N_average = 0.0;
    }

    TRACE("MovingAverageAbsoluteLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void MovingAverageAbsoluteLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::print -->");
    buffer << "_MAA_" << window_size << "_" << threshold ;
    TRACE("MovingAverageAbsoluteLSUpdateVisitor::print <--");
}
