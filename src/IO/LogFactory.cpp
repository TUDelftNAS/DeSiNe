/******************************************************************************

    source file LogFactory.cpp for class: LogFactory

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/



// Include(s)
#include "IO/AbstractLog.h"
#include "IO/IgorBinaryLog.h"
#include "IO/IgorTextLog.h"
#include "IO/LogFactory.h"
#include "IO/Tag.h"
#include "Utils/TraceManager.h"


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor LogFactory::LogFactory()
//------------------------------------------------------------------------------
LogFactory::LogFactory(const string &path, const string &type)
    : path(path), type(type)
{
  	TRACE("LogFactory::LogFactory -->");
    //Empty
  	TRACE("LogFactory::LogFactory <--");
}


//------------------------------------------------------------------------------
//  destructor LogFactory::~LogFactory()
//------------------------------------------------------------------------------
LogFactory::~LogFactory()
{
	TRACE("LogFactory::~LogFactory -->");
    //Empty
	TRACE("LogFactory::~LogFactory <--");
}


//------------------------------------------------------------------------------
//  AbstractLog* createTextLog(const string &name);
//------------------------------------------------------------------------------
AbstractLog* LogFactory::createBinLog(const string &name) const
{
	TRACE("LogFactory::createBinLog -->");

    AbstractLog* result = (AbstractLog*) 0;
    if (type == Tag::LOG_TYPE_IGOR)
    {
        result = new IgorBinaryLog(name, path);
    }
	TRACE("LogFactory::createBinLog <--");
    return result;
}


//------------------------------------------------------------------------------
//  AbstractLog* createTextLog(const string &name);
//------------------------------------------------------------------------------
AbstractLog* LogFactory::createTextLog(const string &name) const
{
	TRACE("LogFactory::createTextLog -->");

    AbstractLog* result = (AbstractLog*) 0;
    if (type == Tag::LOG_TYPE_IGOR)
    {
        result = new IgorTextLog(name, path);
    }
	TRACE("LogFactory::createTextLog <--");
    return result;
}
