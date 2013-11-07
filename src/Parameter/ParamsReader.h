#ifndef PARAMSREADER_H
#define PARAMSREADER_H
/******************************************************************************

    header file ParamsReader.h for class: ParamsReader

	This class is meant to read the parameters from a file using FileReader
	and store them in a vector. The key-value pairs can be obtained through
	their TAG (see Tag.h)

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "IO/FileReader.h"
#include "Utils/Types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using Types::uli;
using Types::TString;

class ParamsReader
{
    // Constanst(s)

    // Variable(s)
	private:
   	typedef vector<TString> TokenList;
    TokenList token_list;
    FileReader* file_reader;
    uli vectorindex;  // used for multiple occurances of keys in the vector
    string searchkey;  // used for multiple occurances of keys in the vector

    // Function(s) declarations
 	public:
//------------------------------------------------------------------------------
//
//  constructor ParamsReader();
//
//  Constructs ParamsReader.
//  Input : parameter_file of the parameter file
//  Output:
//
//------------------------------------------------------------------------------
    ParamsReader(const string parameter_file);


//------------------------------------------------------------------------------
//
//  destructor ~ParamsReader()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~ParamsReader();


//------------------------------------------------------------------------------
//
//  TString* getParameter(const string key);
//
//  Returns the value matched with first occurance of 'key'. A newly allocated
//  TString is returned!!
//  Input :
//		key : the key of the Parameter (see Tag.h for all keys)
//  Output:
//      - : the value mapped with 'key', or 0 otherwise
//
//------------------------------------------------------------------------------
    TString getParameter(const string key);

//------------------------------------------------------------------------------
//
//  TString* getNextParameter(char* value);
//
//  Returns the value matched with next occurance of key last used for
//  getParameter. A newly allocated TString is returned!!
//  Input :
//  Output:
//      - : the value mapped with 'key', or 0 otherwise
//
//------------------------------------------------------------------------------
	TString getNextParameter();


	private:
//------------------------------------------------------------------------------
//
// Find index of a key/value pair
//
//------------------------------------------------------------------------------
	int findKey();

//------------------------------------------------------------------------------
//
//  void readParameters();
//
//  Reads parameters from the file. Invoked by comntructor.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    void readParameters();
}; //end declarations
#endif //PARAMSREADER_H
