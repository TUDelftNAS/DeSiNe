/******************************************************************************

    source file LinkCostFunctionVisitorFactory.cpp for class:
            LinkCostFunctionVisitorFactoryFactory

    See header file for details

    The Link Cost Functions
    - Inverse
    - PowerDot
    - TEDBlc
    - Delta
    - Delta3
    - MidDelay
    - MinHop

    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "IO/Tag.h"
#include "LinkCostFunction/Delta3LCFVisitor.h"
#include "LinkCostFunction/DeltaLCFVisitor.h"
#include "LinkCostFunction/InverseLCFVisitor.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "LinkCostFunction/LinkCostFunctionVisitorFactory.h"
#include "LinkCostFunction/MinDelayLCFVisitor.h"
#include "LinkCostFunction/MinHopLCFVisitor.h"
#include "LinkCostFunction/PowerDot75LCFVisitor.h"
#include "LinkCostFunction/SquareSinLCFVisitor.h"
#include "LinkCostFunction/TEDBLCFVisitor.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;



// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor LinkCostFunctionVisitorFactory::LinkCostFunctionVisitorFactory()
//------------------------------------------------------------------------------
LinkCostFunctionVisitorFactory::LinkCostFunctionVisitorFactory()
{
  	TRACE("LinkCostFunctionVisitorFactory::LinkCostFunctionVisitorFactory -->");
    //Empty
  	TRACE("LinkCostFunctionVisitorFactory::LinkCostFunctionVisitorFactory <--");
}


//------------------------------------------------------------------------------
//  destructor LinkCostFunctionVisitorFactory::~LinkCostFunctionVisitorFactory()
//------------------------------------------------------------------------------
LinkCostFunctionVisitorFactory::~LinkCostFunctionVisitorFactory()
{
	TRACE("LinkCostFunctionVisitorFactory::~LinkCostFunctionVisitorFactory -->");
    //Empty
	TRACE("LinkCostFunctionVisitorFactory::~LinkCostFunctionVisitorFactory <--");
}


//------------------------------------------------------------------------------
//  LinkCostFunctionVisitor* create();
//------------------------------------------------------------------------------
LinkCostFunctionVisitor* LinkCostFunctionVisitorFactory::create(
    const string &specs)
{
   	TRACE("LinkCostFunctionVisitorFactory::create -->");

    LinkCostFunctionVisitor* result = (LinkCostFunctionVisitor*) 0;
    if ( specs == Tag::LCF_MIN_HOP)
    {
        result = new MinHopLCFVisitor();
    } else
    if ( specs == Tag::LCF_INVERSE)
    {
        result = new InverseLCFVisitor();
    } else
    if ( specs == Tag::LCF_PWRDOT75)
    {
        result = new PowerDot75LCFVisitor();
    } else
    if ( specs == Tag::LCF_DELTA)
    {
        result = new DeltaLCFVisitor();
    } else
    if ( specs == Tag::LCF_DELTA3)
    {
        result = new Delta3LCFVisitor();
    } else
    if ( specs == Tag::LCF_SQUARE_SIN)
    {
        result = new SquareSinLCFVisitor();
    } else
    if ( specs == Tag::LCF_MIN_DELAY)
    {
        result = new MinDelayLCFVisitor();
    } else
    if ( specs == Tag::LCF_TEDB)
    {
        result = new TEDBLCFVisitor();
    }
    //else if
   	TRACE("LinkCostFunctionVisitorFactory::create <--");
    return result;
}

