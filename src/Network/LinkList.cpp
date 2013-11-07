/******************************************************************************

    source file LinkList.cpp for class: LinkList

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Network/Link.h"
#include "Network/LinkList.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <map>
#include <ostream>
using std::endl;
using std::make_pair;
using std::ostream;
using Types::ull;
using Types::DblVector;


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor LinkList::LinkList(int number_of_nodes)
//------------------------------------------------------------------------------
LinkList::LinkList(const int& number_of_nodes)
{
    TRACE("LinkList::LinkList -->");
    // Initialize map and create submaps...
    link_map = new IntIntLinkMap();
    for (int source = 0; source < number_of_nodes; ++source)
    {
        link_map->insert(make_pair(source, new IntLinkMap()));
    }
    TRACE("LinkList::LinkList <--");
}


//------------------------------------------------------------------------------
//  constructor LinkList(const LinkList& original);
//------------------------------------------------------------------------------
LinkList::LinkList(const LinkList& original)
{
    TRACE("LinkList::LinkList2 -->");
    // Initialize map and create submaps...
    link_map = new IntIntLinkMap(*original.link_map);

    // iterate source nodes
    for (IntIntLinkMap::iterator srcIX = link_map->begin();
         srcIX != link_map->end(); ++srcIX)
    {
        IntLinkMap* dest_map = new IntLinkMap(*srcIX->second);
        // iterate destination nodes
        for (IntLinkMap::iterator dstIX = dest_map->begin();
             dstIX != dest_map->end(); ++dstIX)
        {
            dstIX->second = new Link(*dstIX->second);
        }
        srcIX->second = dest_map;
    }

    TRACE("LinkList::LinkList2 <--");
}


//------------------------------------------------------------------------------
//  destructor LinkList::~LinkList()
//------------------------------------------------------------------------------
LinkList::~LinkList()
{
    TRACE("LinkList::~LinkList -->");

    //remove all elements
    // iterate source nodes
    for (IntIntLinkMap::iterator srcIX = link_map->begin();
         srcIX != link_map->end(); ++srcIX)
    {
        IntLinkMap* dest_map = srcIX->second;
        // iterate destination nodes
        for (IntLinkMap::iterator dstIX = dest_map->begin();
             dstIX != dest_map->end(); ++dstIX)
        {
            delete dstIX->second;
//                dest_map->erase(dstIX++);
        }
        delete srcIX->second;
//            link_map->erase(srcIX++);
    }
    delete link_map;
    TRACE("LinkList::~LinkList <--");
}


//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//------------------------------------------------------------------------------
void LinkList::accept(AbstractNetworkElementVisitor& anev)
{
    TRACE("LinkList::accept -->");
    // iterate all links
    for (LinkListIterator iter = getIterator(); iter(); ++iter)
    {
        (*iter)->accept(anev); // print the link
    }
    anev.visitLinkList(this);
    TRACE("LinkList::accept <--");
}


//------------------------------------------------------------------------------
//  LinkListMemento* LinkList::createMemento()
//------------------------------------------------------------------------------
LinkListMemento* LinkList::createMemento() const
{
    TRACE("LinkList::createMemento -->");

    LinkListMemento* result = new LinkListMemento(link_map);

    TRACE("LinkList::createMemento <--");
    return result;
}


//------------------------------------------------------------------------------
//  usi getNodalDegree(int source) const;
//------------------------------------------------------------------------------
usi LinkList::getNodalDegree(const int &source) const
{
    TRACE("LinkList::getNodalDegree -->");
    usi result = (*link_map)[source]->size();
    TRACE("LinkList::getNodalDegree <--");
    return result;
}



//------------------------------------------------------------------------------
//  Link* LinkList::insert(const DblVector* specs)
//------------------------------------------------------------------------------
Link* LinkList::insert(const DblVector& specs)
{
    TRACE("LinkList::insert -->");

    Link* result;

    // set source and dest etc
    int source      = (int) specs[0];
    int dest        = (int) specs[1];
    int core        = (int) specs[2];
    double capacity = (double) specs[3];

    DblVector qos_metrics;
    for (unsigned int qos = 4; qos < specs.size(); ++qos)
    {
        qos_metrics.push_back(specs[qos]);
    }
    result = insert(new Link(source, dest, capacity, core, qos_metrics));

    TRACE("LinkList::insert <--");
    return result;
}


//------------------------------------------------------------------------------
//  Link* LinkList::insert(int source, int destination, Link* new_link)
//------------------------------------------------------------------------------
Link* LinkList::insert(Link* new_link)
{
    TRACE("LinkList::insert_ -->");

    int source   = new_link->source;
    int dest     = new_link->destination;
    Link* result = new_link;

    // set source and dest etc
    IntLinkMap* dest_map = (*link_map)[source];
    // Insert new destination->link pair if not existing
    if (dest_map->find(dest) == dest_map->end())
    {
        dest_map->insert(make_pair(dest, result));
    }
    else
    {
        // remove old link?? add duplicate link??
        // for now, new link will not be generated and old link is returned
        delete result;
        result = (*dest_map)[dest];
    }

    TRACE("LinkList::insert_ <--");
    return result;
}


//------------------------------------------------------------------------------
//  Link* LinkList::find(int source, int destination);
//------------------------------------------------------------------------------
Link* LinkList::find(const int& source, const int& destination) const
{
    //TRACE("LinkList::find -->");

    Link* result = (Link*) 0;

    // Find destination->link map for source
    IntLinkMap* dest_map = (*link_map)[source];
    // Find destination->link pair
    IntLinkIter iter = dest_map->find(destination);
    if (iter != dest_map->end())
    {
        result = iter->second;
    }

    //TRACE("LinkList::find <--");
    return result;
}


//------------------------------------------------------------------------------
//  Link* LinkList::find(int source, int destination);
//------------------------------------------------------------------------------
LinkListIterator LinkList::getIterator() const
{
    TRACE("LinkList::getIterator1 -->");

    LinkListIterator result(link_map);

    TRACE("LinkList::getIterator1 <--");
    return result;
}


//------------------------------------------------------------------------------
//  Link* LinkList::find(int source, int destination);
//------------------------------------------------------------------------------
LinkListIterator LinkList::getIterator(const int& source) const
{
    TRACE("LinkList::getIterator2 -->");

    LinkListIterator result(link_map, source);

    TRACE("LinkList::getIterator2 <--");
    return result;
}


//------------------------------------------------------------------------------
//  print(ostream &buffer)
//------------------------------------------------------------------------------
void LinkList::print(ostream &buffer) const
{
    //buffer << "LinkList> LinkCostFunction: ";
    //(*iter)->getLinkCostFunction().print(buffer);
    //buffer << endl;
    // iterate all links
    for (LinkListIterator iter = getIterator(); iter(); ++iter)
    {
        (*iter)->print(buffer); // print the link
    }
}


//------------------------------------------------------------------------------
//  void reset()
//------------------------------------------------------------------------------
void LinkList::reset()
{
    TRACE("LinkList::reset -->");

    // reset member variables (??)

    // iterate all links
    for (LinkListIterator iter = getIterator(); iter(); ++iter)
    {
        (*iter)->reset(); // reset the link
    }

    TRACE("LinkList::reset <--");
}


//------------------------------------------------------------------------------
//  Link* LinkList::find(int source, int destination);
//------------------------------------------------------------------------------
void LinkList::remove(const int& source, const int& destination)
{
    TRACE("LinkList::remove -->");

    IntLinkMap* dest_map = (*link_map)[source];
    // Find destination->link pair
    if (dest_map->find(destination) != dest_map->end())
    {
        delete (*dest_map)[destination]; // delete the link
        dest_map->erase(destination);
    }
/*
    dest_map = (*link_map)[destination];
    // Find destination->link pair
    if (dest_map->find(source) != dest_map->end())
    {
        delete (*dest_map)[source]; // delete the link
        dest_map->erase(source);
    }
*/
    TRACE("LinkList::remove <--");
}

//------------------------------------------------------------------------------
//  void LinkList::rollbackMemento(const LinkListMemento* memento)
//------------------------------------------------------------------------------
void LinkList::rollbackMemento(LinkListMemento* memento)
{
    TRACE("LinkList::rollbackMemento -->");

    // Swap elements, only IntLinkMap need to be swapped
    swap( *memento->link_map, *link_map);
    // Memento now contains the old link states, these will be deleted
    // when Memento object is deleted
    TRACE("LinkList::rollbackMemento <--");
}


//------------------------------------------------------------------------------
//  long size()
//
//  Returns the number of links
//  Input :
//  Output: the number of links
//------------------------------------------------------------------------------
ull LinkList::size() const
{
    TRACE("LinkList::size -->");

    ull result = 0;
    // iterate source nodes
    for (IntIntLinkMap::const_iterator srcIX = link_map->begin();
         srcIX != link_map->end(); ++srcIX)
    {
        result += srcIX->second->size();
    }

    TRACE("LinkList::size <--");
    return result;
}
