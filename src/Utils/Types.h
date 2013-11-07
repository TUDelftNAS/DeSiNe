#ifndef TYPEDEFSER_H
#define TYPEDEFSER_H
/******************************************************************************

    header file Typedefser.h for class: Typedefser

    This class contsins basic typedef declarations

    Author : T. Kleiberg
    Version: 1
    Date   : August 2004

******************************************************************************/


// Include(s)
#include "Utils/DistributedVariable.h"
#include "Utils/SimpleVariable.h"
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <string>
using std::vector;
using std::set;
using std::map;
using std::string;
using std::deque;

namespace Types
{

    // Typedef(s)
    typedef unsigned short int usi;
    typedef unsigned long int uli;
    typedef unsigned long long ull;
    typedef long double ldouble;

    typedef DistributedVariable<usi> DVusi;
    typedef DistributedVariable<uli> DVuli;
    typedef DistributedVariable<ull> DVull;
    typedef DistributedVariable<double> DVdouble;

    typedef SimpleVariable<usi> SVusi;
    typedef SimpleVariable<uli> SVuli;
    typedef SimpleVariable<ull> SVull;
    typedef SimpleVariable<double> SVdouble;

    typedef set<int> IntSet;
    typedef map<usi, double> UsiDblMap;
    typedef map<int, double> IntDblMap;
    typedef map<int, ull> IntUllMap;

    typedef vector<double> DblVector;
    typedef vector<int> IntVector;
    typedef vector<usi> UsiVector;
    typedef vector<uli> UliVector;
    typedef vector<ull> UllVector;
    typedef vector<string> StringVector;

    typedef vector<DblVector> DblMatrix;

    typedef map<int, DVull> IntDUullMap;

	typedef deque<string> TString;
} // end: namespace Types
#endif //TYPEDEFSER_H
