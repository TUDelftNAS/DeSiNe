/******************************************************************************

    source file TString.cpp for class TString

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/



// Include(s)
#include "Utils/TString.h"
#include <string>
using std::string;


//------------------------------------------------------------------------------
//  constructor TString()
//------------------------------------------------------------------------------
TString::TString()
{
    // Empty
}


//------------------------------------------------------------------------------
//  destructor ~TString()
//  Destructs TString
//  Input :
//  Output:
//------------------------------------------------------------------------------
TString::~TString()
{
    // Empty
}


//------------------------------------------------------------------------------
// void print()
//------------------------------------------------------------------------------
void TString::print(ostream &buffer) const
{
    for (TypeTString::const_iterator iter = tokenstream.begin();
        iter != tokenstream.end(); ++iter)
    {
        buffer << (*iter) << ' ';
    }
}

//------------------------------------------------------------------------------
// char* pop_front()
//------------------------------------------------------------------------------
string TString::pop_front()
{
    string result = tokenstream.front();
    if (!tokenstream.empty())
    {
        tokenstream.pop_front();
    }
    return result;
}
