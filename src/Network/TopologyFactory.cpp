/******************************************************************************

    source file TopologyFactory.cpp for class: TopologyFactory

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2006

******************************************************************************/


// Include(s)
#include "Network/TopologyFactory.h"
#include "IO/FileReader.h"
#include "IO/Tag.h"
#include "Utils/TraceManager.h"
#include <deque>
#include <set>
#include <string>
#include <cmath>
using std::deque;
using std::string;
using Types::uli;
using Types::DblVector;

// Implementations of Topology generators
#include "Network/TopologyFactoryAdjacency.cpp"
#include "Network/TopologyFactoryBarabasi.cpp"
#include "Network/TopologyFactoryErdos.cpp"
#include "Network/TopologyFactoryFile.cpp"
#include "Network/TopologyFactoryFull.cpp"
#include "Network/TopologyFactoryGrid.cpp"
#include "Network/TopologyFactoryRandom.cpp"


// Constanst(s)
const double TopologyFactory::default_capacity = 1.0;

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor TopologyFactory::TopologyFactory()
//------------------------------------------------------------------------------
TopologyFactory::TopologyFactory(RandomVar* link_capacity) :
    link_capacity(link_capacity)
{
  	TRACE("TopologyFactory::TopologyFactory -->");
    rng = RandomNumberGenerator::getRandomNumberGenerator();
  	TRACE("TopologyFactory::TopologyFactory <--");
}


//------------------------------------------------------------------------------
//  destructor TopologyFactory::~TopologyFactory()
//------------------------------------------------------------------------------
TopologyFactory::~TopologyFactory()
{
	TRACE("TopologyFactory::~TopologyFactory -->");
    //Empty
	TRACE("TopologyFactory::~TopologyFactory <--");
}


//------------------------------------------------------------------------------
//  Topology* create();
//------------------------------------------------------------------------------
Topology* TopologyFactory::create(const TString &description)
{
	TRACE("TopologyFactory::create -->");
    //description.print(*TraceManager::getStream());
    //TRACE(' ');

    Topology* result = (Topology*) 0;
    if (description.front() == Tag::TOP_ADJACENCY)
    {
        result = createTopologyAdjacency(description);
    } else
    if (description.front() == Tag::TOP_BARABASI)
    {
        result = createTopologyBarabasi(description);
    } else
    if (description.front() == Tag::TOP_ERDOS)
    {
        result = createTopologyErdos(description);
    } else
    if (description.front() == Tag::TOP_FILE)
    {
        result = createTopologyFile(description);
    } else
    if (description.front() == Tag::TOP_FULL)
    {
        result = createTopologyFull(description);
    } else
    if (description.front() == Tag::TOP_GRID2D)
    {
        result = createTopologyGrid2D(description);
    } else
    if (description.front() == Tag::TOP_RANDOM)
    {
        result = createTopologyRandom(description);
    }
    else
    {
        // No matching topology could be found....
        ERROR("Unknown description: " << description.front());
        exit(-1);
    }

	TRACE("TopologyFactory::create <--");
    return result;
}

//------------------------------------------------------------------------------
//  void build(const NodePairDeque &nodepairs, Topology* topology)
//------------------------------------------------------------------------------
void TopologyFactory::build(const NodePairDeque &nodepairs, Topology* topology)
{
    TRACE("TopologyFactory::build -->");
    for(NodePairDeque::const_iterator iter = nodepairs.begin();
        iter != nodepairs.end(); ++iter)
    {
		if (iter->source != iter->destination)
		{
	        double link_cap = link_capacity == (RandomVar*) 0 ?
	            default_capacity : link_capacity->generate();
	        DblVector d;
	        d.push_back(iter->source);             // source
	        d.push_back(iter->destination);        // dest
	        d.push_back(0.0);                      // core
	        d.push_back(link_cap); // cap
	        topology->link_list->insert(d);
	        if (!topology->is_directed)
	        {
	            DblVector d2;
	            d2.push_back(iter->destination);  // source
	            d2.push_back(iter->source);       // dest
	            d2.push_back(0.0);                // core
	            d2.push_back(link_cap); // cap
	            topology->link_list->insert(d2);
	        } //end: if (!topology->is_directed)
		} //end: if (iter->source != iter->destination)
    }
    TRACE("TopologyFactory::build <--");
}
