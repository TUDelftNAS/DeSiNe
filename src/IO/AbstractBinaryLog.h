#ifndef ABSTRACTBINARYLOG_H
#define ABSTRACTBINARYLOG_H
/******************************************************************************

    header file AbstractBinaryLog.h for class: AbstractBinaryLog

    This class is the abstract base class for all binary log files

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "IO/AbstractLog.h"
#include "Utils/TraceManager.h"
#include <string>
using std::string;


class AbstractBinaryLog : public AbstractLog
{
    // Friends

    // Constanst(s)
    private:
    static const bool WRITE_LSB_FIRST = false; // Least Significant Byte first??

    // Variable(s)
    private:
    bool convertByteOrder;

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//  constructor AbstractBinaryLog()
//  Constructs AbstractBinaryLog
//  Input :
//------------------------------------------------------------------------------
    AbstractBinaryLog(const string &name, const string &path)
        : AbstractLog(name, path)
    {
        TRACE("AbstractBinaryLog::AbstractBinaryLog -->");
    	char swapTest[2] = { 1, 0 };
    	bool littleEndianSystem = false;
    	if( *(short*) swapTest == 1 ) //little endian => LSB first
    	{
       		littleEndianSystem = true;
    	}
   	convertByteOrder = (littleEndianSystem != WRITE_LSB_FIRST);
        TRACE("AbstractBinaryLog::AbstractBinaryLog <--");
    }


    public:
//------------------------------------------------------------------------------
//  destructor ~AbstractBinaryLog()
//  Destructs AbstractBinaryLog
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~AbstractBinaryLog()
    {
        TRACE("AbstractBinaryLog::~AbstractBinaryLog -->");
        //Empty!!
        TRACE("AbstractBinaryLog::~AbstractBinaryLog <--");
    }


    protected:
//------------------------------------------------------------------------------
//  convertTypeEndian(T const& x)
//  This function is used for converting between different Endian procs
//------------------------------------------------------------------------------
	template <typename T> union type2char 
	{
		T y;
		unsigned char b[sizeof(T)];
	};

	template <typename T>
	T convertTypeEndian(T x) const
	{
        if (convertByteOrder)
        {
			type2char<T> dat1, dat2;
        	dat1.y = x;
        	for (size_t i = 0; i < sizeof(T); ++i)
        	{
        		dat2.b[i] = dat1.b[sizeof(T)-i-1];
        	}
        	return dat2.y;
        }
        return x;
    }

}; //end declarations AbstractBinaryLog
#endif // ABSTRACTBINARYLOG_H
