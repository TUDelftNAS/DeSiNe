#ifndef UTILS_H
#define UTILS_H
/******************************************************************************

    header file Utils.h for utility library Utils.

    This is a special library object that contains generic utility functions
    suchs as memory allocation functions and common structures.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include <ostream>
#include <deque>
#include <string>
#include <sstream>
using std::deque;
using std::string;
using std::ostream;

//------------------------------------------------------------------------------
//  void**  allocMatrix(int rows, int columns, size_t nBy)
//
// Allocate a matrix of size (rows * columns).
//
//------------------------------------------------------------------------------
void**  allocMatrix(int rows, int columns, size_t nBy);


//------------------------------------------------------------------------------
//  void  freeMatrix(void **buff, int rows)
//
// Deallocate a matrix with 'rows' rows.
//
//------------------------------------------------------------------------------
void  freeMatrix(void **buff, int rows);


//------------------------------------------------------------------------------
//  void getCurrentTime(ostream &buffer)
//
//  Reads current time into a buffer
//  Input : the buffer into which the time is written
//  Output:
//------------------------------------------------------------------------------
void getCurrentTime(ostream &buffer);


// tokenize string
void tokenize_string(const std::string &str,
	std::deque<std::string> &tokens,
	const std::string &delimiters=" ");

//------------------------------------------------------------------------------
//
//  roundn(const double &val, <dec>)
//
//  rounds to <dec> decimals
//------------------------------------------------------------------------------
double roundn(const double &val, const unsigned short &dec);

//------------------------------------------------------------------------------
//
//  string ToString(const T& val)
//
//  Converts type to a string
//------------------------------------------------------------------------------
template<typename T>
string typeToString(const T& val)
{
    std::stringstream strm;
    strm << val;
    return strm.str();
}
#endif //UTILS_H
