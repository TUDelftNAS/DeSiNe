#ifndef ABSTRACTLOG_H
#define ABSTRACTLOG_H
/******************************************************************************

    header file AbstractLog.h for class: AbstractLog

    This class is the abstract base class for all log files

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/WaveSet.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"

#include <string>
using std::string;
using Types::uli;
using Types::usi;

class AbstractLog
{
    // Typedefs
    public:
    typedef WaveSet<double> WSdouble;
    typedef WaveSet<long>  WSlong;
    typedef WaveSet<uli> WSuli;
    typedef WaveSet<short>  WSshort;
    typedef WaveSet<usi> WSusi;
    typedef WaveSet<string> WSstring;

    typedef WSdouble::WaveVector WSdoubleVector;
    typedef WSlong::WaveVector WSlongVector;
    typedef WSuli::WaveVector WSuliVector;
    typedef WSshort::WaveVector WSshortVector;
    typedef WSusi::WaveVector WSusiVector;
    typedef WSstring::WaveVector WSstringVector;

    // Friends

    // Constanst(s)

    // Variable(s)
    protected:
    const string name;
    const string path;

    private:

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//  constructor AbstractLog()
//  Constructs AbstractLog
//  Input :
//------------------------------------------------------------------------------
    AbstractLog(const string &name, const string &path) : name(name), path(path)
    {
        TRACE("AbstractLog::AbstractLog -->");
        TRACE("Creating new log, name: " << name);
        TRACE("Creating new log, path: " << path);
        TRACE("AbstractLog::AbstractLog <--");
    }


    public:
//------------------------------------------------------------------------------
//  destructor ~AbstractLog()
//  Destructs AbstractLog
//  Input :
//  Output:
//------------------------------------------------------------------------------
    virtual ~AbstractLog()
    {
        TRACE("AbstractLog::~AbstractLog -->");
        //Empty!!
        TRACE("AbstractLog::~AbstractLog <--");
    }


//------------------------------------------------------------------------------
//  void append();
//
//  Append to the abstractlog files. This function reads the info from the data
//  object and stores it in the correct file(s). For every type it is being
//  used for, a separate function meeds to be declared and defined because
//  ANSI C++ doesn't allow virual template functions
//------------------------------------------------------------------------------
    virtual void append(const WSdouble &ws) = 0;
    virtual void append(const WSlong &ws) = 0;
    virtual void append(const WSuli &ws) = 0;
    virtual void append(const WSshort &ws) = 0;
    virtual void append(const WSusi &ws) = 0;
    virtual void append(const WSstring &ws) = 0;


//------------------------------------------------------------------------------
//  void append();
//
//  Append to the abstractlog files. This function reads the info from the data
//  object and stores it in the correct file(s).
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  void close();
//
//  Closes the file for writing
//------------------------------------------------------------------------------
    virtual void close() = 0;


//------------------------------------------------------------------------------
//  void open();
//
//  Opens the file for writing
//------------------------------------------------------------------------------
    virtual void open() = 0;


    protected:
//------------------------------------------------------------------------------
//  string fixformat(const string x);
//
//  Replaces dots and spaces by underscores
//------------------------------------------------------------------------------
    string fixformat(const string &x) const
    {
        string result(x);
        for(string::size_type idx = result.find("."); idx != string::npos;
            idx = result.find("."))
        {
            result.replace(idx, 1, "_");
        }
        for(string::size_type idx = result.find(" "); idx != string::npos;
            idx = result.find(" "))
        {
            result.replace(idx, 1, "_");
        }
        return result;
    }

}; //end declarations AbstractLog
#endif // ABSTRACTLOG_H
