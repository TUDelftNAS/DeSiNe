#ifndef DESINEDATA_H
#define DESINEDATA_H
/******************************************************************************

    header file DesineData.h for class: DesineData

    This class forms the a subclass of Data to store simulation results
    for Desine


    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "IO/LogFactory.h"
#include "Main/Data.h"
#include "Utils/Types.h"
#include <ostream>
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;
using Types::usi;
using Types::uli;
using Types::DblVector;
using Types::UliVector;
using Types::DVuli;
using Types::DVdouble;
using Types::SVuli;
using Types::SVdouble;


class DesineData : public Data
{
    // Typedef(s)
    public:
    DVuli update_num;          // total number of update for the number of flows
    DVuli flow_total;          // total number of flows generated
    DVuli flow_accepted;       // total number of flows accepted
    DVuli flow_blocked;        // total number of flows blocked due to capacity
    DVuli flow_rejected_setup; // total number of flows rejected due to setup
    vector<DVuli> flow_rejected_qos;  // flows rejected due to qos[x]

    DVdouble tp_total;         // total throughput
    DVdouble tp_accepted;      // accepted throughput
    DVdouble tp_blocked;       // blocked throughput
    DVdouble tp_rejected_setup;// rejected throughput due to setup failure
    DVdouble tp_rejected_qos;  // rejected throughput due to qos constraints

    DVuli hop_total;           // total hops (used for avg hopcounmt)
    DVdouble time_comp;        // total computation time

#ifndef NO_THROUGHPUT
    vector<SVuli> numflows;       // number of flows (array of size #flows)
    vector<SVdouble> throughput;  // throughput (array of size #flows)
#endif



//------------------------------------------------------------------------------
//
//  constructor DesineData(unsigned int weightfactor)
//
//  Constructs Data.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    DesineData(const string &name, const uli &number_of_qos, const uli &flows);


//------------------------------------------------------------------------------
//
//  destructor ~DesineData()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~DesineData();


//------------------------------------------------------------------------------
//
//  void print(ostream& buffer);
//
//  Print contents to a buffer (usually cout)
//
//------------------------------------------------------------------------------
    void print(ostream& buffer) const;


//------------------------------------------------------------------------------
//
//  void write(LogFactory* log);
//
//  Write contents to a log created with this factory
//
//------------------------------------------------------------------------------
    void write(const LogFactory* logfact) const;


//------------------------------------------------------------------------------
//
//  operator+=(const Data &data);
//
//  Add other data instance and store averaged result
//
//------------------------------------------------------------------------------
    Data& operator+=(const Data &data);

};
#endif //DESINEDATA_H
