/******************************************************************************

    source file TopologyFactoryErdos.cpp with implementation of
	createTopologyErdos

    Author : T. Kleiberg
    Version: 1
    Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a E-R Random graph with N nodes and linkprobability p
//
// createTopologyErdos()
//------------------------------------------------------------------------------
Topology* TopologyFactory::createTopologyErdos(const TString &description)
{
    TRACE("TopologyFactory::createTopologyErdos -->");

    Topology* result = new Topology();

    result->number_of_nodes   = atoi(description.at(1).c_str());
    double link_probability   = atof(description.at(2).c_str());
    result->is_directed       = description.size()<4 ? false :
        (atoi(description.at(3).c_str()) != 0);
    result->number_of_qos     = 0;
    result->link_list         = new LinkList(result->number_of_nodes);

    // Make list of all posible nodepairs and remove link with
    // probability (1-p)
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

    // Now build nodepairs list.
    NodePairDeque nodepairs(pairs);
    if (link_probability < 1.0)
    {
        for(NodePairDeque::iterator iter = nodepairs.begin();
            iter != nodepairs.end(); )
        {
            // remove if rnd > prob or just increase iter when rnd <= prob
            iter = rng->generate() <= link_probability ?
                iter + 1 : nodepairs.erase(iter);
        }
    }
    build(nodepairs, result);
    TRACE("TopologyFactory::createTopologyErdos <--");

    return result;
}

