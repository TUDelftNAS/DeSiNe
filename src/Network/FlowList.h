#ifndef FLOWLIST_H
#define FLOWLIST_H
/******************************************************************************

    header file FlowList.h for class: FlowList

    This class manages all flows that run in the network. It both creates and
    desctructs them.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Network/Flow.h"
#include "Utils/Time.h"
#include "Utils/Types.h"
#include <map>
#include <ostream>
using std::multimap;
using std::ostream;
using Types::uli;

class FlowList
{
    // Declare nested class
    public:
    class Iterator;

    // Friends
    friend class FlowManager;

    // Typedef(s)
    private:
    typedef multimap<double, Flow> FlowMap;

    // Variable(s)
    private:
    // Flows are stored in a multimap. The Tend values are used as 'key' so that
    // the (multi)map automatically stores the flows in the correct order
    FlowMap flow_map;
    double throughput;
    Time* time;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor FlowList();
//
//  Constructs FlowList
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    FlowList();


//------------------------------------------------------------------------------
//
//  destructor ~FlowList()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~FlowList();


//------------------------------------------------------------------------------
//  void accept(Flow* flow)
//
//  Accept a flow when it is accepted by the topology. It is then added to the
//  list and the counter for the accepted dlows is incremented
//
//  Input : the accepted flow
//  Output:
//------------------------------------------------------------------------------
    void accept(const Flow &flow);


//------------------------------------------------------------------------------
//  Iterator iterator()
//
//  Returns iterator for all flows
//------------------------------------------------------------------------------
    Iterator getIterator() const;


//------------------------------------------------------------------------------
//  double getThroughput()
//
//  Returns throughput
//------------------------------------------------------------------------------
    double getThroughput()  const
    {
        return throughput;
    }


//------------------------------------------------------------------------------
//  void print(ostream &buffer);
//
//  Prints flowlist to the buffer
//
//  Input : LogManagerID
//  Output:
//------------------------------------------------------------------------------
    void print(ostream &buffer) const;


//------------------------------------------------------------------------------
//  int size();
//
//  Returns size of the flowlist (number of flows in the network)
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    uli size() const
    {
        return flow_map.size();
    }


//------------------------------------------------------------------------------
//  void setTime(Time t)
//------------------------------------------------------------------------------
    void setTime(Time* t)
    {
        TRACE("FlowList::setTime-->");
        time = t;
        TRACE("FlowList::setTime<--");
    }


//------------------------------------------------------------------------------
//  void update(double global_time)
//
//  Update the flow lists: chech if flows are expired and if so, remove them.
//
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void update(const double &global_time);


    /**************************************************************************

        header for class: Iterator

        This class forms an iterator for the flow list.

        No tracing performed in this class

    **************************************************************************/
    public:
    class Iterator
    {
        friend class FlowList;
        private:
        // Typedef(s)
        //typedef FlowMap::const_iterator FlowMapIter;

        // Variable(s)
        FlowMap::const_iterator flow_iter;
        FlowMap::const_iterator flow_iter_end;

        // Function(s) declarations
        private:
    //--------------------------------------------------------------------------
    //
    //  constructor Iterator(multimap<double, Flow*>* flowmap)
    //
    //  Constructs Iterator for all flows
    //  Input : the link list
    //  Output:
    //--------------------------------------------------------------------------
        Iterator(const FlowMap &flowmap)
        {
            flow_iter = flowmap.begin();
            flow_iter_end = flowmap.end();
        }


        public:
    //--------------------------------------------------------------------------
    //
    //  destructor ~Iterator()
    //  Input :
    //  Output:
    //
    //--------------------------------------------------------------------------
        ~Iterator() {}


    //--------------------------------------------------------------------------
    //  void operator++();
    //
    //  Increment the iterator
    //  Input :
    //  Output:
    //--------------------------------------------------------------------------
        void operator++()
        {
            ++flow_iter;
        }


    //--------------------------------------------------------------------------
    //  bool operator()();
    //
    //  Checks if end has been reached of iterator
    //  Input :
    //  Output: true if more elements
    //--------------------------------------------------------------------------
        bool operator()() const
        {
            return flow_iter != flow_iter_end;
        }


    //--------------------------------------------------------------------------
    //  Link* operator*();
    //
    //  Returns the actual element (the Link)
    //  Input :
    //  Output: the link
    //--------------------------------------------------------------------------
        const Flow& operator*() const
        {
            return flow_iter->second;
        }
    }; //end declarations Iterator
}; //end declarations FlowList

#endif //FLOWLIST_H
