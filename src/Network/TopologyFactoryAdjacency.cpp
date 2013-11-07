/******************************************************************************

	source file TopologyFactoryAdjacency.cpp with implementation of
	createTopologyAdjacency

	Author : T. Kleiberg
	Version: 1
	Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a topology from adjacency file
//
// createTopologyAdjacency()
//------------------------------------------------------------------------------

Topology* TopologyFactory::createTopologyAdjacency(const TString &description)
{
	TRACE("TopologyFactory::createTopologyAdjacency -->");

	Topology* result = new Topology();
	result->input_type = 0;
	result->is_directed = false;

	{	// First find number of nodes, which requires to read entire file
		FileReader fr(description.at(1));
		std::set<int> nodes;
		TString line;

		// read #nodes
		for(bool cont = fr.firstLine(line); cont; cont = fr.nextLine(line))
		{
			nodes.insert(atoi(line.at(0).c_str()));
			nodes.insert(atoi(line.at(1).c_str()));
		}
		result->number_of_nodes = nodes.size();
		result->edge_nodes.assign(nodes.begin(), nodes.end());
	} //end: block
    result->number_of_qos     = 0;
    result->link_list         = new LinkList(result->number_of_nodes);

	{	// Build links
		FileReader fr(description.at(1));
		TString line;

		// read #nodes
		for(bool cont = fr.firstLine(line); cont; cont = fr.nextLine(line))
		{
			DblVector link;
			link.push_back(atof(line.at(0).c_str()));	// src
			link.push_back(atof(line.at(1).c_str()));	// dst
			link.push_back(0.0);						// core
			link.push_back(atof(line.at(2).c_str()));	// cap
			result->link_list->insert(link);
			if  (!result->is_directed)
			{
				DblVector rlink(link);
				rlink[0] = link[1];
				rlink[1] = link[0];
				result->link_list->insert(rlink);
			} // end: if
		} //end:  for
	} //end: block
	TRACE("TopologyFactory::createTopologyAdjacency <--");
	return result;
}
