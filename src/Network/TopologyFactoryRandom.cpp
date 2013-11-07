/******************************************************************************

    source file TopologyFactoryRandom.cpp with implementation of
	createTopologyRandom

    Author : T. Kleiberg
    Version: 1
    Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a Random graph with N nodes and L links
//
// createTopologyRandom()
//------------------------------------------------------------------------------
Topology* TopologyFactory::createTopologyRandom(const TString &description)
{
    TRACE("TopologyFactory::createTopologyRandom -->");

    Topology* result = new Topology();

    result->number_of_nodes   = atoi(description.at(1).c_str());
    uli number_of_links       = atoi(description.at(2).c_str());
    result->is_directed       = description.size()<4 ? false :
        (atoi(description.at(3).c_str()) != 0);
    result->number_of_qos     = 0;
    result->link_list         = new LinkList(result->number_of_nodes);

    // Make list of all posible nodepairs and pick randomly from this list to
    // make the links. Only make new pairs when description has changed (or is new)
    if (!(last_description == description))
    {
        last_description = description;
        pairs.clear();
        edge_nodes.clear();
        for (int source = 0; source < result->number_of_nodes; ++source)
        {
            edge_nodes.push_back(source); // all nodes are edge-ndoes
            int dest_max = result->is_directed ? result->number_of_nodes : source;
            for (int dest = 0; dest < dest_max ; ++dest)
            {
                NodePair x;
                x.source = source;
                x.destination = dest;
                pairs.push_back(x);
            }
        }
    }
    result->edge_nodes = edge_nodes;

    // Now build nodepairs list. Move pairs from full to empty list until one
    // list has requested size. Then this list is used to build the topology.
    NodePairDeque pairs1;
    NodePairDeque pairs2(pairs);
    uli counter1 = 0;
    uli counter2 = (uli) pairs2.size();

    // number of links cannot exceed maximum links
    uli maximum_links = (uli)  result->number_of_nodes *
        (result->number_of_nodes - 1) / 2;
    number_of_links   = maximum_links < number_of_links ?
        maximum_links : number_of_links;

    while (counter1 != number_of_links && counter2 != number_of_links)
    {
        // Pick random pair
        uli ix = (uli) ceil( (double) counter2*rng->generate() )-1;
        NodePairDeque::iterator iter = pairs2.begin() + ix;
        pairs1.push_back(*iter);
        pairs2.erase(iter);
        ++counter1; --counter2;
    }
    build(counter1 == number_of_links ? pairs1 : pairs2, result);
    TRACE("TopologyFactory::createTopologyRandom <--");
    return result;
}

