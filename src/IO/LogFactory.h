#ifndef LOGFACTORY_H
#define LOGFACTORY_H
/******************************************************************************

    header file LogFactory.h for class: LogFactory

    This class is a factory for creating Log objects. It's able to
    create various version of log writers intended for various programs
    (e.g. Igor or Matlab).

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/AbstractLog.h"
#include <string>
using std::string;

class LogFactory
{

    // Constanst(s)
    private:
    const string path;
    const string type;

    // Variable(s)

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor LogFactory();
//
//  Constructs LogFactory with given path foro the log files and
//  given type (as defined in Tag.h).
//
//------------------------------------------------------------------------------
    LogFactory(const string &path, const string &type);


//------------------------------------------------------------------------------
//
//  destructor ~LogFactory()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LogFactory();


//------------------------------------------------------------------------------
//  AbstractLog* createTextLog(const string &name);
//  Creates the binary logwriter
//  Input : the (file)name of the log
//  Output: AbstractLog
//------------------------------------------------------------------------------
    AbstractLog* createBinLog(const string &name) const;


//------------------------------------------------------------------------------
//  AbstractLog* createTextLog(const string &name);
//  Creates the text logwriter
//  Input : the (file)name of the log
//  Output: AbstractLog
//------------------------------------------------------------------------------
    AbstractLog* createTextLog(const string &name) const;


}; //end declarations
#endif //LOGFACTORY_H
