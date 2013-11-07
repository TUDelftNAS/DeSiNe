#ifndef CLASSHDTIMERLSUPDATEVISITOR_H
#define CLASSHDTIMERLSUPDATEVISITOR_H

/******************************************************************************

    header file ClassHDTimerLSUpdateVisitor.h for class:
    ClassHDTimerLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : June 2005

******************************************************************************/

#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Utils/TraceManager.h"
#include "Utils/Time.h"
#include "Utils/Types.h"
using Types::DblVector;


class ClassHDTimerLSUpdateVisitor : public LinkStateUpdateVisitor
{
    private:
    Time* time;
    const double growth_factor;   // may be got from the parameters
    const double bandw_base;       // the bandwidth of base class, may be got from parameters
    const double holddown_time;
    double new_value_from_update;
    double current_known_capacity;
    double last_trigger_time;
    DblVector bound_vec;   // store the boundaries of each class
    int current_class;      // store the current class number

    // and if so return the new updated_value
    // if not return the old one


    public:
//------------------------------------------------------------------------------
//
//  constructor ClassHDTimerLSUpdateVisitor();
//
//  Constructs ClassHDTimerLSUpdateVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    ClassHDTimerLSUpdateVisitor(
    	const double &growth_factor,
    	const double &bandw_base,
    	const double &holddown_time,
    	const bool &is_parent = true);


//------------------------------------------------------------------------------
//  double getLSUpdateCapacity();
//
//  GEt the ....
//
//------------------------------------------------------------------------------
    double getLSUpdateCapacity()
    {
        return new_value_from_update;
    }


//------------------------------------------------------------------------------
//  void updateLSCapacity()
//
//  Calculate the new Link State Update Capacity value according to the
//  update policy
//
//------------------------------------------------------------------------------
    void updateLSCapacity();


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link);

//------------------------------------------------------------------------------
//  uli getUpdateNum()
//
//  get the number of updates that happened
//  if it is the main visitor,then add all the update numbers from child visitor
//  if it is a child visitor, just return the number of updates happened on its link
//
//------------------------------------------------------------------------------
    uli getUpdateNum();


//------------------------------------------------------------------------------
//  void reset()
//  reset the visitor
//
//------------------------------------------------------------------------------
    void reset();

//------------------------------------------------------------------------------
//  void print()
//  print the visitor
//
//------------------------------------------------------------------------------
    void print(ostream &buffer);

};
#endif //CLASSHDTIMERLSUPDATEVISITOR_H
