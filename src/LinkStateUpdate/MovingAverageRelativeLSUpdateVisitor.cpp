/******************************************************************************

    source file MovingAverageRelativeLSUpdateVisitor.cpp for class:
    MovingAverageRelativeLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : Jan 2005

******************************************************************************/
#include "MovingAverageRelativeLSUpdateVisitor.h"
#include "Network/Link.h"
#include <valarray>

//------------------------------------------------------------------------------
//  MovingAverageRelativeLSUpdateVisitor
//------------------------------------------------------------------------------
MovingAverageRelativeLSUpdateVisitor::MovingAverageRelativeLSUpdateVisitor(
	const int &window_size,
    const double &threshold,
    const bool &is_parent) :
	LinkStateUpdateVisitor(false, is_parent),
    window_size(window_size),
    threshold(threshold)

{
    TRACE("MovingAverageRelativeLSUpdateVisitor::MovingAverageRelativeLSUpdateVisitor -->");
    reset();
    TRACE("MovingAverageRelativeLSUpdateVisitor::MovingAverageRelativeLSUpdateVisitor <--");
}


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void MovingAverageRelativeLSUpdateVisitor::updateLSCapacity()
{
    TRACE("MovingAverageRelativeLSUpdateVisitor::updateLSCapacity -->");
    current_known_capacity = ((Link*) link)->getReservableCapacity();
    last_N_average = ( last_N_average * (window_size - 1) +
                       (((Link*) link)->getAvailableCapacity())) / window_size;

    // check the condition of update
    double infodiff = ((last_N_average - current_known_capacity) > 0)?
                        (last_N_average - current_known_capacity) :
                            -(last_N_average - current_known_capacity);
    if( infodiff > threshold * current_known_capacity )
    {
        new_value_from_update = ((Link*) link)->getAvailableCapacity(); //update
        update_num++;
    }
    else
    {
        new_value_from_update = current_known_capacity; //keep the former one
    }
    TRACE("MovingAverageRelativeLSUpdateVisitor::updateLSCapacity <--");
}


//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli MovingAverageRelativeLSUpdateVisitor::getUpdateNum()
{
    TRACE("MovingAverageRelativeLSUpdateVisitor::getUpdateNum-->");
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
    TRACE("MovingAverageRelativeLSUpdateVisitor::getUpdateNum-->");
    return sum_update_num;
}


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void MovingAverageRelativeLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("MovingAverageRelativeLSUpdateVisitor::visitLink -->");
    MovingAverageRelativeLSUpdateVisitor *clone = new MovingAverageRelativeLSUpdateVisitor(
    	window_size, threshold, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
    TRACE("MovingAverageRelativeLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void MovingAverageRelativeLSUpdateVisitor::reset()
{
    TRACE("MovingAverageRelativeLSUpdateVisitor::reset -->");
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
    TRACE("MovingAverageRelativeLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void MovingAverageRelativeLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("MovingAverageRelativeLSUpdateVisitor::print -->");
    buffer << "_MAR_" << window_size << "_" << threshold ;
    TRACE("MovingAverageRelativeLSUpdateVisitor::print <--");
}
