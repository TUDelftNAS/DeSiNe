/******************************************************************************

	source file IgorTextLog.cpp for class: IgorTextLog

	Author : T. Kleiberg
	Version: 1
	Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/IgorTextLog.h"
#include "IO/WaveSet.h"
#include "Utils/Types.h"
#include <fstream>
#include <sstream>
#include <string>
using std::endl;
using std::ofstream;
using std::string;
using Types::uli;

//------------------------------------------------------------------------------
//  constructor IgorTextLog()
//------------------------------------------------------------------------------
IgorTextLog::IgorTextLog(const string &name, const string &path)
	: AbstractTextLog(name, path)
{
	TRACE("IgorTextLog::IgorTextLog -->");
	txtname = path + "/" + name + ".txt";
	TRACE("IgorTextLog::IgorTextLog <--");
}

//------------------------------------------------------------------------------
//  destructor ~IgorTextLog()
//------------------------------------------------------------------------------
IgorTextLog::~IgorTextLog()
{
	TRACE("IgorTextLog::~IgorTextLog -->");
	if (txtbuffer.is_open()) close();
	TRACE("IgorTextLog::~IgorTextLog <--");
}


//------------------------------------------------------------------------------
//  void append();
//------------------------------------------------------------------------------
void IgorTextLog::close()
{
	TRACE("IgorTextLog::close -->");

	// Write names
	print(txtbuffer, stringSet, -1);
	print(txtbuffer, doubleSet, -1);
	print(txtbuffer, longSet, -1);
	print(txtbuffer, uliSet, -1);
	txtbuffer << endl;

	// Write values until no ..Set contains anymore values (index out of range)
	bool indexInRange = true;
	for(long index = 0; indexInRange ;++index)
	{
		indexInRange =  print(txtbuffer, stringSet, index);
		indexInRange |= print(txtbuffer, doubleSet, index);
		indexInRange |= print(txtbuffer, longSet, index);
		indexInRange |= print(txtbuffer, uliSet, index);
		if (indexInRange) txtbuffer << endl;
	}
	txtbuffer.close();
	TRACE("IgorTextLog::close <--");
}


//------------------------------------------------------------------------------
//  void append();
//------------------------------------------------------------------------------
void IgorTextLog::open()
{
	TRACE("IgorTextLog::open -->");
	// All writing is done in close(). This is done because not all
	// waves are known at this point yet
	txtbuffer.open(txtname.c_str(), ofstream::out | ofstream::trunc);

	TRACE("IgorTextLog::open <--");
}


//------------------------------------------------------------------------------
//  void print();
//------------------------------------------------------------------------------
template <typename T>
bool IgorTextLog::print(ostream &buffer, const vector<T>& ws, const long &index) const
{
	typedef typename vector<T>::const_iterator VWSIterator;
	typedef typename T::Iterator WaveIter;

	// Iterate through vector of wave sets
	std::stringstream tmpbuf;
	for(VWSIterator iter1 = ws.begin(); iter1 != ws.end(); ++iter1)
	{
		// Iterate though waves in a wave set
		for (WaveIter iter2 = iter1->getWaves(); iter2(); ++iter2)
		{
			// Check if names must be written
			if (index < 0) // index < 0 -> print names as header line
			{
				tmpbuf
				<< (tmpbuf.str().empty() ? "" : "\t")
				<< fixformat(iter1->getName())
				<< (iter1->getName().length() ? "_" : "")
				<< fixformat(iter2.getName());
			} else
			if ((uli) index  < iter2.getWaveVector().size())
			{
				tmpbuf
				<< (tmpbuf.str().empty() ? "" : "\t")
				<< iter2.getWaveVector()[index];
			}
		}
	}
	if (!tmpbuf.str().empty())
	{
		buffer << tmpbuf.str();
	}
	return (!tmpbuf.str().empty());
}
