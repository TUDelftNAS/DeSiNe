#ifndef TSTRING_H
#define TSTRING_H
/******************************************************************************

    header file TString.h for utility library TString.

    This is a class for containing tokenized Strings

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include <deque>
#include <string>
#include <ostream>
using std::deque;
using std::string;
using std::ostream;


class TString
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
    typedef deque<string> TypeTString;
    TypeTString tokenstream;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor TString()
//  Constructs empty TString.
//  Input :
//  Output:
//------------------------------------------------------------------------------
    TString();


//------------------------------------------------------------------------------
//  destructor ~TString()
//  Destructs TString
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~TString();


//------------------------------------------------------------------------------
// string at(int position)
//
// Returns element at position 'position'.
//
//------------------------------------------------------------------------------
    string at(const unsigned int &position) const
    {
        return tokenstream.at(position);
    }


//------------------------------------------------------------------------------
// void clear()
//
// clear the stream
//
//------------------------------------------------------------------------------
    void clear()
    {
        tokenstream.clear();
    }


//------------------------------------------------------------------------------
// bool empty()
//
// Test if stream is empty
//
//------------------------------------------------------------------------------
    bool empty() const
    {
        return tokenstream.empty();
    }


//------------------------------------------------------------------------------
// string front()
//
// Returns reference to first element
//
//------------------------------------------------------------------------------
    string front() const
    {
        return (tokenstream.empty() ? "" : tokenstream.front());
    }


//------------------------------------------------------------------------------
// char* pop_front()
//
// Pops the first element of the stream and returns it reference
//
//------------------------------------------------------------------------------
    string pop_front();


//------------------------------------------------------------------------------
// int size()
//
// Returns number of alements in the stream
//
//------------------------------------------------------------------------------
    unsigned int size() const
    {
        return tokenstream.size();
    }

//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints contents to a buffer
//  Input : the buffer
//------------------------------------------------------------------------------
	void print(ostream &buffer) const;


//------------------------------------------------------------------------------
//  void push_back(char* token)
//
//  Add a new token at the end of the stream
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void push_back(const string &token)
    {
        tokenstream.push_back(token);
    }


//------------------------------------------------------------------------------
//  bool operator==
//
//  Compares TString object
//------------------------------------------------------------------------------
    bool operator==(const TString &s1)
    {
        return (s1.tokenstream==tokenstream);
    }
}; //end declarations TString
#endif //TSTRING_H
