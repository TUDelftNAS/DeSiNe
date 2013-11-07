/******************************************************************************

    source file Topology.cpp for class: Topology

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/Cluster.h"
#include "Network/Link.h"
#include "Network/Topology.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <deque>
#include <iostream>
#include <string>
#include <cmath>
using std::deque;
using std::endl;
using std::ostream;
using std::string;
using Types::IntVector;
using Types::DblVector;

// Constanst(s)

// Variable(s)

// Function(s) definitions


//------------------------------------------------------------------------------
//  constructor Topology::Topology()
//------------------------------------------------------------------------------
Topology::Topology()
{
    TRACE("Topology::Topology -->");
    number_of_nodes   = 0;
    input_type = 0;
    is_directed       = false;
    number_of_qos     = 0;
    link_list         = (LinkList*) 0;
    lcf_visitor = (LinkCostFunctionVisitor *) 0;

    TRACE("Topology::Topology <--");
}

//------------------------------------------------------------------------------
//  constructor Topology::Topology(const Topology& original)
//------------------------------------------------------------------------------
/*
Topology::Topology(const Topology& original)
{
    TRACE("Topology::Topology4 -->");
    number_of_nodes = original.number_of_nodes;
    number_of_qos   = original.number_of_qos;
    edge_nodes      = new IntVector(*original.edge_nodes);
    link_list       = new LinkList(*original.link_list);
    is_directed     = original.is_directed;

    lcf_visitor = original.lcf_visitor ? lcf_factory.create(
        original.lcf_visitor->getName()) : (LinkCostFunctionVisitor*) 0;

    TRACE("Topology::Topology4 <--");
}
*/

//------------------------------------------------------------------------------
//  destructor Topology::~Topology()
//------------------------------------------------------------------------------
Topology::~Topology()
{
    TRACE("Topology::~Topology -->");

    delete link_list;
    delete lcf_visitor;

    TRACE("Topology::~Topology <--");
}


//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//------------------------------------------------------------------------------
void Topology::accept(AbstractNetworkElementVisitor& anev)
{
    TRACE("Topology::accept -->");
    link_list->accept(anev);
    anev.visitTopology(this);
    TRACE("Topology::accept <--");
}



//------------------------------------------------------------------------------
//  void allocate(const int& source,
//                const int& destination,
//                const double& req_capacity)
//------------------------------------------------------------------------------
void Topology::allocate(const int& source, const int& destination,
    const double& req_capacity)
    throw (InsufficientCapacityException &)
{
    TRACE("Topology::allocate -->");
    link(source, destination)->allocate(req_capacity);
    if(!is_directed)
    {
        link(destination, source)->allocate(req_capacity);
    }
    TRACE("Topology::allocate <--");

}


//------------------------------------------------------------------------------
//  LinkListMemento* createLinkListMemento()
//------------------------------------------------------------------------------
LinkListMemento* Topology::createLinkListMemento() const
{
    TRACE("Topology::createLinkListMemento -->");
    TRACE("Topology::createLinkListMemento <--");
    return link_list->createMemento();
}


//------------------------------------------------------------------------------
//  IntVector* getEdgeNodes();
//------------------------------------------------------------------------------
const IntVector Topology::getEdgeNodes() const
{
    TRACE("Topology::getEdgeNodes -->");
    TRACE("Topology::getEdgeNodes <--");
    return edge_nodes;
}


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
int Topology::getInputType() const
{
    TRACE("Topology::getInputType -->");
    TRACE("Topology::getInputType <--");
    return input_type;
}


//------------------------------------------------------------------------------
//  Link* ggetRandomLink
//------------------------------------------------------------------------------
Link* Topology::getRandomLink() const
{
    return getRandomLink(getRandomNode());
}

