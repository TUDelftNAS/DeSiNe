#ifndef VECTORSHAREABLE_H
#define VECTORSHAREABLE_H
/******************************************************************************

    header file VectorShareable.h for class VectorShareable.

    This is a class for emulating a vector with
    ability to store them in Shared Memory Blocks

    Template class

    Two shm blocks are needed
    - size vector + shmid values
    - values <T> array (T)

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/


// Include(s)
#include "Utils/Shareable.h"
#include "Utils/SharedMemoryFacade.h"
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
#include <vector>
using std::vector;
using Types::uli;


template <typename T>
class VectorShareable : public Shareable, public vector<T>
{
    // Friends

    // Typedef(s)
    typedef typename vector<T>::const_iterator const_iterator;

    // Constanst(s)

    // Variable(s)
    private:
    static int smf_T_rc; //reference counter

    protected:
    static SharedMemoryFacade<T>* smf_T;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor VectorShareable()
//  Constructs empty VectorShareable.
//------------------------------------------------------------------------------
    VectorShareable()
    {
        TRACE("VectorShareable::VectorShareable1 -->")
        // this is first init of SMM
        if (++smf_T_rc == 1) smf_T =  new SharedMemoryFacade<T>();
        TRACE("VectorShareable::VectorShareable1 <--")
    }


//------------------------------------------------------------------------------
//  constructor VectorShareable()
//  Constructs empty VectorShareable.
//------------------------------------------------------------------------------
    VectorShareable(const vector<T>& original) : vector<T>(original)
    {
        TRACE("VectorShareable::VectorShareable2 -->")
        // this is first init of SMM
        if (++smf_T_rc == 1) smf_T =  new SharedMemoryFacade<T>();
        TRACE("VectorShareable::VectorShareable2 <--")
    }


//------------------------------------------------------------------------------
//  destructor ~VectorShareable()
//  Destructs VectorShareable
//------------------------------------------------------------------------------
    ~VectorShareable()
    {
        TRACE("VectorShareable::~VectorShareable -->")
        if (shmid) releaseShareable();
        if (--smf_T_rc == 0) // no more references
        {
            delete smf_T;
            smf_T = (SharedMemoryFacade<T>*) 0;
        }
        TRACE("VectorShareable::~VectorShareable <--")
    }

//------------------------------------------------------------------------------
// void allocateShareable();
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void allocateShareable()
    {
        TRACE("VectorShareable::allocateShareable -->")
        shmid = smf_uli->create(2); // two memory blocks
        TRACE("VectorShareable::allocateShareable <--")
    }


//------------------------------------------------------------------------------
// void copyFromShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyFromShareable()
    {
        TRACE("VectorShareable::copyFromShareable -->")

        clear();

        // Retrieve shmid's and size
        uli* p = (uli*) smf_uli->attach(shmid);
        uli size_     = (uli) p[0];
        uli id_values = (uli) p[1];
        smf_uli->detach(p);

        // Memory block values
        T* p_values = (T*) smf_T->attach(id_values);
        for (int counter = 0; counter < size_; ++counter)
        {
            push_back(p_values[counter]);
        }
        smf_T->detach(p_values);

        TRACE("VectorShareable::copyFromShareable <--")
    }


//------------------------------------------------------------------------------
// void copyToShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyToShareable()
    {
        TRACE("VectorShareable::copyToShareable -->")

        int size_ = size();
        int id_values = smf_T->create(size_);
        //TRACE("size: " << size << "\tid_values: " << id_values);

        // Memory block one
        uli* p = (uli*) smf_uli->attach(shmid);
        p[0] = (uli) size_;
        p[1] = (uli) id_values;
        //TRACE("p[0]: " << p[0] << "\tp[1]: " << p[1]);
        smf_uli->detach(p);

        // Memory block two and three
        int counter = 0;
        T* p_values = (T*) smf_T->attach(id_values);
        for (const_iterator iter = begin(); iter != end(); ++counter, ++iter)
        {
            p_values[counter] = *iter;
        }
        smf_T->detach(p_values);

        TRACE("VectorShareable::copyToShareable <--")
    }


//------------------------------------------------------------------------------
// void releaseShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void releaseShareable()
    {
        TRACE("VectorShareable::releaseShareable -->")

        // Retrieve shmid's
        uli* p = (uli*) smf_uli->attach(shmid);
        uli id_values = (uli) p[1];
        smf_uli->detach(p);

        // Memory block two and three
        smf_T->destroy(id_values);
        smf_uli->destroy(shmid);
        shmid = 0;

        TRACE("VectorShareable::releaseShareable <--")
    }


//------------------------------------------------------------------------------
//  VectorShareable<T>& operator=(const vector<T>& original)
//
//  Copies the contents from another vector
//------------------------------------------------------------------------------
    VectorShareable<T>& operator=(const vector<T>& original)
    {
        TRACE("VectorShareable::operator= -->")
        *((vector<T>*) this) = original;
        TRACE("VectorShareable::operator= <--")
        return *this;
    }

}; //end declarations VectorShareable

template <typename T>
int VectorShareable<T>::smf_T_rc = 0;

template <typename T>
SharedMemoryFacade<T>* VectorShareable<T>::smf_T = (SharedMemoryFacade<T>*)0;

#endif //VECTORSHAREABLE_H
