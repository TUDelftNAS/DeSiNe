#ifndef LINKLIST_H
#define LINKLIST_H
/******************************************************************************

    header file LinkList.h for class: LinkList

    This class manages all links that makeup the network. It both creates and
    desctructs them. It also declares the classes ...Iterator and ...Memento.
    The definitions of the latter are placed in separate files however.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElement.h"
#include "Network/AbstractNetworkElementVisitor.h"
#include "Network/Link.h"
#include "Utils/Types.h"
#include <map>
#include <ostream>
#include <string>
using std::map;
using std::ostream;
using std::string;
using Types::ull;
using Types::DblVector;

// Declare classes
class LinkListIterator;
class LinkListMemento;

class LinkList : public AbstractNetworkElement
{
    // Typedef(s)
    private:
    typedef map<int, Link*> IntLinkMap;
    typedef map<int, IntLinkMap*> IntIntLinkMap;
    typedef IntLinkMap::const_iterator IntLinkIter;
    typedef IntIntLinkMap::const_iterator IntIntLinkIter;

    //friend void AbstractNetworkElementVisitor::visitLinkList(const AbstractNetworkElement* linklist);
    //friend void DegreeDistributionVisitor::visitLinkList(const AbstractNetworkElement* linklist);
    friend class LinkListIterator;
    friend class LinkListMemento;
    friend class DegreeDistributionVisitor;

    // Variable(s)
    private:
    IntIntLinkMap* link_map; // used for source -> dest_link map


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor LinkList(int number_of_nodes);
//
//  Constructs LinkList
//  Input :number of nodes
//  Output:
//------------------------------------------------------------------------------
    LinkList(const int &number_of_nodes);


//------------------------------------------------------------------------------
//
//  constructor LinkList(const LinkList& original);
//
//  Constructs LinkList
//  Input :number of nodes
//  Output:
//------------------------------------------------------------------------------
    LinkList(const LinkList &original);


//------------------------------------------------------------------------------
//
//  destructor ~LinkList()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LinkList();


//------------------------------------------------------------------------------
//  accept(AbstractNetworkElementVisitor& anev);
//
//  Accepts and executes a network element visitor
//
//------------------------------------------------------------------------------
    void accept(AbstractNetworkElementVisitor& anev);


//------------------------------------------------------------------------------
//  Link* insert(DblVector* specs);
//
//  Insert a new Link with the specified characteristics.
//  Input :
//     specs :  an array defining source, dest, cap, core, qos
//  Output:
//      - : the new Link
//------------------------------------------------------------------------------
    Link* insert(const DblVector &specs);


//------------------------------------------------------------------------------
//  Link* insert(int source, int destination, Link* new_link);
//
//  Insert a new Link
//  Input :
//  Output:
//      - : the new Link
//------------------------------------------------------------------------------
    Link* insert(Link* new_link);


//------------------------------------------------------------------------------
//  Link* find(int source, int destination);
//
//  Retrieve a link with source/destination pair
//  Input :
//     source and destination node
//  Output:
//      - : the Link or 0 if no link matches the criteria
//------------------------------------------------------------------------------
    Link* find(const int &source, const int &destination) const;


//------------------------------------------------------------------------------
//  LinkListIterator iterator()
//
//  Returns iterator for all links
//------------------------------------------------------------------------------
    LinkListIterator getIterator() const;


//------------------------------------------------------------------------------
//  LinkListIterator getIterator(int source)
//
//  Returns iterator for all links with specific source node
//------------------------------------------------------------------------------
    LinkListIterator getIterator(const int &source) const;

//------------------------------------------------------------------------------
//  usi getNodalDegree(int source)
//
//  Returns nodal degree for <source>
//------------------------------------------------------------------------------
    usi getNodalDegree(const int &source) const;


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints link to the buffer
//
//  Input : the buffer
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;


//------------------------------------------------------------------------------
//  void remove(int source, int destination)
//
//  Remove a link from the topology
//  Input :
//     source and destination node
//  Output:
//------------------------------------------------------------------------------
    void remove(const int &source, const int &destination);


//------------------------------------------------------------------------------
//  ull size()
//
//  Returns the number of links
//  Input :
//  Output: the number of links
//------------------------------------------------------------------------------
    ull size() const;


//------------------------------------------------------------------------------
//  LinkListMemento* createMemento()
//
//  Create a memento object for the link list
//
//  Input :
//  Output: the memento

//------------------------------------------------------------------------------
    LinkListMemento* createMemento() const;


//------------------------------------------------------------------------------
//  void reset()
//
//  Reset the links (and LinkList) to its initial state
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void reset();

//------------------------------------------------------------------------------
//  void rollbackMemento(LinkListMemento* memento)
//
//  Rolls back to the state stored in the memento. The memento object is NOT
//  deleted.
//
//  Input : the memento
//  Output:
//------------------------------------------------------------------------------
    void rollbackMemento(LinkListMemento* memento);

}; //end declarations LinkList



/******************************************************************************

    header for class: LinkListIterator

    This class forms an iterator for the links list.

    No tracing performed in this class

******************************************************************************/
class LinkListIterator
{
    friend class LinkList;

