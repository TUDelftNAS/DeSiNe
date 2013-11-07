/******************************************************************************

    source file DesineData.cpp for class: DesineData

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/



// Include(s)
#include "IO/WaveSet.h"
#include "Main/Desine/DesineData.h"
#include "Utils/Types.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using std::endl;
using std::ostream;
using std::ofstream;
using std::left;
using std::setw;
using std::string;
using Types::uli;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor DesineData::DesineData(char* input)
//------------------------------------------------------------------------------
DesineData::DesineData(const string &name, const uli &number_of_qos,
                       const uli &flows)
          : Data(name)
{
    TRACE("DesineData::DesineData -->");
    flow_rejected_qos.resize(number_of_qos);

#ifndef NO_THROUGHPUT
    numflows.resize(flows);
    throughput.resize(flows);
#endif //NO_THROUGHPUT

    TRACE("DesineData::DesineData <--");
}


//------------------------------------------------------------------------------
//  destructor DesineData::~DesineData()
//------------------------------------------------------------------------------
DesineData::~DesineData()
{
    TRACE("DesineData::~DesineData -->");
    //Empty
    TRACE("DesineData::~DesineData <--");
}


//------------------------------------------------------------------------------
//  void DesineData::print(ostream& buffer)
//------------------------------------------------------------------------------
void DesineData::print(ostream& buffer) const
{
    TRACE("DesineData::print -->");

    int precision = buffer.precision(6);

    // Calculate mean over all QoS rejected flows and add them
    double flow_rej_qos = 0.0;
    for (uli iter = 0; iter < flow_rejected_qos.size(); ++iter)
    {
        flow_rej_qos += flow_rejected_qos[iter].getMean();
    }

    // Calculate Avg. hopcount and timers
    double flow_a = flow_accepted.getMean() +
                    flow_rejected_setup.getMean() +
                    flow_rej_qos;
    double avghop = flow_a ? hop_total.getMean()/flow_a : 0.0;

    buffer << left << setw(20) << name
    << "  UpdateNum  "   << setw(8) << update_num.getMean()
    << ": Accepted: "    << setw(8) << flow_accepted.getMean()
    << "  Blocked "      << setw(8) << flow_blocked.getMean()
    << "  RejectSetup: " << setw(8) << flow_rejected_setup.getMean()
    << "  RejectQoS: "   << setw(8) << flow_rej_qos
    << "  AvgHop: "      << setw(8) << avghop
    << "  Time(ms): "    << setw(8) << time_comp.getMean();
    buffer.precision(precision);

    TRACE("DesineData::print <--");
}


//------------------------------------------------------------------------------
//  void DesineData::write(LogFactory* logfact)
//------------------------------------------------------------------------------
void DesineData::write(const LogFactory* logfact) const
{
    TRACE("DesineData::write -->");

#ifndef NO_THROUGHPUT
    AbstractLog* log = logfact->createBinLog(name);
    AbstractLog::WSdouble waves(name);
    AbstractLog::WSdoubleVector vnumflows, vthroughput;

    for (uli iter = 0; iter < numflows.size(); ++iter)
    {
        vnumflows.push_back(numflows[iter].getMean());
        vthroughput.push_back(throughput[iter].getMean());
    }
    waves.insert("NumFlows"  , vnumflows);
    waves.insert("Throughput", vthroughput);

    log->open();
    log->append(waves);
    log->close();
    delete log;
#endif

    TRACE("DesineData::write <--");
}


//------------------------------------------------------------------------------
//  &Data DesineData::operator+=(const Data &data)
//------------------------------------------------------------------------------
Data& DesineData::operator+=(const Data &data)
{
    TRACE("DesineData::operator+= -->");

    DesineData* d = (DesineData*) &data;

    update_num          += d->update_num;
    flow_total          += d->flow_total;
    flow_accepted       += d->flow_accepted;
    flow_blocked        += d->flow_blocked;
    flow_rejected_setup += d->flow_rejected_setup;

    tp_total            += d->tp_total;
    tp_accepted         += d->tp_accepted;
    tp_blocked          += d->tp_blocked;
    tp_rejected_setup   += d->tp_rejected_setup;
    tp_rejected_qos     += d->tp_rejected_qos;

    hop_total           += d->hop_total;
    time_comp           += d->time_comp;

    for (uli iter = 0; iter < flow_rejected_qos.size(); ++iter)
    {
        flow_rejected_qos[iter] += d->flow_rejected_qos[iter];
    }

#ifndef NO_THROUGHPUT
    for (uli iter = 0; iter < numflows.size(); ++iter)
    {
        numflows[iter]    += d->numflows[iter];
        throughput[iter]  += d->throughput[iter];
    }
#endif

    TRACE("DesineData::operator+= <--");
    return *this;
}
