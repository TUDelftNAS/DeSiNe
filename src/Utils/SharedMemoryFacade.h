#ifndef SHAREDMEMORYFACADE_H
#define SHAREDMEMORYFACADE_H
/******************************************************************************

    header file SharedMemoryFacade.h for class SharedMemoryFacade.

    This is a facade class for creating and destroying shared memeory blocks.
    Note: this class has no protection for destroying obsolete blocks.

    Template class

    Reduced logging

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"
//#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>


// Octal 666, permissions for shared memory blocks
#define PERMS 438


template <typename T>
class SharedMemoryFacade
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor SharedMemoryFacade()
//  Constructs empty SharedMemoryFacade.
//------------------------------------------------------------------------------
//    SharedMemoryFacade()
//    {
//        TRACE("SharedMemoryFacade::SharedMemoryFacade -->");
//        TRACE("SharedMemoryFacade::SharedMemoryFacade <--");
//    }


//------------------------------------------------------------------------------
//  destructor ~SharedMemoryFacade()
//  Destructs SharedMemoryFacade
//------------------------------------------------------------------------------
//    ~SharedMemoryFacade()
//    {
//        TRACE("SharedMemoryFacade::~SharedMemoryFacade -->");
//        TRACE("SharedMemoryFacade::~SharedMemoryFacade <--");
//    }



//------------------------------------------------------------------------------
// T* attach(int id)
//
// Attach shm to an id
//
//------------------------------------------------------------------------------
    T* attach(int shmid)
    {
        TRACE("SharedMemoryFacade::attach: memory block " << shmid);
        T* result = (T*) shmat(shmid, 0, 0);
        if ((T*) result < (T*) 0)
        {
            ERROR("ERROR: attaching to memory block " << shmid);
        }
        return result;
    }


//------------------------------------------------------------------------------
// int create()
//
// Create a new memory block, only possible by class that instantiated
// SharedMemoryFacade. Count is the number of 'sizeof' blocks to reserve.
//
//------------------------------------------------------------------------------
    int create(int count)
    {
        // Removed restriction for childprocess to create memory blocks!!
        // Be aware to always remove those shm too!!
        int result = shmget((key_t) IPC_PRIVATE, count * sizeof(T),
                     PERMS | IPC_CREAT);
        if (result < 0)
        {
            ERROR("ERROR: creating memory block");
        }
        TRACE("SharedMemoryFacade::create: memory block " << result);
        return result;
    }


//------------------------------------------------------------------------------
// void destroy(int shmid)
//
// Destroy single shared memory block, can only be called by creating class
//
//------------------------------------------------------------------------------
    void destroy(int shmid)
    {
        // Removed restriction for childprocess to destroy memory blocks!!
        // Be aware to always remove shm correctly!!
        if (shmctl(shmid, IPC_RMID, 0) < 0)
        {
            ERROR("ERROR: removing memory block " << shmid);
        }
        TRACE("SharedMemoryFacade::destroy: memory block " << shmid);
    }


//------------------------------------------------------------------------------
// void detach(T* shmptr)
//
// Detach from shmptr
//
//------------------------------------------------------------------------------
    void detach(T* shmptr)
    {
        TRACE("SharedMemoryFacade::detach: memory block.");
        if (shmdt(shmptr) < 0)
        {
            ERROR("ERROR: detaching memory block");
        }
    }

}; //end declarations
#endif //SHAREDMEMORYFACADE_H
