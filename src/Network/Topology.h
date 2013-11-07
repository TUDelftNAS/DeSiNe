#ifndef TOPOLOGY_H
#define TOPOLOGY_H
/******************************************************************************

    header file Topology.h for class: Topology

    This class is meant to represent the topology.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "InsufficientCapacityException.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "LinkCostFunction/LinkCostFunctionVisitorFactory.h"
#include "Network/AbstractNetworkElement.h"
#include "Network/AbstractNetworkElementVisitor.h"
#include "Network/Link.h"
#include "Network/LinkList.h"
#include "Network/TopologyFactory.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/IllegalOperationException.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <list>
#include <ostream>
#include <string>
using std::list;
using std::ostream;
using std::string;
using Types::ull;
using Types::usi;
using Types::IntVector;


class Topology : public AbstractNetworkElement
{
    // Friend(s)
    friend class TopologyFactory;

    // Typedef(s)
    public:
    typedef vector<int> NodeVector;

    // Constanst(s)

    // Variable(s)
    private:
    int input_type; // the type of input defines how src and dst for flowmanager will be generated
    				// input_type = 0 means the topology is fixed, src, dst will be selected from
    				//	edge nodes according to the distribution defined in the parameters
    				// input_type = 1 means the topology and the traffic matrix are both fixed
    				//  src, dst, reqc will be generated based on the traffix matrix.

    int number_of_nodes;    // number of nodes in the network
    int number_of_qos;      // number of QoS metrics
    IntVector edge_nodes;   // Array with edge nodes
    IntVector costv;
    IntVector f_src;
   	IntVector f_dest;
   	DblVector f_reqc;

    LinkList* link_list;    // List with the links of the topology
    LinkCostFunctionVisitorFactory lcf_factory;
    LinkCostFunctionVisitor *lcf_visitor;
    bool is_directed;       // indicate directedness

    typedef list<IntVector> IntVectorList;
    IntVectorList cost_list;
    IntVectorList::const_iterator cost_iter; // used for traversing link values


    // Function(s) declarations
//------------------------------------------------------------------------------
//
//  constructor Topology();
//
//  Constructs empty Topology. Only TopologyFactory builds Topology.
//
//------------------------------------------------------------------------------
    private:
    Topology();

//------------------------------------------------------------------------------
//
//  constructor Topology(const Topology& original);
//
//  Clones Topology
//
//------------------------------------------------------------------------------
    public:
    //Topology(const Topology& original);

//------------------------------------------------------------------------------
//
//  destructor ~Topology()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~Topology();


//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//
//  Accepts and executes a network element visitor
//
//------------------------------------------------------------------------------
    void accept(AbstractNetworkElementVisitor& anev);


//------------------------------------------------------------------------------
//  void allocate(const int& source,
//                const int& destination,
//                const double& req_capacity)
//
//  Allocating requested capacity on a link.
//
//------------------------------------------------------------------------------
    void allocate(const int& source, const int& destination,
        const double& req_capacity)
        throw (InsufficientCapacityException &);


//------------------------------------------------------------------------------
//  LinkListMemento* createLinkListMemento()
//
//  Create a memento object for the link list
//
//  Input :
//  Output: the memento

//------------------------------------------------------------------------------
    LinkListMemento* createLinkListMemento() const;


//------------------------------------------------------------------------------
//
//  IntVector* getEdgeNodes();
//
//  Returns array of edge nodes in the network
//  Input :
//  Output:
//      - : pointer to list with nodes
//
//------------------------------------------------------------------------------
    const IntVector getEdgeNodes() const;

	const int getflowsrc(const int& indexsrc);
	const int getflowdest(const int& indexsrc);
	const double getflowreqc(const int& indexsrc);
	const int getNumSDpairs();
	//IntVector* getflowsrcVector();
	//IntVector* getflowdestVector();
	//DblVector* getflowreqcVector();
//------------------------------------------------------------------------------
//
//  int getNumLinks();
//
//  Returns the number of links in the network
//  Input :
//  Output:
//      - : the number of nodes
//
//------------------------------------------------------------------------------
    ull getNumLinks() const;

//------------------------------------------------------------------------------
//
//  int getInputType();
//
//  Returns the type of input
//  Input :
//  Output:
//      - : the type of input
//
//------------------------------------------------------------------------------
     int getInputType() const;

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
//  int getNumQos();
//
//  Returns the number of QoS constraints defined in the topology
//  Input :
//  Output:
//      - : the number of QoS constraints
//
//------------------------------------------------------------------------------
    int getNumQos() const;

//------------------------------------------------------------------------------
//  Link* getRandomLink()
//
// Returns a random link
//------------------------------------------------------------------------------
    Link* getRandomLink() const;


//------------------------------------------------------------------------------
//  Link* getRandomLink()
//
// Returns a random link connected to 'source'
//------------------------------------------------------------------------------
    Link* getRandomLink(int source) const;


//------------------------------------------------------------------------------
//  int getRandomNode()
//
// Returns a random node-index.
//------------------------------------------------------------------------------
    int getRandomNode() const;


//------------------------------------------------------------------------------
//  int getRandomEdgeNode(RandomVar* rng)
//
//  Returns a random node from the edgenodes list. The distribution for
//  picking the node must be specified.
//------------------------------------------------------------------------------
    int getRandomEdgeNode(RandomVar* rng) const;

//------------------------------------------------------------------------------
//
//  bool isConnected()
//
//  Tests if the topology is connected
//
//------------------------------------------------------------------------------
    bool isConnected() const;


//------------------------------------------------------------------------------
//
//  bool bool isDirected()
//
//  Tests if the topology is directed
//
//------------------------------------------------------------------------------
    bool isDirected() const
    {
        return is_directed;
    }


//------------------------------------------------------------------------------
//
//  Link* link(int source, int destination);
//
//  Returns link between source and destination
//  Input :
//  Output:
//      - : pointer to the link or NULL if not defined
//
//------------------------------------------------------------------------------
    Link* link(const int& source, const int& destination) const;


//------------------------------------------------------------------------------
//  usi getNodalDegree(int source)
//
//  Returns nodal degree for <source>
//------------------------------------------------------------------------------
    usi getNodalDegree(const int &source) const
    {
        return link_list->getNodalDegree(source);
    }

//------------------------------------------------------------------------------
//  NodeVector getNeighbours(int source) const;
//
//  Returns vector with neighboues of <source>
//------------------------------------------------------------------------------
    NodeVector getNeighbours(int source) const;


//------------------------------------------------------------------------------
//  LinkListIterator getLinkIterator()
//
//  Returns iterator for all links
//------------------------------------------------------------------------------
    LinkListIterator getLinkIterator() const;


//------------------------------------------------------------------------------
//  LinkListIterator getLinkIterator(int source)
//
//  Returns iterator for all links with specific source node
//------------------------------------------------------------------------------
    LinkListIterator getLinkIterator(const int& source) const;


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints topology to the buffer
//
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;


//------------------------------------------------------------------------------
//  void release(const int& source,
//                const int& destination,
//                const double& req_capacity)
//
//
//  Releasing requested capacity on a link.
//
//------------------------------------------------------------------------------
    void release(const int& source, const int& destination,
        const double& req_capacity)
        throw (IllegalOperationException &);


//------------------------------------------------------------------------------
//  void remove(int source, int destination)
//
//  Remove a link from the topology
//  Input :
//     source and destination node
//  Output:
//------------------------------------------------------------------------------
    void removeLink(const int& source, const int&destination);

//------------------------------------------------------------------------------
//
//  void reset()
//
//  Reset the topology to its initial state
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    void reset();

//------------------------------------------------------------------------------
//  void rollbackLinkListMemento(LinkListMemento* memento)
//
//  Rolls back to the link list state stored in the memento. The memento object
//  is NOT deleted.
//
//  Input : the memento
//  Output:
//------------------------------------------------------------------------------
    void rollbackLinkListMemento(LinkListMemento* memento);


//------------------------------------------------------------------------------
//  void setLinkCostFunction(const string description)
//
//  Sets the link cost funtion, no check performed!!
//  Input : link_cost_func
//  Output:
//------------------------------------------------------------------------------
    void setLinkCostFunction(const string &description);

}; //end declarations
#endif //TOPOLOGY_H
