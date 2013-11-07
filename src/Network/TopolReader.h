#ifndef TOPOLREADER_H
#define TOPOLREADER_H
/******************************************************************************

    header file TopolReader.h for class: TopolReader

    This class is meant to read the topology from a file using FileReader.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "IO/FileReader.h"
#include "Utils/Utils.h"
#include "Utils/Types.h"
#include <list>
#include <string>
using std::list;
using std::string;
using Types::IntVector;
using Types::DblVector;


class TopolReader
{
    // Constanst(s)

    // Variable(s)
    private:
    FileReader* file_reader;
    int input_type;
    int number_of_nodes;
    int number_of_qos;
    bool is_directed;
    IntVector edge_nodes;
    IntVector src;
    IntVector dest;
    DblVector reqc;
	IntVector cost;

    typedef list<DblVector> DblVectorList;
    DblVectorList link_values;
    DblVectorList::const_iterator link_iter; // used for traversing link values

//  double** link_values;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor TopolReader();
//
//  Constructs TopolReader.
//  Input : input_file_name of the topolgy file
//  Output:
//
//------------------------------------------------------------------------------
    TopolReader(const string input_file_name);


//------------------------------------------------------------------------------
//
//  destructor ~TopolReader()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~TopolReader();


//------------------------------------------------------------------------------
//
//  int getNumNodes();
//
//  Returns the number of nodes in the network
//  Input :
//  Output:
//      - : the number of nodes
//
//------------------------------------------------------------------------------
    int getNumNodes() const;


//------------------------------------------------------------------------------
//
//  bool isDirected();
//
//  Returns directedness
//
//------------------------------------------------------------------------------
    bool isDirected() const;

//------------------------------------------------------------------------------
//
//  int getInputType();
//
//  Returns the type of input for topology / traffix matrix
//  Input :
//  Output:
//      - : the type of input
//
//------------------------------------------------------------------------------
    int getInputType();
//------------------------------------------------------------------------------
//
//  int getNumQos();
//
//  Returns the number of QoS comstraints defined in the topology
//  Input :
//  Output:
//      - : the number of QoS constraints
//
//------------------------------------------------------------------------------
    int getNumQos() const;


//------------------------------------------------------------------------------
//
//  IntVector* getEdgeNodes();
//
//  Returns array of edge nodes in the network
//  Input :
//  Output:
//      - : (newly allocated) IntVector* with nodes
//
//------------------------------------------------------------------------------
    IntVector& getEdgeNodes();

	IntVector& getFlowSrc();
	
	IntVector& getFlowDest();
	
	DblVector& getFlowReqc();
	IntVector& getAssignedCost();

//------------------------------------------------------------------------------
//
//  DblVector* getFirstLink();
//
//  Returns an array with the values for the first link
//  Input :
//  Output:
//      - : (newly allocated) linkstate values
//
//------------------------------------------------------------------------------
    DblVector getFirstLink();

//------------------------------------------------------------------------------
//
//  DblVector* getNextLink();
//
//  Returns an array with the values for the next link. Returns 0 if
//  no more links
//  Input :
//  Output:
//      - : the linkstate values
//
//------------------------------------------------------------------------------
    DblVector getNextLink();


    private:
//------------------------------------------------------------------------------
//
//  void readNextWord(char* src, char* dest)
//
//  Reads first word from a line into a buffer.
//  Input :
//      src : the source, is truncated after use
//  Output:
//      dest : the buffer to which the word is written
//------------------------------------------------------------------------------
//  void readNextWord(char* src, char* dest);


//------------------------------------------------------------------------------
//
//  void readTopology();
//
//  Reads topology from the file. Invoked by comntructor.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    void readTopology();

}; //end declarations
#endif //TOPOLREADER_H
