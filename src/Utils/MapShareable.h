#ifndef MAPSHAREABLE_H
#define MAPSHAREABLE_H
/******************************************************************************

    header file MapShareable.h for class MapShareable.

    This is a class for emulating a map with
    ability to store them in Shared Memory Blocks

    Template class

    Three shm blocks are needed
    - size vector + shmid values
    - keys <KT> array (KT)
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
#include <map>
using std::map;
using std::make_pair;
using Types::uli;


template <typename K, typename T>
class MapShareable : public Shareable, public map<K, T>
{
    // Friends

    // Typedef(s)
    typedef typename map<K, T>::const_iterator const_iterator;

    // Constanst(s)

    // Variable(s)
    private:
    static int smf_K_rc; //reference counter
    static int smf_T_rc; //reference counter

    protected:
    static SharedMemoryFacade<K>* smf_K;
    static SharedMemoryFacade<T>* smf_T;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor MapShareable()
//  Constructs empty MapShareable.
//------------------------------------------------------------------------------
    MapShareable()
    {
        TRACE("MapShareable::MapShareable1 -->")
        // this is first init of SMM
        if (++smf_K_rc == 1) smf_K =  new SharedMemoryFacade<K>();
        if (++smf_T_rc == 1) smf_T =  new SharedMemoryFacade<T>();
        TRACE("MapShareable::MapShareable1 <--")
    }


//------------------------------------------------------------------------------
//  constructor MapShareable()
//  Constructs clone from map
//------------------------------------------------------------------------------
    MapShareable(const map<K, T>& original) : map<K, T>(original)
    {
        TRACE("MapShareable::MapShareable2 -->")
        // this is first init of SMM
        if (++smf_K_rc == 1) smf_K =  new SharedMemoryFacade<K>();
        if (++smf_T_rc == 1) smf_T =  new SharedMemoryFacade<T>();
        TRACE("MapShareable::MapShareable2 <--")
    }


//------------------------------------------------------------------------------
//  destructor ~MapShareable()
//  Destructs MapShareable
//------------------------------------------------------------------------------
    virtual ~MapShareable()
    {
        TRACE("MapShareable::~MapShareable -->")
        if (shmid) releaseShareable();
        if (--smf_K_rc == 0) // no more references
        {
            delete smf_K;
            smf_K = (SharedMemoryFacade<K>*) 0;
        }
        if (--smf_T_rc == 0) // no more references
        {
            delete smf_T;
            smf_T = (SharedMemoryFacade<T>*) 0;
        }
        TRACE("MapShareable::~MapShareable <--")
    }


//------------------------------------------------------------------------------
// void allocateShareable();
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void allocateShareable()
    {
        TRACE("MapShareable::allocateShareable -->")
        shmid = smf_uli->create(3);  // three memory blocks
        TRACE("MapShareable::allocateShareable <--")
    }


//------------------------------------------------------------------------------
// void copyFromShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyFromShareable()
    {
        TRACE("MapShareable::copyFromShareable -->")

        clear();

        // Retrieve shmid's and size
        uli* p = (uli*) smf_uli->attach(shmid);
        uli size_     = (uli) p[0];
        uli id_keys   = (uli) p[1];
        uli id_values = (uli) p[2];
        smf_uli->detach(p);

        // Memory block keys
        K* p_keys   = (K*) smf_K->attach(id_keys);
        T* p_values = (T*) smf_T->attach(id_values);
        for (int counter = 0; counter < size_; ++counter)
        {
            insert(make_pair(p_keys[counter], p_values[counter]));
        }
        smf_T->detach(p_values);
        smf_K->detach(p_keys);

        TRACE("MapShareable::copyFromShareable <--")
    }


//------------------------------------------------------------------------------
// void copyToShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void copyToShareable()
    {
        TRACE("MapShareable::copyToShareable -->")

        int size_     = size();
        int id_keys   = smf_K->create(size_);
        int id_values = smf_T->create(size_);
        //TRACE("s: "<< size <<"\tid_k: " << id_keys <<"\tid_v: " << id_values);

        // Memory block one
        uli* p = (uli*) smf_uli->attach(shmid);
        p[0] = (uli) size_;
        p[1] = (uli) id_keys;
        p[2] = (uli) id_values;
        //TRACE("p[0]: " << p[0] << "\tp[1]: " << p[1] << "\tp[2]: " << p[2]);
        smf_uli->detach(p);

        // Memory block two and three
        int counter = 0;
        K* p_keys   = (K*) smf_K->attach(id_keys);
        T* p_values = (T*) smf_T->attach(id_values);
        for (const_iterator iter = begin(); iter != end(); ++counter, ++iter)
        {
            p_keys[counter]   = iter->first;
            p_values[counter] = iter->second;
        }
        smf_T->detach(p_values);
        smf_K->detach(p_keys);

        TRACE("MapShareable::copyToShareable <--")
    }


//------------------------------------------------------------------------------
// void releaseShareable()
//
// See superclass for derails
//
//------------------------------------------------------------------------------
    void releaseShareable()
    {
        TRACE("MapShareable::releaseShareable -->")

        // Retrieve shmid's
        uli* p = (uli*) smf_uli->attach(shmid);
        uli id_keys   = (uli) p[1];
        uli id_values = (uli) p[2];
        smf_uli->detach(p);

        // Memory block two and three
        smf_T->destroy(id_values);
        smf_K->destroy(id_keys);
        smf_uli->destroy(shmid);
        shmid = 0;

        TRACE("MapShareable::releaseShareable <--")
    }


//------------------------------------------------------------------------------
//  Copies the contents from another map
//------------------------------------------------------------------------------
    MapShareable<K, T>& operator=(const map<K, T>& original)
    {
        TRACE("MapShareable::operator= -->")
        *((map<K, T>*) this) = original;
        TRACE("MapShareable::operator= <--")
        return *this;
    }

}; //end declarations MapShareable

template <typename K, typename T>
int MapShareable<K, T>::smf_K_rc = 0;

template <typename K, typename T>
int MapShareable<K, T>::smf_T_rc = 0;

template <typename K, typename T>
SharedMemoryFacade<K>* MapShareable<K, T>::smf_K = (SharedMemoryFacade<K>*)0;

template <typename K, typename T>
SharedMemoryFacade<T>* MapShareable<K, T>::smf_T = (SharedMemoryFacade<T>*)0;

#endif //MAPSHAREABLE_H
