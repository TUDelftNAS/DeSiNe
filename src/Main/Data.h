#ifndef DATA_H
#define DATA_H
/******************************************************************************

    header file Data.h for class: Data

    This class forms the super class for all Data subclasses/interfaces


    Author : T. Kleiberg
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "IO/LogFactory.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <ostream>
#include <string>
using std::ostream;
using std::string;
using Types::DblVector;
using Types::DblMatrix;
using Types::StringVector;

class Data
{
    protected:
    string name;

    public:
//------------------------------------------------------------------------------
//
//  constructor Data(const string name)
//
//  Constructs Data.
//  Input : weightfactor : used when averaging with other Data instance
//  Output:
//
//------------------------------------------------------------------------------
    Data(const string name = "data")
    {
        TRACE("Data::Data -->");
        this->name = name;
        TRACE("Data::Data <--");
    }


//------------------------------------------------------------------------------
//
//  destructor ~RGModel()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~Data() {};


//------------------------------------------------------------------------------
//
//  const string getName()
//
//  Returns the name of the data object
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return name;
    }


//------------------------------------------------------------------------------
//
//  void print(ostream& buffer);
//
//  Print contents to a buffer (usually cout)
//
//------------------------------------------------------------------------------
    virtual void print(ostream& buffer) const = 0;


//------------------------------------------------------------------------------
//
//  void write()
//
//  Write contents to a log with filename-prefix being the name of the
//  data object.
//
//------------------------------------------------------------------------------
    virtual void write(const LogFactory* logfact) const
    {
        write(logfact, name);
    }


//------------------------------------------------------------------------------
//
//  void write()
//
//  Write contents to a log with a specific filename-prefix.
//
//------------------------------------------------------------------------------
    virtual void write(const LogFactory* logfact, const string filename) const
    {}


//------------------------------------------------------------------------------
//
//  virtual void operator+=(const Data &data) = 0;
//
//  Add other data instance and store averaged result
//
//------------------------------------------------------------------------------
    virtual Data& operator+=(const Data &data) = 0;
};
#endif //DATA_H
