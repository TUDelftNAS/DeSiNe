/******************************************************************************

    source file Utils.cpp for library Utils

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Utils/Utils.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  void**  allocMatrix(int rows, int columns, size_t nBy)
//------------------------------------------------------------------------------
void**  allocMatrix(int rows, int columns, size_t nBy)
{
    void** buff = (void**) calloc (rows, sizeof(void*));

    if (buff == NULL)
    {
        fprintf ( stderr,
            "Alloc-ERR: Can't allocate matrix for %dBy sized tokens [%d]x[%d]\n",
            nBy, rows, columns);
        return NULL;
    }

    for (int i=0; i<rows; ++i)
    {
        buff[i] = (void*) calloc (columns, nBy);
        if (buff[i] == NULL)
        {
            fprintf (stderr,
            "Alloc-ERR: Can't allocate matrix for %dBy sized tokens [%d]x[%d]\n",
            nBy, rows, columns);
            for (int j=0; j<i; ++j)
            {
                free (buff[j]);
            }
            free (buff);
            return NULL;
        }
    }
    return (void**) buff;
}


//------------------------------------------------------------------------------
//  void  freeMatrix(void **buff, int rows)
//------------------------------------------------------------------------------
void  freeMatrix(void **buff, int rows)
{
	for (int i=0; i<rows; ++i)
	{
		free (buff[i]);
    }
	free (buff);
}


// Local Function(s) definitions
//------------------------------------------------------------------------------
//  void getCurrentTime(ostream &buffer)
//------------------------------------------------------------------------------
void getCurrentTime(ostream &buffer)
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    buffer << asctime(timeinfo);
}


//------------------------------------------------------------------------------
//  roundn(const double& val, const unsigned short dec)
//------------------------------------------------------------------------------
double roundn(const double &val, const unsigned short &dec)
{
    return pow(10.0,-dec) * round(val * pow(10.0, dec) );
}


void tokenize_string(const std::string &str,
	std::deque<std::string> &tokens,
	const std::string &delimiters)
{
	tokens.clear();
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first "non-delimiter".
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}
