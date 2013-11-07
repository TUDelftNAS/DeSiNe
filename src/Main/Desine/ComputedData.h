#ifndef COMPUTEDDATA_H
#define COMPUTEDDATA_H
/******************************************************************************

    header file ComputedData.h for class: ComputedData

    This class forms the a subclass of Data to store simulation results
    for Desine


    Author : E. Astiz Lezaun
    Version: 1
    Date   : July 2005

******************************************************************************/


// Include(s)
#include "IO/LogFactory.h"
#include "Main/Data.h"
#include "Main/Desine/DesineData.h"
#include "Utils/Types.h"
#include <map>
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

class ComputedData : public Data
{
	private:
    // Typedef(s)
    typedef map<int, DesineData> MapColl;
    // Variables
    MapColl dataset;

    public:
    typedef MapColl::iterator iterator;
    typedef MapColl::const_iterator const_iterator;

//------------------------------------------------------------------------------
//
//  constructor ComputedData(const string &name, const vector<int>& flowIdList)
//
//  Constructs Data.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ComputedData(const string &name, const uli &number_of_qos, const vector<int>& flowIdList, const long flows);


//------------------------------------------------------------------------------
//
//  destructor ~ComputedData()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~ComputedData();


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

//------------------------------------------------------------------------------
//
//  DesineData* getDesineDataById(int flowId);
//
//  Looks up the flow list for the asociated DesineData with the flowId specified.
//
//  Input : flowId
//  Output: const FlowType* // We dont allow the programmer change the object pointed by the pointer
//
//------------------------------------------------------------------------------

    DesineData* getDesineDataById(int flowId);

    const DesineData* getDesineDataById(int flowId) const;

    iterator begin() { return dataset.begin(); }

	iterator end() { return dataset.end(); }

	const_iterator begin() const { return dataset.begin(); }

	const_iterator end() const { return dataset.end(); }

};
#endif //COMPUTEDDATA_H
