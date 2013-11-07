/******************************************************************************

    source file TopologyFactoryFull.cpp with implementation of
	createTopologyFull

    Author : T. Kleiberg
    Version: 1
    Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a Full-Mesh Network of N nodes
//
// createTopologyFull()
//------------------------------------------------------------------------------
Topology* TopologyFactory::createTopologyFull(const TString &description)
{
    TRACE("TopologyFactory::createTopologyFull -->");

    Topology* result = new Topology();

    result->number_of_nodes   = atoi(description.at(1).c_str());
    result->is_directed       = description.size()<3 ? false :
        (atoi(description.at(2).c_str()) != 0);
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
    build(pairs, result);

    TRACE("TopologyFactory::createTopologyFull <--");
    return result;
}
