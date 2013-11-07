#ifndef ABSTRACTTEXTLOG_H
#define ABSTRACTTEXTLOG_H
/******************************************************************************

    header file AbstractTextLog.h for class: AbstractTextLog

    This class is the abstract base class for all text log files

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/AbstractLog.h"
#include "Utils/TraceManager.h"

#include <string>
using std::string;

class AbstractTextLog : public AbstractLog
{
    // Friends

    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//  constructor AbstractTextLog()
//  Constructs AbstractTextLog
//  Input :
//------------------------------------------------------------------------------
    AbstractTextLog(const string &name, const string &path)
        : AbstractLog(name, path)
    {
        TRACE("AbstractTextLog::AbstractTextLog -->");
        //Empty!!
        TRACE("AbstractTextLog::AbstractTextLog <--");
    }


    public:
//------------------------------------------------------------------------------
//  destructor ~AbstractTextLog()
//  Destructs AbstractTextLog
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~AbstractTextLog()
    {
        TRACE("AbstractTextLog::~AbstractTextLog -->");
        //Empty!!
        TRACE("AbstractTextLog::~AbstractTextLog <--");
    }

}; //end declarations AbstractTextLog
#endif // ABSTRACTTEXTLOG_H
