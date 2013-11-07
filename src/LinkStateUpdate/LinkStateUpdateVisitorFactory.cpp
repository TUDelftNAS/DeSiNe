/******************************************************************************

    source file LinkStateUpdateVisitorFactory.cpp for class:
            LinkStateUpdateVisitorFactoryFactory

    See header file for details

    Author : Bingjie FU
    Version: 1
    Date   : Jan 2005

******************************************************************************/



// Include(s)
#include "IO/Tag.h"
#include "LinkStateUpdate/LinkStateUpdateVisitorFactory.h"
#include "LinkStateUpdate/MovingAverageAbsoluteLSUpdateVisitor.h"
#include "LinkStateUpdate/MovingAverageClassLSUpdateVisitor.h"
#include "LinkStateUpdate/MovingAverageRelativeLSUpdateVisitor.h"
#include "LinkStateUpdate/PeriodLSUpdateVisitor.h"
#include "LinkStateUpdate/ClassHDTimerLSUpdateVisitor.h"
#include "LinkStateUpdate/ThresholdHDTimerLSUpdateVisitor.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor LinkStateUpdateVisitorFactory::LinkStateUpdateVisitorFactory()
//------------------------------------------------------------------------------
LinkStateUpdateVisitorFactory::LinkStateUpdateVisitorFactory()
{
    TRACE("LinkStateUpdateVisitorFactory::LinkStateUpdateVisitorFactory -->");
    //Empty
    TRACE("LinkStateUpdateVisitorFactory::LinkStateUpdateVisitorFactory <--");
}


//------------------------------------------------------------------------------
//  destructor LinkStateUpdateVisitorFactory::~LinkStateUpdateVisitorFactory()
//------------------------------------------------------------------------------
LinkStateUpdateVisitorFactory::~LinkStateUpdateVisitorFactory()
{
    TRACE("LinkStateUpdateVisitorFactory::~LinkStateUpdateVisitorFactory -->");
    //Empty
    TRACE("LinkStateUpdateVisitorFactory::~LinkStateUpdateVisitorFactory <--");
}


//------------------------------------------------------------------------------
//  LinkStateUpdateVisitor* create();
//------------------------------------------------------------------------------
LinkStateUpdateVisitor* LinkStateUpdateVisitorFactory::create(const TString &specs)
{
    TRACE("LinkStateUpdateVisitorFactory::create -->");

    //PRINTLN("specs.size: " << (specs.size()) << "\n");

    string policy = specs.front();
    LinkStateUpdateVisitor* result = (LinkStateUpdateVisitor*) 0;
    if (policy == Tag::LSU_MOVINGAVERAGE_RELATIVE)
    {
        int window_size  = atoi(specs.at(1).c_str());
        double threshold = atof(specs.at(2).c_str());
        result = new MovingAverageRelativeLSUpdateVisitor(window_size, threshold);
    } else
    if (policy == Tag::LSU_MOVINGAVERAGE_ABSOLUTE)
    {
        int window_size  = atoi(specs.at(1).c_str());
        double threshold = atof(specs.at(2).c_str());
        result = new MovingAverageAbsoluteLSUpdateVisitor(window_size, threshold);
    } else
    if (policy == Tag::LSU_MOVINGAVERAGE_CLASS)
    {
        int window_size      = atoi(specs.at(1).c_str());
        double growth_factor = atof(specs.at(2).c_str());
        double bandw_base    = atof(specs.at(3).c_str());
        result = new MovingAverageClassLSUpdateVisitor(window_size,
            growth_factor, bandw_base);
    } else
    if (policy == Tag::LSU_PERIOD)
    {
        double period = atof(specs.at(1).c_str());
        result = new PeriodLSUpdateVisitor(period);
    } else
    if (policy == Tag::LSU_HOLDDOWNTIMER_CLASS)
    {
        double period = atof(specs.at(1).c_str());
        double growth_factor = atof(specs.at(2).c_str());
        double bandw_base    = atof(specs.at(3).c_str());
        result = new ClassHDTimerLSUpdateVisitor(period, growth_factor, bandw_base);
    } else
    if (policy == Tag::LSU_HOLDDOWNTIMER_THRESHOLD)
    {
        double period = atof(specs.at(1).c_str());
        double threshold = atof(specs.at(2).c_str());
        result = new ThresholdHDTimerLSUpdateVisitor(period, threshold);
    }
    //else if
    TRACE("LinkStateUpdateVisitorFactory::create <--");
    return result;
}

