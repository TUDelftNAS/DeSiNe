#ifndef FILEREADER_H
#define FILEREADER_H
/******************************************************************************

    header file FileReader.h for class: FileReader

    This class is used for reading text files. Every line is being read and
    the result is returned as a Token (see token.h) where the first word of
    the line holds the key and the rest the value.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include <string>
#include "Utils/Types.h"
using Types::TString;

class FileReader
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
   	TString tokens;
   	std::size_t index;



    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor FileReader(const string input_file_name)
//  Constructs FileReader with input read from input_file_name.
//  Input :
//      input_file_name : the file read for input
//  Output:
//------------------------------------------------------------------------------
    FileReader(const std::string input_file_name);


//------------------------------------------------------------------------------
//  destructor ~FileReader()
//  Destructs FileReader
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~FileReader();


//------------------------------------------------------------------------------
//  bool firstLine(char* output);
//  Reads the first line from the file.
//  Input :
//  Output:
//      output : the line that is being read
//      - : if a line is found, this is TRUE
//------------------------------------------------------------------------------
    bool firstLine(TString &output);

//------------------------------------------------------------------------------
//  bool nextLine(Token* output);
//  Reads the next line from the file.
//  Input :
//  Output:
//      output : the line that is being read
//      - : if a line is found, this is TRUE
//------------------------------------------------------------------------------
    bool nextLine(TString &output);


}; //end declarations FileReader
#endif // FILEREADER_H
