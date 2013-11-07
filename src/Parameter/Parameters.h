#ifndef PARAMETERS_H
#define PARAMETERS_H
/******************************************************************************

    header file Parameters.h for class: Parameters

    This class is used for holding all the variables. It uses ParamsReader
    to retrieve the parameters. It stores them in local member variables.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Parameter/ParamsReader.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/Types.h"
#include <ostream>
#include <string>
#include <vector>
using Types::TString;
using std::ostream;
using std::string;
using std::vector;

class Parameters
{
    // Constanst(s)

    // Variable(s)
    public:
    typedef vector<RandomVar*> RandomVarList;
    typedef vector<TString> TStringArray;

    long flows;                 // number of flows
    long warmup;                // number of warmup flows
    //long nodes;                 // number of nodes in the network
    int splitnum;		// split the amount of traffic between each s_d pair into several pieces
    int iterations;             // number of iterations
    RandomNumberGenerator* rng; // rn generator
    string log_dir;             // log directory
    string log_type;            // log type
    TString topology;           // description for building topology
                                // See TopologyFactory.cpp for more info
    RandomVar* endpoints;       // end point distribution
    RandomVar* f_arrival;       // flow arrival distribution
    RandomVar* f_duration;      // flow duration
    RandomVar* f_bandwidth;     // flow bandwidth
    RandomVar* l_capacity;      // link capacity
    RandomVarList qos_cons;    // flow_qos_contraints
    TStringArray algorithms;   // algorithms
    TStringArray lsupdate_info;// link state update information


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor PParameters(const string parameter_file);
//
//  Constructs Parameters.
//  Input :
//      parameter_file : name of textfile with the parameters
//  Output:
//
//------------------------------------------------------------------------------
    Parameters(const string &parameter_file);


//------------------------------------------------------------------------------
//
//  destructor ~Parameters()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~Parameters();


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints parameter values to a stream
//
//  Input : stream buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;


    protected:
//------------------------------------------------------------------------------
//
//  RandomVar* createDistribution(TString* specs);
//
//  Create a distribution
//  Input :
//     specs : distribution specs, e.g. U 1 10
//  Output:
//     dist : the newly created distribution object
//------------------------------------------------------------------------------
    RandomVar* createDistribution(const TString &specs);

    private:
//------------------------------------------------------------------------------
//
//  void readParameters(char* parameter_file);
//
//  Reads parameters from the file. Invoked by comntructor. It also writes the
//  log files Specification and Algorithms (see above)
//  Input : parameter file name
//  Output:
//
//------------------------------------------------------------------------------
    void readParameters(const string &parameter_file);

}; //end declarations
#endif //PARAMETERS_H
