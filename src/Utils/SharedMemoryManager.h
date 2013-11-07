#ifndef SHAREDMEMORYMANAGER_H
#define SHAREDMEMORYMANAGER_H
/******************************************************************************

    header file SharedMemoryManager.h for class SharedMemoryManager.

    This is a class for managing shared memeory blocks. It uses
    SharedMemoryFacade and adds some protection so that only parent process
    can create and destroy smb. It also cleans up all smb on destruction.

    Template class

    Reduced logging

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "Utils/SharedMemoryFacade.h"
#include "Utils/TraceManager.h"
#include <unistd.h>
#include <set>
using std::set;


// Iterator class
class SharedMemoryIterator;

template <typename T>
class SharedMemoryManager
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
    pid_t pid;
    set<int> idset;
    SharedMemoryFacade<T>* smf;



    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor SharedMemoryManager()
//  Constructs empty SharedMemoryManager.
//------------------------------------------------------------------------------
    SharedMemoryManager()
    {
        TRACE("SharedMemoryManager::SharedMemoryManager -->");
        pid = getpid();
        smf = new SharedMemoryFacade<T>();
        TRACE("SharedMemoryManager::SharedMemoryManager <--");
    }


//------------------------------------------------------------------------------
//  destructor ~SharedMemoryManager()
//  Destructs SharedMemoryManager
//------------------------------------------------------------------------------
    ~SharedMemoryManager()
    {
        TRACE("SharedMemoryManager::~SharedMemoryManager -->");
        destroy();
        if (smf) delete smf;
        TRACE("SharedMemoryManager::~SharedMemoryManager <--");
    }



//------------------------------------------------------------------------------
// T* attach(int id)
//
// Attach shm to an id
//
//------------------------------------------------------------------------------
    T* attach(int shmid)
    {
        return (T*) smf->attach(shmid);
    }


//------------------------------------------------------------------------------
// int create()
//
// Create a new memory block, only possible by class that instantiated
// SharedMemoryManager. Count is the number of 'sizeof' blocks to reserve.
//
//------------------------------------------------------------------------------
    int create(int count)
    {
        int result = -1;
        if (getpid() == pid)
        {
            result = smf->create(count);
            if (result < 0)
            {
                ERROR("SharedMemoryManager::create: Error: Memory block creation failed.");
            }
            else
            {
                TRACE("SharedMemoryManager::create: created memory block: " << result);
                idset.insert(result);
            }
        }
        return result;
    }



//------------------------------------------------------------------------------
// void destroy()
//
// Destroy all shared memory block, can only be called by creating class
//
//------------------------------------------------------------------------------
    void destroy()
    {
        if (getpid() == pid)
        {
            for (set<int>::const_iterator iter = idset.begin();
                 iter != idset.end(); ++iter)
            {
                smf->destroy(*iter);
            }
            idset.clear();
        }
    }


//------------------------------------------------------------------------------
// void destroy(int shmid)
//
// Destroy single shared memory block, can only be called by creating class
//
//------------------------------------------------------------------------------
    void destroy(int shmid)
    {
        if (getpid() == pid && idset.count(shmid))
        {
            smf->destroy(shmid);
            idset.erase(shmid);
        }
    }


//------------------------------------------------------------------------------
// void detach(T* shmptr)
//
// Detach from shmptr
//
//------------------------------------------------------------------------------
    void detach(T* shmptr)
    {
        smf->detach(shmptr);
    }



//------------------------------------------------------------------------------
// SharedMemoryIterator getIterator()
//
// Returns an iterator for the IDs of shared memeory blocks
//
//------------------------------------------------------------------------------
    SharedMemoryIterator getIterator()
    {
//        cout << "### " << idset.size() << " ## ";
//        cout << (idset.begin() != idset.end()) << "\n";
        return SharedMemoryIterator(idset);
    }
}; //end declarations



/******************************************************************************

    source SharedMemoryIterator for class SharedMemeoryIterator.

    This is a class for iterating through shared memeory block IDs

    No logging

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


class SharedMemoryIterator
{
    // Variable(s)
    private:
    set<int>::const_iterator iter;
    set<int>::const_iterator iter_end;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor SharedMemoryIterator(IntIntLinkMap* linkmap);
//
//  Constructs SharedMemoryIterator for all links
//  Input : the link list
//  Output:
//------------------------------------------------------------------------------
    SharedMemoryIterator(set<int> &idlist)
    {
        iter = idlist.begin();
        iter_end = idlist.end();
    }


//------------------------------------------------------------------------------
//
//  destructor ~SharedMemoryIterator()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
//    ~SharedMemoryIterator() {}


//------------------------------------------------------------------------------
//  void operator++();
//
//  Increment the iterator
//  Input :
//  Output:
//------------------------------------------------------------------------------
    void operator++()
    {
        ++iter;
    }


//------------------------------------------------------------------------------
//  bool operator()();
//
//  Checks if end has been reached of iterator
//  Input :
//  Output: false if no more elements
//------------------------------------------------------------------------------
    bool operator()()
    {
        return iter != iter_end;
    }


//------------------------------------------------------------------------------
//  Link* operator*();
//
//  Returns the actual element
//  Output: ID
//------------------------------------------------------------------------------
    int operator*()
    {
        return *iter;
    }
}; //end declarations SharedMemoryIterator

#endif //SHAREDMEMORYMANAGER_H
