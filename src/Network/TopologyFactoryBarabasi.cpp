/******************************************************************************

    source file TopologyFactoryBarabasi.cpp with implementation of
    createTopologyBarabasi

    Author : T. Kleiberg
    Version: 1
    Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a Barabasi-Albert power-law graph with N nodes, a core of m0 nodes
// and m links per new node. If m is omitted or m=0 then m=m0
// Graph is ALWAYS undirected.
//
// number of links is always L = (N-m0) * m if core is empty.
//                 otherwise L = (N-m0) * m + m0 * (m0-1) / 2
// createTopologyBarabasi()
//------------------------------------------------------------------------------
Topology* TopologyFactory::createTopologyBarabasi(const TString &description)
{
    TRACE("TopologyFactory::createTopologyBarabasi -->");

    Topology* result = new Topology();
    result->number_of_nodes   = atoi(description.at(1).c_str());
    usi m0                    = atoi(description.at(2).c_str());
    usi m = (description.size() > 3) ? atoi(description.at(3).c_str()) : 0;
    m = (m==0 || m > m0) ? m0 : m;
	// If core is not full mesh, then m0 MUST be equal to m
#ifndef BARABASI_FULL_MESH_CORE
	m = m0;
#endif
    result->is_directed       = 0;
    result->number_of_qos     = 0;
    result->link_list         = new LinkList(result->number_of_nodes);

    pairs.clear();
    edge_nodes.clear();

	// Create a vector that maintains the degree of all nodes, used for computation
	// of the attachment probabilities. This vector also serves to control the
	// number of 'added' nodes. sum_degrees maintains the sum of all degrees.
    vector<usi> degreevector(m0, 0);
	uli sum_degrees = 0;

	// Build the core, can be full mesh or collection of vertices
    for (int source = 0; source < m0; ++source)
    {
        edge_nodes.push_back(source);
#ifdef BARABASI_FULL_MESH_CORE
        degreevector[dest] = m0-1;
		sum_degrees += m0-1;
		// create a full-mesh core.
        for (int dest = 0; dest < source; ++dest)
        {
            NodePair x;
            x.source = source;
            x.destination = dest;
            pairs.push_back(x);
        }
#endif
    }

	// Start adding nodes
	while ((int) edge_nodes.size() < result->number_of_nodes)
	{
		// New node is 'added', now add m links to random nodes
		// Attachnodes holds the set of nodes to which the new node is attached.
		set<usi> attachnodes;

		// if 'empty' core, automatically add all nodes to attachnodes
		if (sum_degrees == 0)
		{
			for (int node_index = 0; node_index < m0; ++node_index)
			{
				attachnodes.insert(node_index);
			}
		} // end: if (sum_degrees == 0)

		for (usi m_index = 0; m_index < m; ++m_index)
		{
			// Find m links which may not be attached to same nodes.
			while(attachnodes.size() <= m_index) // size = m_ix+1 if node is found
			{
				// find right node
				double rnd = rng->generate();
				usi node_index = 0;
				uli node_degree_sum = degreevector[node_index];
				while(node_degree_sum < rnd * sum_degrees)
				{
					node_degree_sum += degreevector[++node_index];
				}
				// Attach-node has index node_index
				// add node_index, if it is in the set, then nothing happens
				// (set does not allow duplicates)
				attachnodes.insert(node_index);
			} //end: while(attachnodes.size()
		} // end: for (usi m_index = 0;

		// m links have been found, now add the node_pairs and update degree_vec
		// the 'new' node has the ID #nodes + 1 == edge_nodes.size()
        edge_nodes.push_back((int) edge_nodes.size());
		sum_degrees += 2 * m;
		degreevector.push_back(m);

		// construct the links (node_pairs)
		for (set<usi>::const_iterator iter = attachnodes.begin();
			iter !=attachnodes.end(); ++iter)
		{
			degreevector[*iter]++;

            NodePair x;
            x.source = edge_nodes.back();
            x.destination = edge_nodes[*iter];
            pairs.push_back(x);
		} // end: for (set<usi>.const_iterator iter
	} //end: while (degreevector.size()
	result->edge_nodes = edge_nodes;
    build(pairs, result);

    TRACE("TopologyFactory::createTopologyBarabasi <--");
    return result;
}

