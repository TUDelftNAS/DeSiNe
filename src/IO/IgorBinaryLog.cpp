/******************************************************************************

    source file IgorBinaryLog.cpp for class: IgorBinaryLog

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "IO/IgorBinaryLog.h"
#include "IO/WaveSet.h"
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
using std::endl;
using std::ofstream;
using std::string;

//------------------------------------------------------------------------------
//  constructor IgorBinaryLog()
//------------------------------------------------------------------------------
IgorBinaryLog::IgorBinaryLog(const string &name, const string &path)
    : AbstractBinaryLog(name, path)
{
    TRACE("IgorBinaryLog::IgorBinaryLog -->");

    ipfname = path + "/" + name + ".ipf";
    binpref = path + "/" + name + "_W_";

    TRACE("IgorBinaryLog::IgorBinaryLog <--");
}

//------------------------------------------------------------------------------
//  destructor ~IgorBinaryLog()
//------------------------------------------------------------------------------
IgorBinaryLog::~IgorBinaryLog()
{
    TRACE("IgorBinaryLog::~IgorBinaryLog -->");
    if (ipfbuffer.is_open()) close();
    TRACE("IgorBinaryLog::~IgorBinaryLog <--");
}


//------------------------------------------------------------------------------
//  void append();
//------------------------------------------------------------------------------
void IgorBinaryLog::close()
{
    TRACE("IgorBinaryLog::close -->");
    ipfbuffer  << "End" << endl;
    ipfbuffer.close();
    TRACE("IgorBinaryLog::close <--");
}

//------------------------------------------------------------------------------
//  void append();
//------------------------------------------------------------------------------
void IgorBinaryLog::open()
{
    TRACE("IgorBinaryLog::open -->");

    string macroname = fixformat(name);
    ipfbuffer.open(ipfname.c_str(), ofstream::out | ofstream::trunc);
    ipfbuffer  << "#pragma rtGlobals=1"
    << endl    << "Menu \"Macros\""
    << endl    << "\t\"Load " << macroname << "\", Load" << macroname << "()"
    << endl    << "End"
    << endl    << "Macro Load" << macroname << "()"
    << endl;

    TRACE("IgorBinaryLog::open <--");
}



//------------------------------------------------------------------------------
//  void append(const WaveSet<T>& ws);
//------------------------------------------------------------------------------
template <typename T>
void IgorBinaryLog::append(const WaveSet<T>& ws)
{
    TRACE("IgorBinaryLog::append -->");

    const unsigned long max_size = 100000;
    typedef typename WaveSet<T>::Iterator WaveIter;

    // Construct the binary file name
    string binname = binpref + ws.getName() + ".bin";

	// set data type
    string datatype("/T={4,4}");
    if (typeid(T) == typeid(long))
    {
    	datatype = "/T={32,32}";
	} else
    if (typeid(T) == typeid(uli))
    {
    	datatype = "/T={96,96}";
	} else
    if (typeid(T) == typeid(short))
    {
    	datatype = "/T={16,16}";
	} else
    if (typeid(T) == typeid(usi))
    {
    	datatype = "/T={80,80}";
	}


    ipfbuffer
    << "\tGBLoadWave"
    << datatype
    << "/W=" << ws.size() << " \"" << binname << "\"" << endl;

    // Write a binary file, one for all waves in this set
    ofstream buffer(binname.c_str(),
        ofstream::out | ofstream::trunc | ofstream::binary);

	// Split wave into parts of max_size entries to avoid memory problems
    WaveIter iter = ws.getWaves();
    const unsigned long wavesize = iter.getWaveVector().size();
    const unsigned long wix = (unsigned long) std::ceil(
    	(double) wavesize/ (double) max_size);

    for (unsigned long wave_ix = 0; iter();  ++iter, ++wave_ix)
    {
        // Write a line to the IPF file
        ipfbuffer
        << "\tRename wave" << wave_ix << " "
        << fixformat(ws.getName())
        << (ws.getName().length() ?  "_" : "")
        << fixformat(iter.getName())
        << ";" << endl;

	    // Allocate heap space for the memory block that is written to the file
		for (unsigned long ix = 0; ix < wix; ++ix)
		{
			// Get minimum of max_size and remainder
			unsigned long size = (max_size < (wavesize - ix * max_size)) ?
				max_size : wavesize - ix * max_size;
			T heap[size];

	        // Iterate through the wave and convert double if needed
	        for(unsigned long counter = 0; counter < size; ++counter)
	        {
	            heap[counter] = convertTypeEndian<T>(
	            	iter.getWaveVector()[ix * max_size + counter]);
	        }
	        buffer.write((char*) heap, (unsigned long) size * sizeof(T));
		} // end: for
    } // end: for
    buffer.close();

    TRACE("IgorBinaryLog::append <--");
}