//------------------------------------------------------------------------------
//  Link* ggetRandomLink
//------------------------------------------------------------------------------
Link* Topology::getRandomLink(int source) const
{
    TRACE("Topology::getRandomLink() -->");

    Link* result = (Link*) 0;
    usi degree = getNodalDegree(source);
    if (degree>0)
    {
        size_t ix = (size_t) ceil( (double) degree *
            (RandomNumberGenerator::getRandomNumberGenerator())->generate() )-1;
        LinkListIterator iter = link_list->getIterator(source);
        for (size_t counter=0; counter < ix; ++counter, ++iter) {}
        result = *iter;
    }
    TRACE("Topology::getRandomLink() <--");
    return result;
}


//------------------------------------------------------------------------------
//  int getRandomNode
//------------------------------------------------------------------------------
int Topology::getRandomNode() const
{
    TRACE("Topology::getRandomNode() -->");

    // Random generator generates (0, 1]
    int result = (int) ceil( (double) number_of_nodes *
        (RandomNumberGenerator::getRandomNumberGenerator())->generate() )-1;

    TRACE("Topology::getRandomNode() <--");
    return result;
}


//------------------------------------------------------------------------------
//  int getRandomEdgeNode
//------------------------------------------------------------------------------
int Topology::getRandomEdgeNode(RandomVar* rng) const
{
    TRACE("Topology::getRandomEdgeNode -->");

    // Random generator does generates (0, 1]
    int index = (int) ceil( (double) edge_nodes.size() * rng->generate()) -1;
    int result = edge_nodes[index];

    TRACE("Topology::getRandomEdgeNode <--");
    return result;
}


//------------------------------------------------------------------------------
//  NodeVector getNeighbours(int source) const;
//------------------------------------------------------------------------------
Topology::NodeVector Topology::getNeighbours(int source) const
{
    TRACE("Topology::getNeighbours -->");
    NodeVector result;
    for (LinkListIterator iter = link_list->getIterator(source); iter(); ++iter)
    {
        result.push_back((*iter)->getDestination());
    }
    TRACE("Topology::getNeighbours <--");
    return result;
}


//------------------------------------------------------------------------------
//  int getNumLinks();
//------------------------------------------------------------------------------
ull Topology::getNumLinks() const
{
    TRACE("Topology::getNumLinks -->");
    ull result = is_directed ? link_list->size() : (ull) (link_list->size()*0.5);
    TRACE("Topology::getNumLinks <--");
    return result;
}


//------------------------------------------------------------------------------
//  int getNumNodes();
//------------------------------------------------------------------------------
int Topology::getNumNodes() const
{
    TRACE("Topology::getNumNodes -->");
    TRACE("Topology::getNumNodes <--");
    return number_of_nodes;
}


//------------------------------------------------------------------------------
//  int getNumQos();
//------------------------------------------------------------------------------
int Topology::getNumQos() const
{
    TRACE("Topology::getNumQos-->");
    TRACE("Topology::getNumQos <--");
    return number_of_qos;
}

const int Topology::getflowsrc(const int& indexsrc)
{
    TRACE("Topology::getflowsource-->");
    TRACE("Topology::getflowsource <--");

	return f_src[indexsrc];
}
const int Topology::getflowdest(const int& indexsrc)
{
    TRACE("Topology::getflowdest-->");
    TRACE("Topology::getflowdest <--");

	return f_dest[indexsrc];
}
const double Topology::getflowreqc(const int& indexsrc)
{
    TRACE("Topology::getflowreqc-->");
    TRACE("Topology::getflowreqc <--");

	return f_reqc[indexsrc];
}
const int Topology::getNumSDpairs()
{
	return f_src.size();
}

