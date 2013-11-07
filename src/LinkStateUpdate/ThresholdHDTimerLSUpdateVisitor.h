#ifndef THRESHOLDHDTIMERLSUPDATEVISITOR_H
#define THRESHOLDHDTIMERLSUPDATEVISITOR_H

/******************************************************************************

    header file ThresholdHDTimerLSUpdateVisitor.h for class:
    ThresholdHDTimerLSUpdateVisitor

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



class ThresholdHDTimerLSUpdateVisitor : public LinkStateUpdateVisitor
{
    private:
    const double threshold;
    const double holddown_time;
    double new_value_from_update;
    double current_known_capacity;
    double last_trigger_time;

    // the function used to check if the condition of update is met
    // and if so return the new updated_value
    // if not return the old one


    public:
//------------------------------------------------------------------------------
//
//  constructor ThresholdHDTimerLSUpdateVisitor();
//
//  Constructs ThresholdHDTimerLSUpdateVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    ThresholdHDTimerLSUpdateVisitor(
    	const double &threshold,
    	const double &holddown_time,
    	const bool &is_parent = true);


    public:
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
#endif //THRESHOLDHDTIMERLSUPDATEVISITOR_H
