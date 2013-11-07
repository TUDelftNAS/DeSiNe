#ifndef DISTRIBUTEDVARIABLESHAREABLE_H
#define DISTRIBUTEDVARIABLESHAREABLE_H
/******************************************************************************

    header file DistributedVariableShareable.h for class
    DistributedVariableShareable.

    This is a class for emulating a discrete distributed variable with
    ability to store them in Shared Memory Blocks. It uses MapShareable
    to store the distribution in the shared memory blocks.

    It has no (primitive) member variables, so no extra memory blocks
    need to be created (shmid remains unused).

    Template class

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/


// Include(s)
#include "Utils/DistributedVariable.h"
#include "Utils/MapShareable.h"
#include "Utils/Shareable.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
using Types::uli;


template <typename T>
class DistributedVariableShareable : public DistributedVariable<T>, public Shareable
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
    typedef MapShareable<T, uli> CollMapS;
    bool shareable;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor DistributedVariableShareable()
//  Constructs empty DistributedVariableShareable.
//------------------------------------------------------------------------------
    DistributedVariableShareable()
    {
        TRACE("DistributedVariableShareable::DistributedVariableShareable -->")
        shareable = false;
        TRACE("DistributedVariableShareable::DistributedVariableShareable <--")
    }


//------------------------------------------------------------------------------
//  constructor DistributedVariableShareable()
//  Constructs empty DistributedVariableShareable.
//------------------------------------------------------------------------------
    DistributedVariableShareable(const DistributedVariable<T>& original) :
        DistributedVariable<T>(original)
    {
        TRACE("DistributedVariableShareable::DistributedVariableShareable -->")
        shareable = false;
        TRACE("DistributedVariableShareable::DistributedVariableShareable <--")
    }


//------------------------------------------------------------------------------
//  destructor ~DistributedVariableShareable()
//  Destructs DistributedVariableShareable
//------------------------------------------------------------------------------
    ~DistributedVariableShareable()
    {
        TRACE("DistributedVariableShareable::~DistributedVariableShareable -->")
        if (collection && shareable) delete (CollMapS*) collection;
        TRACE("DistributedVariableShareable::~DistributedVariableShareable <--")
    }


//------------------------------------------------------------------------------
// void allocateShareable();
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void allocateShareable()
    {
        TRACE("DistributedVariableShareable::allocateShareable -->")
        // Replace colllection by MapShareable
        CollMapS* collectionS = new CollMapS(*collection);
        if (shareable)
        {
            delete (CollMapS*) collection;
        }
        else
        {
            delete collection;
        }
        collection = collectionS;
        ((CollMapS*) collection)->allocateShareable();
        shareable = true;
        TRACE("DistributedVariableShareable::allocateShareable <--")
    }


//------------------------------------------------------------------------------
// void copyFromShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyFromShareable()
    {
        TRACE("DistributedVariableShareable::copyFromShareable -->")
        ((CollMapS*) collection)->copyFromShareable();
        TRACE("DistributedVariableShareable::copyFromShareable <--")
    }


//------------------------------------------------------------------------------
// void copyToShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyToShareable()
    {
        TRACE("DistributedVariableShareable::copyToShareable -->")
        ((CollMapS*) collection)->copyToShareable();
        TRACE("DistributedVariableShareable::copyToShareable <--")
    }


//------------------------------------------------------------------------------
// void releaseShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void releaseShareable()
    {
        TRACE("DistributedVariableShareable::releaseShareable -->")
        ((CollMapS*) collection)->releaseShareable();
        TRACE("DistributedVariableShareable::releaseShareable <--")
    }


//------------------------------------------------------------------------------
//  VectorShareable<T>& operator=(const vector<T>& original)
//
//  Copies the contents from another vector
//------------------------------------------------------------------------------
    DistributedVariableShareable<T>& operator=(
        const DistributedVariable<T>& original)
    {
        TRACE("DistributedVariableShareable::operator= -->")
        *((DistributedVariable<T>*) this) = original;
        TRACE("DistributedVariableShareable::operator= <--")
        return *this;
    }

}; //end declarations DistributedVariableShareable

#endif //DISTRIBUTEDVARIABLESHAREABLE_H
