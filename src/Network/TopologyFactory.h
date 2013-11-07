#ifndef TOPOLOGYFACTORY_H
#define TOPOLOGYFACTORY_H
/******************************************************************************

    header file TopologyFactory.h for class: TopologyFactory

    This class is a factory for creating Topology objects. It follows the
    concrete factory design pattern. The arguments that define the topology
    to be built, are passed on as a string. The Factory then parses the string
    and constructs the object likewise.

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2006

******************************************************************************/


// Include(s)
#include "Network/Topology.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/Types.h"
using Types::TString;
using Types::IntVector;

class TopologyFactory
{
    // Struct(s)
    private:
    typedef struct
    {
        int source;
        int destination;
    } NodePair;
    typedef deque<NodePair> NodePairDeque;

    // Constanst(s)
    const static double default_capacity;

    // Variable(s)
    RandomNumberGenerator* rng;
    NodePairDeque pairs;
    IntVector edge_nodes;
    RandomVar* link_capacity;
    TString last_description;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor TopologyFactory();
//
//  Constructs TopologyFactory. If link_capacity is omitted, unit capacity
//  is used.
//
//------------------------------------------------------------------------------
    TopologyFactory(RandomVar* link_capacity = (RandomVar*) 0);


//------------------------------------------------------------------------------
//
//  destructor ~TopologyFactory()
//
//------------------------------------------------------------------------------
    ~TopologyFactory();


//------------------------------------------------------------------------------
//  Topology* create(TString* description);
//  Creates the new Topology
//  Input : the description of for the new topology
//  Output:
//      - : the new topology
//------------------------------------------------------------------------------
    Topology* create(const TString &description);


    private:
//------------------------------------------------------------------------------
//  void build(const NodePairDeque &nodepairs, Topology* topology);
//  Creates the new Topology from the nodepairs.
//------------------------------------------------------------------------------
    void build(const NodePairDeque &nodepairs, Topology* topology);

//------------------------------------------------------------------------------
//  Topology* createTopologyAdjacency(description);
//  Creates the new Topology from a adjacency file.
//  Input : the description of for the new topology:
//  description = "File","<filename>"
//------------------------------------------------------------------------------
    Topology* createTopologyAdjacency(const TString &description);


//------------------------------------------------------------------------------
//  Topology* createTopologyBarabasi(description);
//  Creates the new Topology using Barabasi-Albert power-law graph with N nodes,
//  a core of m0 nodes and m links per new node. If m is omitted or m=0 then m=m0
//  Graph is ALWAYS undirected.
//  Input : the description of for the new topology:
//  description = "Barabasi","<nodes>","<m0>","[<m>]"
//------------------------------------------------------------------------------
    Topology* createTopologyBarabasi(const TString &description);

//------------------------------------------------------------------------------
//  Topology* createTopologyFile(description);
//  Creates the new Topology using Erdos-Renyi model Gp(N)
//  Input : the description of for the new topology:
//  description = "Erdos","<nodes>","<probability>","[<directed>]"
//    when <directed> is omitted, the topology is undirected.
//------------------------------------------------------------------------------
    Topology* createTopologyErdos(const TString &description);

//------------------------------------------------------------------------------
//  Topology* createTopologyFile(description);
//  Creates the new Topology from a file.
//  Input : the description of for the new topology:
//  description = "File","<filename>"
//------------------------------------------------------------------------------
    Topology* createTopologyFile(const TString &description);

//------------------------------------------------------------------------------
//  Topology* createTopologyFull(description);
//  Creates the new Full-Mesh Topology, K_N
//  Input : the description of for the new topology:
//  description = "Full","<nodes>","[<directed>]"
//    when <directed> is omitted, the topology is undirected.
//------------------------------------------------------------------------------
    Topology* createTopologyFull(const TString &description);

//------------------------------------------------------------------------------
//  Topology* createTopologyGrid2D(description);
//  Creates the new Topology in form a 2-Dimensional grid.
//  Input : the description of for the new topology:
//  description = "Grid2D","<rows>","<columns>","[<directed>]"
//    when <directed> is omitted, the topology is undirected.
//------------------------------------------------------------------------------
    Topology* createTopologyGrid2D(const TString &description);

//------------------------------------------------------------------------------
//  Topology* createTopologyFile(description);
//  Creates the new Topology using random graph model G(N,L)
//  Input : the description of for the new topology:
//  description = "Random","<nodes>","<links>","[<directed>]"
//    when <directed> is omitted, the topology is undirected.
//------------------------------------------------------------------------------
    Topology* createTopologyRandom(const TString &description);

}; //end declarations
#endif //TOPOLOGYFACTORY_H
