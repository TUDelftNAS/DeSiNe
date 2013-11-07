/******************************************************************************

	source file TopologyFactoryFile.cpp with implementation of
	createTopologyFile

	Author : T. Kleiberg
	Version: 1
	Date   : Mar 2007

******************************************************************************/

//------------------------------------------------------------------------------
// Create a topology from file
//
// createTopologyFile()
//------------------------------------------------------------------------------

Topology* TopologyFactory::createTopologyFile(const TString &description)
{
	TRACE("TopologyFactory::createTopologyFile -->");

	Topology* result = new Topology();
	result->input_type = 0;
	result->is_directed = false;
	//result->lcf_visitor = (LinkCostFunctionVisitor*) 0;

	FileReader fr(description.at(1));
	{	// read headers
		TString line;

		// read #nodes, #edgenodex, #qos
		fr.firstLine(line);
		result->number_of_nodes = atoi(line.at(0).c_str());
		int number_of_edgenodes = atoi(line.at(1).c_str());
		result->number_of_qos = atoi(line.at(2).c_str());
		if (line.size() > 3)
		{
			result->input_type = atoi(line.at(3).c_str());
		}
		if (line.size() > 4)
		{
			result->is_directed = (bool) atoi(line.at(4).c_str());
		}

		// read edgenodes list
		if (number_of_edgenodes > 0)
		{
			fr.nextLine(line);
			for(std::size_t index=0;index<line.size();++index)
			{
				result->edge_nodes.push_back(atoi(line.at(index).c_str() ));
			}
		}
	} //end: block
	result->link_list = new LinkList(result->number_of_nodes);

	// read links and traffic matrix
	for (TString line; fr.nextLine(line); )
	{
		if (line.size() == 3 && result->input_type==1) // traffic matrix
		{
			result->f_src.push_back(atoi(line.at(0).c_str()));
			result->f_dest.push_back(atoi(line.at(1).c_str()));
			result->f_reqc.push_back(atof(line.at(2).c_str()));
		} // line,size == 3
		else
		{	// length = #values per link, i.e. src, dst, cost, capacity & #qos
			IntVector cost;
			cost.push_back(atoi(line.at(0).c_str() ));	// src
			cost.push_back(atoi(line.at(1).c_str() ));	// dst
			cost.push_back(atoi(line.at(2).c_str() ));	// cost
			result->cost_list.push_back(cost);

			DblVector link;
			link.push_back(cost[0]);					// src
			link.push_back(cost[1]);					// dst
			link.push_back(0.0);						// core
			link.push_back(cost[3]);					// cap
			for(std::size_t index= 4; index < line.size(); ++index)
			{
				link.push_back(atof( line.at(index).c_str() ));
			}
			result->link_list->insert(link);
			if  (!result->is_directed)
			{
				DblVector rlink(link);
				rlink[0] = link[1];
				rlink[1] = link[0];
				result->link_list->insert(rlink);
			}
		} // line.size != 3
	}
	TRACE("TopologyFactory::createTopologyFile <--");
	return result;
}

