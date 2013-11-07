#ifndef DESINEMAIN_H
#define DESINEMAIN_H
/******************************************************************************

    header file DesineMain.h for class: DesineMain

    This class forms the executable main.

    This object containss the executable part of Desine.

    The following arguments are accepted by the commandline:
    -> first argument MUST be the name of the parameter file
    -> the following optional arguments can be used (case sensitive):
        --v                   : verbose, display traces (see also NO_TRACES)
        --t                   : display topolgy at atartup (does not imply -v)
        --h, --help           : display help message


    Author : T. Kleiberg
    Version: 1
    Date   : Jan 2005
******************************************************************************/


// Include(s)
#include "IO/LogFactory.h"
#include "Parameter/Parameters.h"
#include <string>
using std::string;

// Class definition
class DesineMain
{
    // Constanst(s)

    // Variable declarations
    private:
    bool print_iter;
    string file_name;
    LogFactory* log_fct;
    Parameters* parameters;


    public:
//------------------------------------------------------------------------------
//
//  constructor DesineData(unsigned int weightfactor)
//
//  Constructs Data.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    DesineMain(int argc, const char* argv[]);


//------------------------------------------------------------------------------
//
//  destructor ~DesineData()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~DesineMain();


    private:
//------------------------------------------------------------------------------
//
//  void execute()
//
//------------------------------------------------------------------------------
    void execute();


//------------------------------------------------------------------------------
//
//  void showHelp()
//  Display help message
//
//------------------------------------------------------------------------------
    void showHelp();


//------------------------------------------------------------------------------
//
//  void showVersion()
//  Display version info
//
//------------------------------------------------------------------------------
    void showVersion();

}; //end DesineMain
#endif //DESINEDATA_H
