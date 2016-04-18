/******************************************************************************

    source file FileReader.cpp for class: FileReader

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "IO/FileReader.h"
#include "IO/Tag.h"
#include "Utils/TraceManager.h"
#include "Utils/Utils.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using std::string;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor FileReader::FileReader(char* input)
//------------------------------------------------------------------------------
FileReader::FileReader(const std::string input_file_name)
{
    TRACE("FileReader::FileReader -->");
    TRACE("Opening file for reading: " << input_file_name);

	// open input file
	std::ifstream file(input_file_name.c_str());

	// file opened?
	if (!file)
	{
		std::cout << "Can't open input file: \"" << input_file_name
			<<"\"" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream filestring;
	// copy file contents to cout
	char c;
	while (file.get(c))
	{
		filestring.put(c);
	}
	tokenize_string(filestring.str(), tokens, "\n");

    TRACE("FileReader::FileReader <--");
}


//------------------------------------------------------------------------------
//  destructor FileReader::~FileReader()
//------------------------------------------------------------------------------
FileReader::~FileReader()
{
    TRACE("FileReader::~FileReader -->");
    //delete input_file;
    TRACE("FileReader::~FileReader <--");
}


//------------------------------------------------------------------------------
//  bool FileReader::firstLine()
//------------------------------------------------------------------------------
bool FileReader::firstLine(TString &output)
{
    TRACE("FileReader::firstLine -->");

    index = 0;
    bool result = nextLine(output);
    TRACE("FileReader::firstLine <--");
    return result;
}


//------------------------------------------------------------------------------
//  bool FileReader::nextLine()
//------------------------------------------------------------------------------
bool FileReader::nextLine(TString &output)
{
    TRACE("FileReader::nextLine -->");

    for(output.clear(); index < tokens.size() && output.empty(); ++index)
    {
		output.clear();
		tokenize_string(
			tokens.at(index).substr(0,tokens.at(index).find('#')),
			output,
			" \t");
	} // end while
	TRACE("FileReader::nextLine <--");
	return (!output.empty());
}
