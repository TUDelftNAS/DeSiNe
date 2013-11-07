#ifndef IGORBINARYLOG_H
#define IGORBINARYLOG_H
/******************************************************************************

    header file IgorBinaryLog.h for class: IgorBinaryLog

    This class is the igor base class for all binary log files

	The name structure is as follows:
	ipf: <logpath><logname>.ipf
	bin: <logpath><logname>_W_<waveset>.bin
	wav: <waveset>_<wavename>

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/AbstractBinaryLog.h"
#include "IO/WaveSet.h"
#include "Utils/TraceManager.h"

#include <fstream>
#include <string>
using std::ofstream;
using std::string;


class IgorBinaryLog : public AbstractBinaryLog
{
    // Friends
    friend class LogFactory;

    // Constanst(s)

    // Variable(s)
    private:
    string ipfname;
    string binpref;
    ofstream ipfbuffer;


    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//  constructor IgorBinaryLog()
//  Constructs IgorBinaryLog
//  Input :
//------------------------------------------------------------------------------
    IgorBinaryLog(const string &name, const string &path);


    public:
//------------------------------------------------------------------------------
//  destructor ~IgorBinaryLog()
//  Destructs IgorBinaryLog
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~IgorBinaryLog();


//------------------------------------------------------------------------------
//  void append();
//
//  Append to the abstractlog files. This function reads the info from the data object
//  and stores it in the correct file(s).
//------------------------------------------------------------------------------
    void append(const WSdouble &ws) { append<double>(ws); }
    void append(const WSlong &ws) { append<long>(ws); }
    void append(const WSuli &ws) { append<uli>(ws); }
    void append(const WSshort &ws) { append<short>(ws); }
    void append(const WSusi &ws) { append<usi>(ws); }
    void append(const WSstring &ws) {} // Empty, no valid argument


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
//  void append(const WaveSet<T>& ws);
//
//  Append to the file, template function for virrtual funcs
//------------------------------------------------------------------------------
    template <typename T>
    void append(const WaveSet<T>& ws);

}; //end declarations IgorBinaryLog
#endif // IGORBINARYLOG_H
