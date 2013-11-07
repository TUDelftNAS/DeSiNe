/******************************************************************************

    source file TopolReader.cpp for class: TopolReader

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "IO/FileReader.h"
#include "IO/Tag.h"
#include "Network/TopolReader.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
using Types::IntVector;
using Types::DblVector;



// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor TopolReader::TopolReader(char* input)
//------------------------------------------------------------------------------
TopolReader::TopolReader(const string input_file_name)
{
    TRACE("TopolReader::TopolReader -->");
    file_reader = new FileReader(input_file_name);
    if (file_reader == (FileReader*) 0)
    {
        ERROR("Problem opening file: " << input_file_name);
    }
    is_directed = false;
    readTopology();
    TRACE("TopolReader::TopolReader <--");
}


//------------------------------------------------------------------------------
//  destructor TopolReader::~TopolReader()
//------------------------------------------------------------------------------
TopolReader::~TopolReader()
{
    TRACE("TopolReader::~TopolReader -->");
    if (file_reader) delete file_reader;
    TRACE("TopolReader::~TopolReader <--");
}


//------------------------------------------------------------------------------
//  int getNumNodes();
//------------------------------------------------------------------------------
int TopolReader::getNumNodes() const
{
    TRACE("TopolReader::getNumNodes -->");
    TRACE("TopolReader::getNumNodes <--");
    return number_of_nodes;
}


//------------------------------------------------------------------------------
//  int getNumNodes();
//------------------------------------------------------------------------------
bool TopolReader::isDirected() const
{
    TRACE("TopolReader::isDirected -->");
    TRACE("TopolReader::isDirected <--");
    return is_directed;
}

//------------------------------------------------------------------------------
//  int getInputType();
//------------------------------------------------------------------------------
int TopolReader::getInputType()
{
    TRACE("TopolReader::getInputType -->");
    TRACE("TopolReader::getInputType <--");
    return input_type;
}

//------------------------------------------------------------------------------
//  int getNumNodes();
//------------------------------------------------------------------------------
int TopolReader::getNumQos() const
{
    TRACE("TopolReader::getNumQos -->");
    TRACE("TopolReader::getNumQos <--");
    return number_of_qos;
}


//------------------------------------------------------------------------------
//  int getEdgeNodes();
//------------------------------------------------------------------------------
IntVector& TopolReader::getEdgeNodes()
{
    TRACE("TopolReader::getEdgeNodes -->");
    TRACE("TopolReader::getEdgeNodes <--");
    return edge_nodes;
}


IntVector& TopolReader::getFlowSrc()
{
    TRACE("TopolReader::getFlowSrc -->");
    TRACE("TopolReader::getFlowSrc <--");
    return src;
}


IntVector& TopolReader::getFlowDest()
{
    TRACE("TopolReader::getFlowDest -->");
    TRACE("TopolReader::getFlowDest <--");
    return dest;
}


DblVector& TopolReader::getFlowReqc()
{
    TRACE("TopolReader::getFlowReqc -->");
    TRACE("TopolReader::getFlowReqc <--");
    return reqc;
}
IntVector& TopolReader::getAssignedCost()
{
    TRACE("TopolReader::getAssignedCost -->");
    TRACE("TopolReader::getAssignedCost <--");
    return cost;
}
//------------------------------------------------------------------------------
//  DblVector* getFirstLink();
//------------------------------------------------------------------------------
DblVector TopolReader::getFirstLink()
{
    TRACE("TopolReader::getFirstLink -->");
    link_iter = link_values.begin();
    TRACE("TopolReader::getFirstLink <--");
    return getNextLink();
}


//------------------------------------------------------------------------------
//  DblVector* getNextLink();
//------------------------------------------------------------------------------
DblVector TopolReader::getNextLink()
{
    TRACE("TopolReader::getNextLink -->");
    DblVector result;
    if (link_iter != link_values.end())
    {
        result = *link_iter;
        ++link_iter;
    }
    TRACE("TopolReader::getNextLink <--");
    return result;
}


//------------------------------------------------------------------------------
//  void readTopology();
//------------------------------------------------------------------------------
void TopolReader::readTopology()
{
    TRACE("TopolReader::readTopology -->");

	{
	    TString line;
	    int number_of_edgenodes;

		input_type = 0; // default topology type is 0, in case previous users use the
						// old topology format

	    // read #nodes, #edgenodex, #qos
	    file_reader->firstLine(line);

	    number_of_nodes     = atoi(line.at(0).c_str());
	    number_of_edgenodes = atoi(line.at(1).c_str());
	    number_of_qos       = atoi(line.at(2).c_str());
	    if (line.size() > 3)
	    {
	    	input_type = atoi(line.at(3).c_str());
	    }
	    if (line.size() > 4)
	    {
	        is_directed = (bool) atoi(line.at(4).c_str());
	    }

	    // read edgenodes list
	    if (number_of_edgenodes > 0)
	    {
	        file_reader->nextLine(line);
	        for(std::size_t index=0;index<line.size();++index)
	        {
	            edge_nodes.push_back(atoi(line.at(index).c_str() ));
	        }
	    }
	}

    // read links and traffic matrix
    for (TString line; file_reader->nextLine(line); )
    {
       	if (line.size() == 3) // traffic matrix
    	{
    		src.push_back(atoi(line.at(0).c_str()));
			dest.push_back(atoi(line.at(1).c_str()));
			reqc.push_back(atof(line.at(2).c_str()));
        } // line,size == 3
        else
        {	// length = #values per link, i.e. src, dst, cost, capacity & #qos
        	DblVector link;
        	link.push_back(atof(line.at(0).c_str() ));	// src
        	link.push_back(atof(line.at(1).c_str() ));	// dst
   			cost.push_back(atoi(line.at(2).c_str() ));	// cost
			link.push_back(0.0);						// core

			for(std::size_t index= 3; index < line.size(); ++index)
			{
				link.push_back(atof( line.at(index).c_str() ));
			}
        	link_values.push_back(link);
        } // line.size != 3
    }
    TRACE("TopolReader::readTopology <--");
}