    // Variable(s)
    private:
    bool allLinks;
    LinkList::IntLinkIter link_iter;
    LinkList::IntLinkIter link_iter_end;
    LinkList::IntIntLinkIter src_iter;
    LinkList::IntIntLinkIter src_iter_end;


    // Function(s) declarations
    public: //private:
//------------------------------------------------------------------------------
//
//  constructor LinkListIterator(IntIntLinkMap* linkmap);
//
//  Constructs LinkListIterator for all links
//  Input : the link list
//  Output:
//------------------------------------------------------------------------------
    LinkListIterator(const LinkList::IntIntLinkMap* linkmap);


//------------------------------------------------------------------------------
//
//  constructor LinkListIterator(IntIntLinkMap* linkmap, int source)
//
//  Constructs LinkListIterator for all links with a spec. source node
//  Input : the link iterator (for a specific source node)
//  Output:
//------------------------------------------------------------------------------
    LinkListIterator(const LinkList::IntIntLinkMap* linkmap, const int &source);


    public:
//------------------------------------------------------------------------------
//
//  destructor ~LinkListIterator()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LinkListIterator() {}


//------------------------------------------------------------------------------
//  void operator++();
//
//  Increment the iterator
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void operator++();


//------------------------------------------------------------------------------
//  bool operator()();
//
//  Checks if end has been reached of iterator
//  Input :
//  Output: false if no more elements
//------------------------------------------------------------------------------
    bool operator()();


//------------------------------------------------------------------------------
//  Link* operator*();
//
//  Returns the actual element (the Link)
//  Input :
//  Output: the link
//------------------------------------------------------------------------------
    Link* operator*() const
    {
        return (Link*)link_iter->second;
    }
}; //end declarations LinkListIterator



/******************************************************************************

    header for class: LinkListMemento

    This class forms a memento of the LinkListMemento, used to undo and rollback
    the links in a topology. See the Memento pattern.

******************************************************************************/
class LinkListMemento
{
    friend class LinkList;
    // Constanst(s)

    // Variable(s)
    private:
    LinkList::IntIntLinkMap* link_map;


    // Function(s) declarations
    private:
//------------------------------------------------------------------------------
//
//  constructor LinkListMemento(Parameters* params);
//
//  Constructs LinkListMemento
//  Input :
//      params : the Parameters
//  Output:
//------------------------------------------------------------------------------
    LinkListMemento(const LinkList::IntIntLinkMap *linkmap);


    public:
//------------------------------------------------------------------------------
//
//  destructor ~LinkListMemento()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~LinkListMemento();

}; //end declarations
#endif //LINKLIST_H
