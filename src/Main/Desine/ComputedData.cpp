/******************************************************************************

    source file ComputedData.cpp for class: ComputedData

    See header file for details

    Author : E. Astiz Lezaun
    Version: 1
    Date   : July 2005

******************************************************************************/



// Include(s)
#include "IO/WaveSet.h"
#include "Main/Desine/ComputedData.h"
#include "Utils/Types.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <typeinfo>
using std::endl;
using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::left;
using std::setw;
using std::string;
using Types::uli;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor ComputedData::DesineData(char* input)
//------------------------------------------------------------------------------
ComputedData::ComputedData(const string &name, const uli &number_of_qos, const vector<int>& flowIdList, const long flows)
          : Data(name)
{
    TRACE("ComputedData::ComputedData -->");
    vector<int>::const_iterator flowIdList_Iter;
    for(flowIdList_Iter=flowIdList.begin();flowIdList_Iter!=flowIdList.end();flowIdList_Iter++){
    	int id = *flowIdList_Iter;
    	ostringstream outs;
    	outs << name << "type" << id;
    	dataset.insert( std::make_pair(id, DesineData(outs.str(),id,number_of_qos,flows)));
	}
    TRACE("ComputedData::ComputedData <--");
}


//------------------------------------------------------------------------------
//  destructor ComputedData::~DesineData()
//------------------------------------------------------------------------------
ComputedData::~ComputedData()
{
    TRACE("ComputedData::~ComputedData -->");
    dataset.clear();
    TRACE("ComputedData::~ComputedData <--");
}


//------------------------------------------------------------------------------
//  void ComputedData::print(ostream& buffer)
//------------------------------------------------------------------------------
void ComputedData::print(ostream& buffer) const
{
    TRACE("ComputedData::print -->");
	for(MapColl::const_iterator iter = dataset.begin();
        iter != dataset.end(); ++iter)
    {
        iter->second.print(buffer);
        buffer << endl;
    }
    TRACE("ComputedData::print <--");
}


//------------------------------------------------------------------------------
//  void ComputedData::write(LogFactory* logfact)
//------------------------------------------------------------------------------
void ComputedData::write(const LogFactory* logfact) const
{
    TRACE("ComputedData::write -->");
    for(MapColl::const_iterator iter = dataset.begin();
        iter != dataset.end(); ++iter)
    {
        iter->second.write(logfact);
    }

    TRACE("ComputedData::write <--");
}


//------------------------------------------------------------------------------
//  &Data ComputedData::operator+=(const Data &data)
//------------------------------------------------------------------------------
Data& ComputedData::operator+=(const Data &data)
{
    TRACE("ComputedData::operator+= -->");
    try{
    	const ComputedData & foreignComputedData = dynamic_cast<const ComputedData&>(data);

	    for(MapColl::iterator iter = dataset.begin();
	        iter != dataset.end(); ++iter){
	        	iter->second+=*(foreignComputedData.getDesineDataById(iter->first));
	    }
	}
	catch(std::bad_cast){
		TRACE("ComputedData::operator+=: Incoming Data is not ComputedData");
		cout << "ComputedData::operator+=: Incoming Data is not ComputedData" << std::endl;
	}

    TRACE("ComputedData::operator+= <--");
    return *this;
}

//------------------------------------------------------------------------------
//  DesineData* ComputedData::getDesineDataById(int flowId)
//------------------------------------------------------------------------------
DesineData* ComputedData::getDesineDataById(int flowId)
{
	TRACE("ComputedData::getDesineDataById= -->");
	DesineData *desineData= (DesineData*)0;
	MapColl::iterator dataset_iter = dataset.find(flowId);

	if(dataset_iter != dataset.end() && dataset_iter->first == flowId){
		desineData = &dataset_iter->second;
	}

    TRACE("ComputedData::getDesineDataById= <--");
    return desineData;
}

const DesineData* ComputedData::getDesineDataById(int flowId) const{
	TRACE("ComputedData::getDesineDataById= -->");
	const DesineData *desineData= (DesineData*)0;
	MapColl::const_iterator dataset_iter = dataset.find(flowId);

	if(dataset_iter != dataset.end() && dataset_iter->first == flowId){
		desineData = &dataset_iter->second;
	}

    TRACE("ComputedData::getDesineDataById= <--");
    return desineData;
}

