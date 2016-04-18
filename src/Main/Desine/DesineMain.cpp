/******************************************************************************

    source file DesineMain.cpp for class: DesineMain

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/AlgorithmFactory.h"
#include "IO/AbstractLog.h"
#include "LinkStateUpdate/LinkStateUpdateVisitorFactory.h"
#include "Main/Data.h"
#include "Main/Desine/DesineMain.h"
#include "Main/Desine/DesineModel.h"
#include "Main/Desine/DesineSumData.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include "Utils/Utils.h"
#include <cstdlib>
#include <cstring>
#include <new>
#include <fstream>
using std::set_new_handler;
using std::ofstream;
using Types::uli;
using std::endl;

//------------------------------------------------------------------------------
//  constructor DesineMain(int argc, const char* argv[])
//------------------------------------------------------------------------------
DesineMain::DesineMain(int argc, const char* argv[])
{
    // Initialize
    print_iter = false;
    file_name = "out";
    TraceManager::initialize();

    // Read commandline arguments, first two arguments are exe and parameterfile
    if (argc < 2 || strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        showHelp();
        exit(0);
    }
    if (strcmp(argv[1], "--V") == 0 || strcmp(argv[1], "--version") == 0)
    {
        showVersion();
        exit(0);
    }
    for (int count = 2; count < argc; ++count)
    {
#ifndef NO_TRACES
        if (strcmp(argv[count], "--v") == 0)
        {
            TraceManager::start();
            TRACE("TraceManager started...");
        } else
#endif //NO_TRACES
        if (strcmp(argv[count], "--print") == 0)
        {
            print_iter = true;
        } else
        if (strcmp(argv[count], "--filename") == 0)
        {
            file_name = argv[++count];
        } else
        {
            PRINTLN("Error: Unrecognized argument: " << argv[count]);
            showHelp();
            exit(0);
        }
    }

    TRACE("DesineMain::DesineMain -->");

    // Show start time and arguments
    PRINT(  "# Desine started        : "); getCurrentTime(cout);
    PRINTLN("# Parameter file        : " << argv[1]);
    PRINTLN("# Print to stdout       : " << (print_iter ? "yes" : "no"));
    PRINTLN("# Output filename       : " << file_name);

    parameters = new Parameters(argv[1]);
    log_fct = new LogFactory(parameters->log_dir, parameters->log_type);

    // Check linnk state update info
    if (parameters->lsupdate_info.size() == 0)
    {
        WARNING("Missing linkstate update policy information in parameter"
             << " file. Not using linkstate update policies.");
    }

    // Create spec. log file
    if (1)
    {
        string filename = parameters->log_dir + string("/") +
                          file_name + string("_specs.txt");
        ofstream log_s(filename.c_str());
        parameters->print(log_s);
        log_s.close();
    }
    execute();
    // Show end time
    PRINT("# Desine finished: "); getCurrentTime(cout); PRINTLN("");
    TRACE("DesineMain::DesineMain <--");
}


//------------------------------------------------------------------------------
//
//  destructor ~DesineMain()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
DesineMain::~DesineMain()
{
    TRACE("DesineMain::~DesineMain -->");
    if (parameters) delete parameters;
    if (log_fct) delete log_fct;
    TRACE("DesineMain::~DesineMain <--");
}


//------------------------------------------------------------------------------
//
//  void execute()
//
//------------------------------------------------------------------------------
void DesineMain::execute()
{
    TRACE("DesineMain::execute -->");

    AlgorithmFactory alg_fct;
    LinkStateUpdateVisitorFactory lsuv_fct;

    int number_of_alg = parameters->algorithms.size();
    DesineSumData sumdata(file_name);

    //----------------------------------------------------------------------
    //
    //   S T A R T
    //
    //----------------------------------------------------------------------
    uli lsu_iter = 0;
    do
    {
        // Set Link State Update Visitor
        LinkStateUpdateVisitor *lsuv = (LinkStateUpdateVisitor*) 0;
        if (!parameters->lsupdate_info.empty())
        {
            lsuv = lsuv_fct.create(parameters->lsupdate_info[lsu_iter]);
        } // end: if (parameters->lsupdate_info->size()

        for (int ai = 0; ai < number_of_alg; ++ai)
        {
            Algorithm* alg = alg_fct.create(parameters->algorithms[ai] );
            DesineModel* model = new DesineModel(parameters, alg, lsuv);
            Data* data = model->execute(parameters->iterations);

            // Simulation finished, store results
            if (print_iter)
            {
                data->print(cout);
                cout << endl;
            }
            data->write(log_fct);

            sumdata += (*data);

            // Clear database
            delete data;
            delete model;
            delete alg;
        } // end: for (int ai    or end of process in case of MP
        if (lsuv) delete lsuv;
        ++lsu_iter;
    } while (lsu_iter < parameters->lsupdate_info.size()); // end: do..

    //----------------------------------------------------------------------
    //
    //   E N D
    //
    //----------------------------------------------------------------------

    sumdata.write(log_fct);

    // deleting references
    TRACE("DesineMain::execute <--");
}


//------------------------------------------------------------------------------
//  void showHelp()
//------------------------------------------------------------------------------
void DesineMain::showHelp()
{
    PRINTLN("Desine network flow simulator help message.");
    PRINTLN("Usage: desine <parameter-file> [OPTIONS]");
    PRINTLN("\t<parameter-file> : the parameter file");
    PRINTLN("");
    PRINTLN("\tOPTIONS:");
#ifndef NO_TRACES
    PRINTLN("\t--v              : verbose mode (for debugging purposes)");
#endif //NO_TRACES
    PRINTLN("\t--h, --help      : display this help message");
    PRINTLN("\t--print          : print results after an iterations-run")
    PRINTLN("\t--V, --version   : display version and compile date");
    PRINTLN("\t--filename <nm>  : set base filename <nm> for result filenames")
    PRINTLN("\t                   default filename is 'out'")
    PRINTLN("")
}


//------------------------------------------------------------------------------
//  void showHelp()
//------------------------------------------------------------------------------
void DesineMain::showVersion()
{
    PRINTLN("Desine v1.0");
    PRINTLN("Compile date: " << __DATE__ << " " << __TIME__);
}


//------------------------------------------------------------------------------
//  out_of_memory handler function
//------------------------------------------------------------------------------
void out_of_memory()
{
    ERROR("Insufficient memory!! Aborting.");
    exit(-1);
}


// Function declarations
int main(int argc, const char* argv[])
{
    // Set out of memory handler
    set_new_handler(out_of_memory);
    DesineMain *nsm = new DesineMain(argc, argv);
    delete nsm;
    return 0;
}
