/******************************************************************************

    source file MovingAverageClassLSUpdateVisitor.cpp for class:
    MovingAverageClassLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : Feb 2005

******************************************************************************/
#include "MovingAverageClassLSUpdateVisitor.h"
#include "Network/Link.h"
#include <valarray>
#include <fstream>
using std::ofstream;

//------------------------------------------------------------------------------
//  MovingAverageClassLSUpdateVisitor
//------------------------------------------------------------------------------
MovingAverageClassLSUpdateVisitor::MovingAverageClassLSUpdateVisitor(
	const int &window_size,
    const double &growth_factor,
    const double &bandw_base,
    const bool &is_parent) :
	LinkStateUpdateVisitor(false, is_parent),
	window_size(window_size),
	growth_factor(growth_factor),
	bandw_base(bandw_base)
{
    TRACE("MovingAverageClassLSUpdateVisitor::MovingAverageClassLSUpdateVisitor -->");

    // compute the bound_vec
    int num=0;
    double bw = 0.0;
    while (bw < 1)
    {
        //PRINTLN("bw---" << bw );
        bound_vec.push_back(bw);
        bw += bandw_base * pow(growth_factor, num);
        ++num;
    }
    bound_vec.push_back(1);
    current_class = num;

    reset();
    TRACE("MovingAverageClassLSUpdateVisitor::MovingAverageClassLSUpdateVisitor <--");
}



//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void MovingAverageClassLSUpdateVisitor::updateLSCapacity()
{
    TRACE("MovingAverageClassLSUpdateVisitor::updateLSCapacity -->");

    current_known_capacity = ((Link*) link)->getReservableCapacity();

    last_N_average = ( last_N_average * (window_size - 1) +
                       (((Link*) link)->getAvailableCapacity())) / window_size;

    // check the condition of update

    bool update_flag = 0;
    while((current_class > 0) && (last_N_average <=
                bound_vec.at(current_class-1)*((Link*) link)->getCapacity()))
    {
        --current_class;
        update_flag = 1;
    }
    while((!update_flag) && (bound_vec.at(current_class) < 1) && (last_N_average >
                bound_vec.at(current_class+1)*((Link*) link)->getCapacity()))
    {
        ++current_class;
        update_flag = 1;
    }

    if (update_flag)
    {
        new_value_from_update = bound_vec.at(current_class)*
                    ((Link*) link)->getCapacity(); // advertise the class value
        update_num++;
    }
    else
    {
        new_value_from_update = current_known_capacity;
    }
    TRACE("MovingAverageClassLSUpdateVisitor::updateLSCapacity <--");
}

//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli MovingAverageClassLSUpdateVisitor::getUpdateNum()
{
    TRACE("MovingAverageClassLSUpdateVisitor::getUpdateNum-->");
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
    TRACE("MovingAverageClassLSUpdateVisitor::getUpdateNum-->");
    return sum_update_num;
}


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void MovingAverageClassLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("MovingAverageClassLSUpdateVisitor::visitLink -->");
    MovingAverageClassLSUpdateVisitor *clone = new MovingAverageClassLSUpdateVisitor(
    	window_size, growth_factor, bandw_base, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
    TRACE("MovingAverageClassLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void MovingAverageClassLSUpdateVisitor::reset()
{
    TRACE("MovingAverageClassLSUpdateVisitor::reset -->");

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

    TRACE("MovingAverageClassLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void MovingAverageClassLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("MovingAverageClassLSUpdateVisitor::print -->");
    buffer << "_MAC_" << window_size << "_" << growth_factor << "_" << bandw_base;
    TRACE("MovingAverageClassLSUpdateVisitor::print <--");
}
