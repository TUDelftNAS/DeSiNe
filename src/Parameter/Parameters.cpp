/******************************************************************************

    source file Parameters.cpp for class: Parameters

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "IO/Tag.h"
#include "Parameter/Parameters.h"
#include "Parameter/ParamsReader.h"
#include "RandomVariables/ConstantVar.h"
#include "RandomVariables/ExponentialVar.h"
#include "RandomVariables/MixedVar.h"
#include "RandomVariables/RandomVar.h"
#include "RandomVariables/UniformVar.h"
#include "Utils/Types.h"
#include <cstdlib>
#include <iostream>
#include <string>
using std::cerr;
using std::endl;
using std::ostream;
using std::string;
using Types::uli;
using Types::DblVector;


// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor Parameters::Parameters(const string parameter_file);
//------------------------------------------------------------------------------
Parameters::Parameters(const string &parameter_file)
{
    TRACE("Parameters::Parameters -->");

    endpoints   = (RandomVar*) 0;
    f_arrival   = (RandomVar*) 0;
    f_duration  = (RandomVar*) 0;
    f_bandwidth = (RandomVar*) 0;
    l_capacity  = (RandomVar*) 0;
    readParameters(parameter_file);

    TRACE("Parameters::Parameters <--");
}


//------------------------------------------------------------------------------
//  destructor Parameters::~Parameters()
//------------------------------------------------------------------------------
Parameters::~Parameters()
{
    TRACE("Parameters::~Parameters -->");
    if (f_arrival) delete f_arrival;
    if (f_duration) delete f_duration;
    if (f_bandwidth) delete f_bandwidth;
    if (l_capacity) delete l_capacity;

    while(!qos_cons.empty())
    {
        delete qos_cons.back();
        qos_cons.pop_back();
    }

    TRACE("Parameters::~Parameters <--");
}


//------------------------------------------------------------------------------
//  RandomVar* createDistribution(TString* specs);
//------------------------------------------------------------------------------
RandomVar* Parameters::createDistribution(const TString &specs)
{
    TRACE("Parameters::createDistribution -->");
    RandomVar* result;
    std::size_t tsindex = 0;
    string dist_type = specs.at(tsindex++);  // read 1st word, type of distr.

    if (dist_type == "C")                               // Constant
    {
        double val = atof(specs.at(tsindex++).c_str());  // Value
        result = (RandomVar*) new ConstantVar(rng, val);
    } else
    if (dist_type == "U")                               // Uniform
    {
        double min = atof(specs.at(tsindex++).c_str());  // Min
        double max = atof(specs.at(tsindex++).c_str());  // Max
        result = (RandomVar*) new UniformVar(rng, min, max);
    } else
    if (dist_type == "E")                               // Exponential
    {
        double mean = atof(specs.at(tsindex++).c_str()); // Mean
        result = (RandomVar*) new ExponentialVar(rng, mean);
    }
    else // a numbder, so a mixed variable
    {
        int number = atoi(dist_type.c_str());
		 //

        // MixedVar destroys vars, only destroy vector here
        DblVector probs(number);
        MixedVar::RandomVarVector vars(number);

        for (int i = 0; i < number; ++i)
        {
            dist_type = specs.at(tsindex++);                     // Distribution
            if (dist_type == "C")                               // Constant
            {
                double val = atof(specs.at(tsindex++).c_str());  // Value

                probs[i] = atof(specs.at(tsindex++).c_str());    // Probability
                vars[i] = (RandomVar*) new ConstantVar(rng, val);
            } else
            if (dist_type == "U")                               // Uniform
            {
                double min = atof(specs.at(tsindex++).c_str());  // Min
                double max = atof(specs.at(tsindex++).c_str());  // Max

                probs[i] = atof(specs.at(tsindex++).c_str());    // Probability
                vars[i] = (RandomVar*) new UniformVar(rng, min, max);
            } else
            if (dist_type == "E")        // Exponential
            {
                double mean = atof(specs.at(tsindex++).c_str()); // Mean

                probs[i] = atof(specs.at(tsindex++).c_str());    // Probability
                vars[i] = (RandomVar*) new ExponentialVar(rng, mean);
            }
        } //for (int i = 0; i < number; i++)
        result = (RandomVar*) new MixedVar(rng, vars, probs);
    } //else: a number, so a mixed variable

    TRACE("Parameters::createDistribution <--");
    return result;
}


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void Parameters::print(ostream &buffer) const
{
    buffer
    << Tag::FLOWS << "  " << flows << endl
    << Tag::WARMUP << "  " << warmup << endl
    << Tag::ITERATIONS << "  " << iterations << endl
    << Tag::TOPOLOGY << "  ";
   // topology.print(buffer);
    buffer << endl

    << Tag::LOG_DIR << "  " << log_dir << endl
    << Tag::LOG_TYPE << "  " << log_type << endl
    << Tag::SEED << " " << rng->getSeed() << endl

    << Tag::ENDPOINTS << "  ";
    endpoints->print(buffer);
    buffer << endl

    << Tag::F_ARRIVAL << "  ";
    f_arrival->print(buffer);
    buffer << endl

    << Tag::F_DURATION << "  ";
    f_duration->print(buffer);
    buffer << endl

    << Tag::F_BANDWIDTH << "  ";
    f_bandwidth->print(buffer);
    buffer << endl;

    for (uli iter = 0; iter < qos_cons.size(); ++iter)
    {
        buffer << Tag::QOS_CONS << "(" << iter << ")  ";
        qos_cons.at(iter)->print(buffer);
        buffer << endl;
    }
}


//------------------------------------------------------------------------------
//  void readParameters(const string parameter_file);
//------------------------------------------------------------------------------
void Parameters::readParameters(const string &parameter_file)
{
    TRACE("Parameters::readParameters -->");

    ParamsReader preader(parameter_file);
    TString ts;
    // Reading Log dir parameter
    ts = preader.getParameter(Tag::LOG_DIR);
    if (!ts.empty())
    {
        log_dir = ts.front();
    }
    else
    {
        log_dir = ".";
    }

    // Reading Log dir parameter
    ts = preader.getParameter(Tag::LOG_TYPE);
    if (!ts.empty())
    {
        log_type = ts.front();
    }
    else
    {
        log_type = Tag::LOG_TYPE_IGOR;
    }

    // Read each parameter separately, because every parametertype is treated
    // differently. Use Tag.h as a reference to the types.
    ts = preader.getParameter(Tag::FLOWS);
    if (!ts.empty())
    {
        flows = atol(ts.front().c_str());
    }
    ts = preader.getParameter(Tag::WARMUP);
    if (!ts.empty())
    {
        warmup = atol(ts.front().c_str());
    }
    ts = preader.getParameter(Tag::ITERATIONS);
    if (!ts.empty())
    {
        iterations = atoi(ts.front().c_str());
    }
    ts = preader.getParameter(Tag::TOPOLOGY);
    if (!ts.empty())
    {
        topology = ts;
    }
    //ts = preader.getParameter(Tag::NODES);
    //if (!ts.empty())
    //{
    //    nodes = atol(ts.front().c_str());
    //}
    // if SEED not found, use default seed specified in RandomGenerator
    ts = preader.getParameter(Tag::SEED);
    rng = RandomNumberGenerator::getRandomNumberGenerator();
    if (!ts.empty())
    {
        rng->setSeed(atol(ts.front().c_str()));
    }
    ts = preader.getParameter(Tag::L_CAPACITY);
    if (!ts.empty())
    {
        l_capacity = createDistribution(ts);
    }
    // endpoints are dependend on number of edge nodes and so topology dependend
    // calculation of source and dest must be scaled in other class, here only
    // the distribution-type is created.
    ts = preader.getParameter(Tag::ENDPOINTS);
    if (!ts.empty())
    {
        if (ts.front() == "E")
        {
            ts.push_back("0.25");
        } else
        if (ts.front() == "U")
        {
            ts.push_back("0.0");
            ts.push_back("1.0");
        }
        endpoints = createDistribution(ts);
    }
    ts = preader.getParameter(Tag::F_ARRIVAL);
    if (!ts.empty())
    {
        f_arrival = createDistribution(ts);
    }
    ts = preader.getParameter(Tag::F_DURATION);
    if (!ts.empty())
    {
        f_duration = createDistribution(ts);
    }
    ts = preader.getParameter(Tag::F_BANDWIDTH);
    if (!ts.empty())
    {
        f_bandwidth = createDistribution(ts);
    }
    ts = preader.getParameter(Tag::SPLIT_NUM);
    if (!ts.empty())
    {
        splitnum = atoi(ts.front().c_str());
    }
    // mulitple occurence of QoS
    for (ts = preader.getParameter(Tag::QOS_CONS); !ts.empty();
         ts = preader.getNextParameter())
    {
        // create QoSCons list
        RandomVar* rv = createDistribution(ts);
        qos_cons.push_back(rv);
    }

    // mulitple occurence of Algorithms
    for (ts = preader.getParameter(Tag::ALGORITHM); !ts.empty();
         ts = preader.getNextParameter())
    {
        algorithms.push_back(ts);
    }

    // multiple occurence of Link State Update
    for (ts = preader.getParameter(Tag::LSUPDATEINFO); !ts.empty();
         ts = preader.getNextParameter())
    {
        lsupdate_info.push_back(ts);
    }
    TRACE("Parameters::readParameters <--");
}
