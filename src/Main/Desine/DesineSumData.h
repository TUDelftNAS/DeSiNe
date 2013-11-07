#ifndef DESINESUMDATA_H
#define DESINESUMDATA_H
/******************************************************************************

    header file DesineSumData.h for class: DesineSumData

    This class forms the a subclass of Data to store summarized results
    for Desine. It summarizes over DesineData objects.


    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/LogFactory.h"
#include "Main/Data.h"
#include "Main/Desine/DesineData.h"
#include <ostream>
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;


class DesineSumData : public Data
{
    // Typedef(s)
    private:
    typedef vector<DesineData> DesineDataVector;

    // Variables
    DesineDataVector dataset;

    public:
//------------------------------------------------------------------------------
//
//  constructor DesineSumData(unsigned int weightfactor)
//
//  Constructs Data.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    DesineSumData(const string &name);


//------------------------------------------------------------------------------
//
//  destructor ~DesineSumData()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~DesineSumData();


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
//  void write(AbstractLog* log)
//
//  Write contents to a log
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
#endif //DESINESUMDATA_H
