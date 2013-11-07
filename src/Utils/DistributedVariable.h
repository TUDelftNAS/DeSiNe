#ifndef DISTRIBUTEDVARIABLE_H
#define DISTRIBUTEDVARIABLE_H
/******************************************************************************

    header file DistributedVariable.h for class DistributedVariable.

    This is a class for emulating a discrete distributed variable

    Template class

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"
#include <cfloat>
#include <iostream>
#include <map>
using std::endl;
using std::ostream;
using std::map;

template <typename T>
class DistributedVariable
{
    //Typedefs (cannot use Types due to mutual dependency
    private:
    typedef unsigned long int uli;
    typedef unsigned long long ull;
    typedef long double ldouble;
    typedef map<T, uli> CollMap;
    typedef typename CollMap::const_iterator CollMapConstIterator;

    // Nested classes
    public:
    class Iterator;

    // Friends
    //friend class DistributedVariableIterator<T>;

    // Constanst(s)

    // Variable(s)
    private:
    CollMap collection;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor DistributedVariable()
//  Constructs empty DistributedVariable.
//------------------------------------------------------------------------------
    DistributedVariable()
    {
        //TRACE("DistributedVariable::DistributedVariable -->")
        //TRACE("DistributedVariable::DistributedVariable <--")
    }


//------------------------------------------------------------------------------
//  destructor ~DistributedVariable()
//  Destructs DistributedVariable
//------------------------------------------------------------------------------
    virtual ~DistributedVariable()
    {
        //TRACE("DistributedVariable::~DistributedVariable -->")
        //TRACE("DistributedVariable::~DistributedVariable <--")
    }


//------------------------------------------------------------------------------
//  Add a new element to the distribution
//------------------------------------------------------------------------------
    void add(const T &var)
    {
        collection[var]++;
    }


//------------------------------------------------------------------------------
//  Return the probability density function
//------------------------------------------------------------------------------
    Iterator getPDF() const
    {
        TRACE("DistributedVariable::getPDF -->")
        Iterator result(collection, getSize());
        TRACE("DistributedVariable::getPDF <--")
        return result;
    }


//------------------------------------------------------------------------------
//  Return the mean
//------------------------------------------------------------------------------
    ldouble getMean() const
    {
        //PRINTLN("sizeof(collection)" << sizeof(collection) << "\tcollection.size()" << collection.size());
        TRACE("DistributedVariable::getMean -->")
        ldouble result = 0.0;
        if (!collection.empty())
        {
            ldouble mean  = 0.0;
            ull n         = 0;
            for (CollMapConstIterator iter = collection.begin();
                 iter != collection.end(); ++iter)
            {
                mean += iter->first * iter->second; // value * occurance
                n    += iter->second;
            }
            result = (ldouble) mean/n;
        }
        TRACE("DistributedVariable::getMean <--")
        return result;
    }


//------------------------------------------------------------------------------
//  Return the variance
//------------------------------------------------------------------------------
    ldouble getVariance() const
    {
        TRACE("DistributedVariable::getVariance -->")
        ldouble result = 0.0;
        if (!collection.empty())
        {
            ldouble sumsq = 0.0;
            ldouble mean  = 0.0;
            ull n         = 0;

            for (CollMapConstIterator iter = collection.begin();
                 iter != collection.end(); ++iter)
            {
                mean  += iter->first * iter->second; // value * occurance
                sumsq += iter->first * iter->first * iter->second; // value^2 * occurance
                n     += iter->second;
            }
            result = (sumsq - mean * mean/n)/n;
        }
        TRACE("DistributedVariable::getVariance <--")
        return result;
    }


//------------------------------------------------------------------------------
//  Return the size (number of samples)
//------------------------------------------------------------------------------
    ull getSize() const
    {
        TRACE("DistributedVariable::getSize -->")
        ull result = 0;
        if (!collection.empty())
        {
            for (CollMapConstIterator iter = collection.begin();
                 iter != collection.end(); ++iter)
            {
                result += iter->second;
            }
        }
        TRACE("DistributedVariable::getSize <--")
        return result;
    }


//------------------------------------------------------------------------------
//  void print(ostream& buffer);
//------------------------------------------------------------------------------
    void print(ostream& buffer) const
    {
        if (!collection.empty())
        {
            for (CollMapConstIterator iter = collection.begin();
                 iter != collection.end(); ++iter)
            {
                buffer << "[" << iter->first << "] " << iter->second << endl;
            }
        }
    }


//------------------------------------------------------------------------------
//  DistributedVariable<T>& operator+=(const DistributedVariable<T>& original)
//
//  Add a DistributedVariable to the distribution
//------------------------------------------------------------------------------
    DistributedVariable<T>& operator+=(const DistributedVariable<T>& original)
    {
        TRACE("DistributedVariable::operator+= -->")
        if (!original.collection.empty())
        {
            for (CollMapConstIterator iter = original.collection.begin();
                 iter != original.collection.end(); ++iter)
            {
                collection[iter->first] += iter->second;
            }
        }
        TRACE("DistributedVariable::operator+= <--")
        return *this;
    }


    /**************************************************************************

        source DistributedVariableIterator for class DistributedVariableIterator.

        This is a class for iterating through Distributed Variable (PDF)

        No logging

        Author : T. Kleiberg
        Version: 1
        Date   : Oct 2004

    **************************************************************************/
    class Iterator
    {
        // Friends
        friend class DistributedVariable<T>;

        // Variable(s)
        private:
        typedef typename DistributedVariable<T>::CollMap CollMap;
        typedef typename CollMap::const_iterator CollMapConstIterator;

        double inv_elements;
        CollMapConstIterator iter;
        CollMapConstIterator iter_end;

        // Function(s) declarations
        private:
    //--------------------------------------------------------------------------
    //
    //  constructor DistributedVariableIterator(IntIntLinkMap* linkmap);
    //
    //  Constructs DistributedVariableIterator for all links
    //  Input : the link list
    //
    //--------------------------------------------------------------------------
        Iterator(const CollMap &collection, uli elements)
        {
            TRACE("DistributedVariable::Iterator::Iterator -->")
            iter     = collection.begin();
            iter_end = collection.end();
            inv_elements = elements ? (double) 1.0/elements : DBL_MAX;
            TRACE("DistributedVariable::Iterator::Iterator <--")
        }

        public:
    //--------------------------------------------------------------------------
    //
    //  destructor ~DistributedVariableIterator()
    //
    //--------------------------------------------------------------------------
        ~Iterator()
        {
            TRACE("DistributedVariable::Iterator::~Iterator -->")
            TRACE("DistributedVariable::Iterator::~Iterator <--")
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
        bool operator()() const
        {
            return (iter != iter_end);
        }


    //--------------------------------------------------------------------------
    //  T first()
    //
    //  Returns the value
    //--------------------------------------------------------------------------
        T first() const
        {
            return iter->first;
        }


    //--------------------------------------------------------------------------
    //  T second()
    //
    //  Returns the occurance
    //--------------------------------------------------------------------------
        double second() const
        {
            return iter->second * inv_elements;
        }

    }; // end: Iterator
}; //end DistributedVariable
#endif //DISTRIBUTEDVARIABLE_H
