/******************************************************************************

    source file ClassHDTimerLSUpdateVisitor.cpp for class:
    ClassHDTimerLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update.

    This is a trigger and hold down timer based updated case.


    Author : Bingjie FU
    Version: 1
    Date   : June 2005

******************************************************************************/
#include "LinkStateUpdate/ClassHDTimerLSUpdateVisitor.h"
#include "Network/Link.h"
#include <cmath>
//#include <valarray>

//------------------------------------------------------------------------------
//  ClassHDTimerLSUpdateVisitor
//------------------------------------------------------------------------------
ClassHDTimerLSUpdateVisitor::ClassHDTimerLSUpdateVisitor(
	const double &growth_factor,
	const double &bandw_base,
	const double &holddown_time,
    const bool &is_parent) :
		LinkStateUpdateVisitor(true, is_parent),
		growth_factor(growth_factor),
		bandw_base(bandw_base),
		holddown_time(holddown_time)
{
    TRACE("ClassHDTimerLSUpdateVisitor::ClassHDTimerLSUpdateVisitor1 -->");

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
    TRACE("ClassHDTimerLSUpdateVisitor::ClassHDTimerLSUpdateVisitor1 <--");
}


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//------------------------------------------------------------------------------
void ClassHDTimerLSUpdateVisitor::updateLSCapacity()
{
    TRACE("ClassHDTimerLSUpdateVisitor::updateLSCapacity -->");
    current_known_capacity = ((Link*) link)->getReservableCapacity();

	bool update_flag = 0;
	// check the condition of time
	if (time->getTime() - last_trigger_time >= holddown_time)
    {
    	//PRINTLN("where.........0");
    	while((current_class > 0) && ( ((Link*) link)->getAvailableCapacity())<=
                (bound_vec.at(current_class-1)*((Link*) link)->getCapacity()))
    	{
    		//PRINTLN("where..........1");
        	--current_class;
        	//PRINTLN("current_class" << current_class);
        	update_flag = 1;
    	}
    	while((!update_flag) && (bound_vec.at(current_class) < 1) &&
    			(((Link*) link)->getAvailableCapacity()) >
                (bound_vec.at(current_class+1)*((Link*) link)->getCapacity()))
    	{
    		//PRINTLN("where.........2");
        	++current_class;
        	//PRINTLN("current_class" << current_class);
        	update_flag = 1;
    	}
	}
	//PRINTLN("where...........3")

    if (update_flag)
    {
    	//PRINTLN("where..........4");
       	new_value_from_update = bound_vec.at(current_class)*
                   ((Link*) link)->getCapacity(); // advertise the class value
       	update_num++;
       	last_trigger_time = time->getTime();
    }
    else
    {
    	new_value_from_update = current_known_capacity;
    }
    TRACE("ClassHDTimerLSUpdateVisitor::updateLSCapacity <--");
}


//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
uli ClassHDTimerLSUpdateVisitor::getUpdateNum()
{
    TRACE("ClassHDTimerLSUpdateVisitor::getUpdateNum-->");
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
    TRACE("ClassHDTimerLSUpdateVisitor::getUpdateNum-->");
    return sum_update_num;
}


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//------------------------------------------------------------------------------
void ClassHDTimerLSUpdateVisitor::visitLink(const AbstractNetworkElement* link)
{
    TRACE("ClassHDTimerLSUpdateVisitor::visitLink -->");

    ClassHDTimerLSUpdateVisitor *clone = new ClassHDTimerLSUpdateVisitor(
    	growth_factor, bandw_base, holddown_time, false);
    clone->link = (Link*) link;
    clone->time = time;
    clone->reset();
    lsuv_vector->push_back(clone);
    ((Link*) link)->setLinkStateUpdatePolicy(clone);
    TRACE("ClassHDTimerLSUpdateVisitor::visitLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void ClassHDTimerLSUpdateVisitor::reset()
{
    TRACE("ClassHDTimerLSUpdateVisitor::reset -->");
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
    TRACE("ClassHDTimerLSUpdateVisitor::reset <--");
}

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
void ClassHDTimerLSUpdateVisitor::print(ostream &buffer)
{
    TRACE("ClassHDTimerLSUpdateVisitor::print -->");
    buffer << "_CHD_" << growth_factor << "_" << bandw_base << "_" << holddown_time ;
    TRACE("ClassHDTimerLSUpdateVisitor::print <--");
}
