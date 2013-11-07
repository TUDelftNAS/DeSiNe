#ifndef IGORTEXTLOG_H
#define IGORTEXTLOG_H
/******************************************************************************

    header file IgorTextLog.h for class: IgorTextLog

    This class is the igor base class for all binary log files

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/AbstractTextLog.h"
#include "IO/WaveSet.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"

#include <fstream>
#include <string>
using std::ofstream;
using std::string;
using Types::uli;

class IgorTextLog : public AbstractTextLog
{
    // Friends
    friend class LogFactory;

    // Constanst(s)

    // Variable(s)
    private:
    typedef vector<WSdouble> VectorWSdouble;
    typedef vector<WSlong> VectorWSlong;
    typedef vector<WSuli> VectorWSuli;
    typedef vector<WSstring> VectorWSstring;

    VectorWSdouble doubleSet;
    VectorWSlong longSet;
    VectorWSuli uliSet;
    VectorWSstring stringSet;

    string txtname;
    ofstream txtbuffer;

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//  constructor IgorTextLog()
//  Constructs IgorTextLog
//  Input :
//------------------------------------------------------------------------------
    IgorTextLog(const string &name, const string &path);


    public:
//------------------------------------------------------------------------------
//  destructor ~IgorTextLog()
//  Destructs IgorTextLog
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~IgorTextLog();


//------------------------------------------------------------------------------
//  void append();
//
//  Append to the abstractlog files. This function reads the info from the data object
//  and stores it in the correct file(s).
//------------------------------------------------------------------------------
    void append(const WSdouble &ws) { doubleSet.push_back(ws); }
    void append(const WSlong &ws) { longSet.push_back(ws); }
    void append(const WSuli &ws) { uliSet.push_back(ws); }
    void append(const WSshort &ws) { //longSet.push_back(ws);
    	}
    void append(const WSusi &ws) { //uliSet.push_back(ws);
    	}
    void append(const WSstring &ws) { stringSet.push_back(ws); }

//------------------------------------------------------------------------------
//  void close();
//
//  Closes the file for writing
//------------------------------------------------------------------------------
    void close();


//------------------------------------------------------------------------------
//  void open();
//
//  Opens the file for writing
//------------------------------------------------------------------------------
    void open();


    private:
//------------------------------------------------------------------------------
//  void print();
//
//  Print a vector of WaveSets to a buffer. If index < 0, the names are written.
//  Index is the position within the waveset-vector that must be written.
//  Returns true if anything is written (i.e. index is within range or < 0).
//------------------------------------------------------------------------------
    template <typename T>
    bool print(ostream &buffer, const vector<T>& ws, const long &index) const;

}; //end declarations IgorTextLog
#endif // IGORTEXTLOG_H
