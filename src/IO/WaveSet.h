#ifndef WAVESET_H
#define WAVESET_H
/******************************************************************************

    header file WaveSet.h for class: WaveSet

    This template class forms a set of waves. A wave is a dataset with a given
    name. The set of waves is also named.

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"
#include <map>
#include <string>
#include <vector>
//using std::make_pair;
using std::map;
using std::string;
using std::vector;

template <typename T>
class WaveSet
{
    // Typedefs
    public:
    typedef vector<T> WaveVector;

    protected:
    typedef map<string, WaveVector> WaveMap;
    typedef typename WaveMap::const_iterator WaveMapConstIterator;

    // Nested classes
    public:
    class Iterator;

    // Constanst(s)


    // Variable(s)
    private:
    string name;
    WaveMap waveset;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor WaveSet()
//  Constructs WaveSet
//  Input :
//------------------------------------------------------------------------------
    WaveSet(const string name) : name(name)
    {
        TRACE("WaveSet::WaveSet -->");
        //Empty!!
        TRACE("WaveSet::WaveSet <--");
    }


//------------------------------------------------------------------------------
//  destructor ~WaveSet()
//  Destructs WaveSet
//  Input :
//  Output:
//------------------------------------------------------------------------------
    ~WaveSet()
    {
        TRACE("WaveSet::~WaveSet -->");
        //Empty!!
        TRACE("WaveSet::~WaveSet <--");
    }


//------------------------------------------------------------------------------
//  void insert();
//
//  gets the name.
//------------------------------------------------------------------------------
    string getName() const
    {
        TRACE("WaveSet::getName -->")
        TRACE("WaveSet::getName <--")
        return name;
    }


//------------------------------------------------------------------------------
//  Iterator getWaves();
//
//  Returns an iterator to the waves
//------------------------------------------------------------------------------
    Iterator getWaves() const
    {
        TRACE("WaveSet::getWaves -->")
        Iterator result(waveset);
        TRACE("WaveSet::getWaves <--")
        return result;
    }


//------------------------------------------------------------------------------
//  void insert();
//
//  Insert a wave in the set.
//------------------------------------------------------------------------------
    void insert(const string wavename, const WaveVector &wavedata)
    {
        TRACE("WaveSet::insert -->")
        waveset[wavename] = wavedata;
        TRACE("WaveSet::insert <--")
    }


//------------------------------------------------------------------------------
//  unsigned long size()
//
//  gets the size of the set (#waves)
//------------------------------------------------------------------------------
    unsigned long size() const
    {
        TRACE("WaveSet::size -->")
        TRACE("WaveSet::size <--")
        return waveset.size();
    }


   /**************************************************************************

        source WaveSetIterator for class WaveSetIterator.

        This is a class for iterating through the waves

        Author : T. Kleiberg
        Version: 1
        Date   : Feb 2005

    **************************************************************************/
    public:
    class Iterator
    {
        // Friends
        friend class WaveSet<T>;

        // Variable(s)
        private:
        typedef typename WaveSet<T>::WaveVector WaveVector;
        typedef typename WaveSet<T>::WaveMap WaveMap;
        typedef typename WaveMap::const_iterator WaveMapConstIterator;

        WaveMapConstIterator iter;
        WaveMapConstIterator iter_end;

        // Function(s) declarations
        private:
    //--------------------------------------------------------------------------
    //
    //  constructor WaveSetIterator(IntIntLinkMap* linkmap);
    //
    //  Constructs WaveSetIterator for all links
    //  Input : the link list
    //  Output:
    //--------------------------------------------------------------------------
        Iterator(const WaveMap& waves)
        {
            TRACE("WaveSet::Iterator::Iterator -->")
            iter     = waves.begin();
            iter_end = waves.end();
            TRACE("WaveSet::Iterator::Iterator <--")
        }

        public:
    //--------------------------------------------------------------------------
    //
    //  destructor ~WaveSetIterator()
    //  Input :
    //  Output:
    //
    //--------------------------------------------------------------------------
        ~Iterator()
        {
            TRACE("WaveSet::Iterator::~Iterator -->")
            //Empty!!
            TRACE("WaveSet::Iterator::~Iterator <--")
        }

    //--------------------------------------------------------------------------
    //  void operator++();
    //
    //  Increment the iterator
    //  Input :
    //  Output:
    //--------------------------------------------------------------------------
        void operator++()
        {
            ++iter;
        }


    //--------------------------------------------------------------------------
    //  bool operator()();
    //
    //  Checks if end has been reached of iterator
    //  Input :
    //  Output: false if no more elements
    //--------------------------------------------------------------------------
        bool operator()()
        {
            return (iter != iter_end);
        }


    //--------------------------------------------------------------------------
    //  string getName()
    //
    //  Returns the wave name
    //--------------------------------------------------------------------------
        string getName() const
        {
            return iter->first;
        }


    //--------------------------------------------------------------------------
    //  const WaveVector& getWaveVector()
    //
    //  Returns the wave data
    //--------------------------------------------------------------------------
        const WaveVector& getWaveVector() const
        {
            return iter->second;
        }
    }; // end: Iterator

}; //end declarations WaveSet
#endif // WAVESET_H
