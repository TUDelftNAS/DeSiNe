/******************************************************************************

    source file TopologyFactoryGrid.cpp with implementation of
	createTopologyGrid2D

    Author : T. Kleiberg
    Version: 1
    Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a Square Lattice with  Z*Z nodes and Uniformly distributed link-capacities
//
// createTopologyGrid2D()
//------------------------------------------------------------------------------
Topology* TopologyFactory::createTopologyGrid2D(const TString &description)
{
    TRACE("TopologyFactory::createTopologyGrid2D -->");

    Topology* result = new Topology();

    int rows                  = atoi(description.at(1).c_str());
    int cols                  = atoi(description.at(2).c_str());
    result->number_of_nodes   = rows * cols;
    result->is_directed       = description.size()<4 ? false :
        (atoi(description.at(3).c_str()) != 0);
    result->number_of_qos     = 0;
    result->link_list         = new LinkList(result->number_of_nodes);

    // Make list of all posible nodepairs and pick randomly from this list to
    // make the links. Only make new pairs when description has changed
    // (or is new). Nodes are numbered from left to right and then downwards
    if (!(last_description == description))
    {
        last_description = description;
        pairs.clear();
        edge_nodes.clear();
        for (int source = 0; source < result->number_of_nodes; ++source)
        {
            edge_nodes.push_back(source); // all nodes are edge-ndoes
            // Each node i connects to (i-1), (i+1), (i-cols), i+cols)
            // unless (i-1 mod cols = 0), (i+1 mod cols = 0), (i-cols < 0),
            // (i+cols > nodex-1)
            // in case of undirectedness, only connect to nodes with higher ID
            if (result->is_directed)
            {
                 // source == boundary node at begin of row, source != 0
                if (source > 0 ? source % cols > 0 :  false)
                {
                    NodePair x;
                    x.source = source;
                    x.destination = source-1;
                    pairs.push_back(x);
                }
                // source not in first row
                if (source >= cols)
                {
                    NodePair x;
                    x.source = source;
                    x.destination = source-cols;
                    pairs.push_back(x);
                }
            } // end: if (!result->is_directed)
            // source == boundary node at end of row
            if ((source+1) % cols > 0)
            {
                NodePair x;
                x.source = source;
                x.destination = source+1;
                pairs.push_back(x);
            }
            // source not in last row
            if (source+cols < result->number_of_nodes)
            {
                NodePair x;
                x.source = source;
                x.destination = source+cols;
                pairs.push_back(x);
            }
        } // end: for (int source = 0;
    } // end: if (last_description
    result->edge_nodes = edge_nodes;
    build(pairs, result);
    TRACE("TopologyFactory::createTopologyGrid2D <--");
    return result;
}
