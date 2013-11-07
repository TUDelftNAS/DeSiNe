/******************************************************************************

    source file ParamsReader.cpp for class: ParamsReader

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "IO/FileReader.h"
#include "IO/Tag.h"
#include "Parameter/ParamsReader.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor ParamsReader::ParamsReader(const string parameter_file)
//------------------------------------------------------------------------------
ParamsReader::ParamsReader(const string parameter_file)
{
    TRACE("ParamsReader::ParamsReader -->");
    file_reader = new FileReader(parameter_file);
    if (file_reader == (FileReader*) 0)
    {
        ERROR("Problems opening parameter file: " << parameter_file);
        exit(-1);
    }
    token_list.reserve(20);
    readParameters();
    TRACE("ParamsReader::ParamsReader <--");
}


//------------------------------------------------------------------------------
//  destructor ParamsReader::~ParamsReader()
//------------------------------------------------------------------------------
ParamsReader::~ParamsReader()
{
    TRACE("ParamsReader::~ParamsReader -->");
    delete file_reader;
    TRACE("ParamsReader::~ParamsReader <--");
}


//------------------------------------------------------------------------------
//  TString* getParameter(string key)
//------------------------------------------------------------------------------
TString ParamsReader::getParameter(const string key)
{
    TRACE("ParamsReader::getParameter -->");
    vectorindex = 0; // reset the index to the start of the vector
    searchkey = key;
    TRACE("Parameter Tag: " << searchkey);
    TRACE("ParamsReader::getParameter <--");
    return getNextParameter();
}


//------------------------------------------------------------------------------
//  TString* getNextParameter(char* value)
//------------------------------------------------------------------------------
TString ParamsReader::getNextParameter()
{
    TRACE("ParamsReader::getNextParameter -->");
    TString result;
    int index = findKey();
    if (index >= 0)
    {
        result = token_list.at(index);
        result.pop_front();
        vectorindex = (uli) index + 1;
    }
    TRACE("ParamsReader::getNextParameter <--");
    return result;
}


// Private Function(s) definitions
//------------------------------------------------------------------------------
// int LogManager::findKey(char* key)
//------------------------------------------------------------------------------
int ParamsReader::findKey()
{
    TRACE("ParamsReader::findKey -->");
    int index = -1;
    for (uli counter = vectorindex; counter < token_list.size() && index < 0 ;
         ++counter)
    {
        if (token_list.at(counter).front() == searchkey)
        {
            index = (uli) counter;
        }
    }
    TRACE("ParamsReader::findKey <--");
    return index;
}


//------------------------------------------------------------------------------
//  bool ParamsReader::readParameters()
//------------------------------------------------------------------------------
void ParamsReader::readParameters()
{
    TRACE("ParamsReader::readParameters -->");
    TString t;
    for (bool tokenRead = file_reader->firstLine(t); tokenRead ;
         tokenRead = file_reader->nextLine(t))
    {
        token_list.push_back(t);
        t.clear();
    }
    TRACE("ParamsReader::readParameters <--");
}