//IntVector* Topology::getflowsrcVector()
//{
//   TRACE("Topology::getflowsrcVector-->");
//    TRACE("Topology::getflowsrcVector <--");
//    return f_src;
//}
//IntVector* Topology::getflowdestVector()
//{
//    TRACE("Topology::getflowdestVector-->");
//    TRACE("Topology::getflowdestVector <--");
//    return f_dest;
//}
//DblVector* Topology::getflowreqcVector()
//{
//    TRACE("Topology::getflowreqcVector-->");
//    TRACE("Topology::getflowreqcVector <--");
//    return f_reqc;
//}
//------------------------------------------------------------------------------
//  LinkListIterator getLinkIterator()
//------------------------------------------------------------------------------
LinkListIterator Topology::getLinkIterator() const
{
    TRACE("Topology::getLinkIterator1-->");
    TRACE("Topology::getLinkIterator1 <--");
    return link_list->getIterator();
}


//------------------------------------------------------------------------------
//  LinkListIterator getLinkIterator(int source)
//------------------------------------------------------------------------------
LinkListIterator Topology::getLinkIterator(const int& source) const
{
    TRACE("Topology::getLinkIterator2-->");
    TRACE("Topology::getLinkIterator2 <--");
    return link_list->getIterator(source);
}


//------------------------------------------------------------------------------
//  bool isConnected()
//------------------------------------------------------------------------------
bool Topology::isConnected() const
{
    TRACE("Topology::isConnected -->");
    Cluster cl(this);
    cl.build(0);
    bool result = (cl.size() == (uli) number_of_nodes);
    TRACE("Topology::isConnected <--");
    return result;
}


//------------------------------------------------------------------------------
//  Link* link(int source, int destination);
//------------------------------------------------------------------------------
Link* Topology::link(const int& source, const int& destination) const
{
    //TRACE("Topology::link -->");
    //TRACE("Topology::link <--");
    return link_list->find(source, destination);
}


//------------------------------------------------------------------------------
//  print(ostream &buffer)
//------------------------------------------------------------------------------
void Topology::print(ostream &buffer) const
{
    buffer << "Topology> Nodes: " << number_of_nodes << "\tEdgenodes: ";
    buffer << edge_nodes.size()  << "\tLinks: "<< getNumLinks() << endl;
    link_list->print(buffer);
}


//------------------------------------------------------------------------------
//  void release(const int& source,
//                const int& destination,
//                const double& req_capacity)
//------------------------------------------------------------------------------
void Topology::release(const int& source, const int& destination,
    const double& req_capacity)
    throw (IllegalOperationException &)
{
    TRACE("Topology::release -->");
    link(source, destination)->release(req_capacity);
    if(!is_directed)
    {
        link(destination, source)->release(req_capacity);
    }
    TRACE("Topology::release <--");
}


//------------------------------------------------------------------------------
//  void remove(int source, int destination)
//------------------------------------------------------------------------------
void Topology::removeLink(const int& source, const int& destination)
{
    TRACE("Topology::removeLink -->");
    link_list->remove(source, destination);
    if (!is_directed)
    {
        link_list->remove(destination, source);
    }
    TRACE("Topology::removeLink <--");
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void Topology::reset()
{
    TRACE("Topology::reset -->");
    link_list->reset();
    TRACE("Topology::reset <--");
}

//------------------------------------------------------------------------------
//  void rollbackLinkListMemento(LinkListMemento* memento)
//------------------------------------------------------------------------------
void Topology::rollbackLinkListMemento(LinkListMemento* memento)
{
    link_list->rollbackMemento(memento);
}


//------------------------------------------------------------------------------
//  void setLinkCostFunction(const string description)
//------------------------------------------------------------------------------
void Topology::setLinkCostFunction(const string& description)
{
    TRACE("Topology::setLinkCostFunction -->");

    //DEBUG("description: " << description);
    //PRINTLN("lcf_visitor: " << lcf_visitor);
    if (lcf_visitor == (LinkCostFunctionVisitor*) 0)
    {
        lcf_visitor = lcf_factory.create(description);
        accept(*lcf_visitor);
    } else
    if (description.compare(lcf_visitor->getName()) != 0)
    {
        delete lcf_visitor;
        lcf_visitor = lcf_factory.create(description);
        accept(*lcf_visitor);
    }
    TRACE("Topology::setLinkCostFunction <--");
}
