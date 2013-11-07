#ifndef SHAREABLE_H
#define SHAREABLE_H
/******************************************************************************

    header file Shareable.h for class Shareable.

    This is the interface that must be implemented by classes/structs
    that support SharedMemoryBlocks

    No logging

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/


/******************************************************************************
  |========|      |===============|
  | shmid  | ---> | size_array_1  |
  |========|      |===============|
                  | atart_array_1 |
                  |===============|
                  | ...           |
                  |===============|
                  | int x         |
                  |===============|
                  | ...           |
                  |===============|
******************************************************************************/


// Include(s)
#include "Utils/SharedMemoryFacade.h"
#include "Utils/Types.h"
using Types::uli;


// Class Definition
class Shareable
{
    // Friends

    // Constanst(s)

    // Variable(s)
    private:
    static int smf_uli_rc;  // reference counter

    protected:
    static SharedMemoryFacade<uli>* smf_uli;
    uli shmid;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor Shareable()
//  Constructs empty Shareable.
//------------------------------------------------------------------------------
    Shareable()
    {
        TRACE("Shareable::Shareable -->")
        shmid = 0;
        // this is first init of SMM
        if (++smf_uli_rc == 1) smf_uli =  new SharedMemoryFacade<uli>();
        TRACE("Shareable::Shareable <--")
   }


//------------------------------------------------------------------------------
//  destructor ~Shareable()
//  Destructs Shareable
//------------------------------------------------------------------------------
    ~Shareable()
    {
        TRACE("Shareable::~Shareable -->")
        if (--smf_uli_rc == 0) // no more references
        {
            delete smf_uli;
            smf_uli = (SharedMemoryFacade<uli>*) 0;
        }
        TRACE("Shareable::~Shareable <--")
    }

//------------------------------------------------------------------------------
// virtual void allocateShareable() = 0;
//
// Allocate the Shared Memory Block
//
//------------------------------------------------------------------------------
    virtual void allocateShareable() = 0;


//------------------------------------------------------------------------------
// virtual void copyFromShareable() = 0;
//
// Copy from the Shared Memory Block
//
//------------------------------------------------------------------------------
    virtual void copyFromShareable() = 0;


//------------------------------------------------------------------------------
// virtual void copyToShareable() = 0;
//
// Copy to the Shared Memory Block
//
//------------------------------------------------------------------------------
    virtual void copyToShareable() = 0;


//------------------------------------------------------------------------------
// virtual void releaseShareable() = 0;
//
// Release/Destroy the Shared Memory Block
//
//------------------------------------------------------------------------------
    virtual void releaseShareable() = 0;

}; //end declarations Shareable

    int Shareable::smf_uli_rc;  // reference counter
    SharedMemoryFacade<uli>* Shareable::smf_uli;

#endif //SHAREABLE_H
