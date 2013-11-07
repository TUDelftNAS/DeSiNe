#ifndef MOVINGAVERAGECLASSLSUPDATEVISITOR_H
#define MOVINGAVERAGECLASSLSUPDATEVISITOR_H

/******************************************************************************

    header file MovingAverageClassLSUpdateVisitor.h for class:
    MovingAverageClassLSUpdateVisitor

    This class is meant to represent an instance of ANEV for link-state update


    Author : Bingjie FU
    Version: 1
    Date   : Feb 2005

******************************************************************************/

#include "LinkStateUpdate/LinkStateUpdateVisitor.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
using Types::DblVector;


class MovingAverageClassLSUpdateVisitor : public LinkStateUpdateVisitor
{
    private:
    const int window_size;        // may be got from the parameters
    const double growth_factor;   // may be got from the parameters
    const double bandw_base;       // the bandwidth of base class, may be got from parameters

    double new_value_from_update;
    double current_known_capacity;
    double last_N_average;
    DblVector bound_vec;   // store the boundaries of each class
    int current_class;      // store the current class number


    // the function used to check if the condition of update is met
    // and if so return the new updated_value
    // if not return the old one


    public:
//------------------------------------------------------------------------------
//
//  constructor MovingAverageClassLSUpdateVisitor();
//
//  Constructs MovingAverageClassLSUpdateVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    MovingAverageClassLSUpdateVisitor(
		const int &window_size,
	    const double &growth_factor,
	    const double &bandw_base,
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
#endif //MOVINGAVERAGEClASSLSUPDATEVISITOR_H
