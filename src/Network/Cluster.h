#ifndef CLUSTER_H
#define CLUSTER_H
/******************************************************************************

    header file Cluster.h for class: Cluster

    This class represents a cluster in a topology.

    Author : T. Kleiberg
    Version: 1
    Date   : August 2004

******************************************************************************/


// Include(s)
#include "Network/AbstractNetworkElement.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <ostream>
using std::ostream;
using Types::uli;
using Types::IntVector;
using Types::IntSet;


class ClusterIterator;

class Cluster
{
    // Constanst(s)

    // Variable(s)
    private:
    IntSet nodes;
    const AbstractNetworkElement* topology;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor PCluster(char* parameter_file);
//
//  Constructs Cluster.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    Cluster(const AbstractNetworkElement* topology) :
        topology(topology)
    {
        TRACE("Cluster::Cluster -->");
        // Empty
        TRACE("Cluster::Cluster <--");
    }


//------------------------------------------------------------------------------
//
//  constructor Cluster(Cluster org)
//
//  Constructs Cluster.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
//  Redundant due to use of aggregate types, used for traces
/*    Cluster(const Cluster& org)
    {
        TRACE("Cluster::Cluster2 -->");

        topology = org.topology;
        nodes = org.nodes;

        TRACE("Cluster::Cluster2 <--");
     }
*/


//------------------------------------------------------------------------------
//
//  destructor ~Cluster()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
//  Redundant due to use of aggregate types, used for traces
    ~Cluster()
    {
        TRACE("Cluster::~Cluster -->");
        //Empty
        TRACE("Cluster::~Cluster <--");
    }


//------------------------------------------------------------------------------
//  void add(int node)
//
//  Builds the cluster
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void add(const int& node)
    {
        nodes.insert(node);
    }

//------------------------------------------------------------------------------
//  void build(int startnode)
//
//  Builds the cluster
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void build(const int& startnode)
    {
        TRACE("Cluster::build -->");
        depthFirstSearch(startnode);
        TRACE("Cluster::build <--");
    }


//------------------------------------------------------------------------------
//  ClusterIterator getIterator();
//
//  Return iterator
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ClusterIterator getIterator() const;


//------------------------------------------------------------------------------
//  bool isMember(int node)
//
//  Tests if node is a member of the cluster
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    bool isMember(const int& node) const
    {
        return (bool) nodes.count(node);
    }


//------------------------------------------------------------------------------
//  int size()
//
//  Tests if node is a member of the cluster
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    uli size() const
    {
        return nodes.size();
    }


//------------------------------------------------------------------------------
//  void print()
//
//  Prints the cluster
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void print(ostream& buffer) const;


//------------------------------------------------------------------------------
//  Cluster& operator-=(Cluster& clust);
//
//  Increment the iterator
//  Input :
//  Output:
//------------------------------------------------------------------------------
    Cluster& operator-=(Cluster& clust);


//------------------------------------------------------------------------------
//  Cluster& operator-=(vector<int>& array);
//
//  Increment the iterator
//  Input :
//  Output:
//------------------------------------------------------------------------------
    Cluster& operator-=(IntVector& array);


    private:
//------------------------------------------------------------------------------
//
//  void depthFirstSearch(int source)
//
//  depthFirstSearch finds neighbours of all nodes connected to 'source'.
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void depthFirstSearch(const int& source);

}; //end declarations



/******************************************************************************

    header for class: ClusterIterator

    This class forms an iterator for the nodes cluster.

******************************************************************************/
class ClusterIterator
{
    friend class Cluster;

    // Variable(s)
    private:
    IntSet::const_iterator int_iter;
    IntSet::const_iterator int_iter_end;


    // Function(s) declarations
    private:
//------------------------------------------------------------------------------
//
//  constructor ClusterIterator();
//
//  Constructs ClusterIterator for all nodes
//  Input : the cluster list
//  Output:
//------------------------------------------------------------------------------
    ClusterIterator(const IntSet& int_set)
    {
        int_iter = int_set.begin();
        int_iter_end = int_set.end();
    }


    public:
//------------------------------------------------------------------------------
//
//  destructor ~ClusterIterator()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
//    ~ClusterIterator() {}


//------------------------------------------------------------------------------
//  void operator++();
//
//  Increment the iterator
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void operator++()
    {
        ++int_iter;
    }


//------------------------------------------------------------------------------
//  bool operator()();
//
//  Checks if end has been reached of iterator
//  Input :
//  Output: true if more elements
//------------------------------------------------------------------------------
    bool operator()() const
    {
        return (int_iter != int_iter_end);
    }


//------------------------------------------------------------------------------
//  Link* operator*();
//
//  Returns the current item (a node number)
//  Input :
//  Output: int
//------------------------------------------------------------------------------
    int operator*() const
    {
        return (int) *int_iter;
    }
};
#endif //CLUSTER_H
