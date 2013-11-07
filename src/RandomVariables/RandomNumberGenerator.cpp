/******************************************************************************

    source file RandomNumberGenerator.cpp for class: RandomNumberGenerator

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/



// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "Utils/TraceManager.h"
#include <ctime>


// Constanst(s)
#ifdef USE_RAN4

const uli RandomNumberGenerator::c1[] = {0xbaa96887L, 0x1e17d32cL, 0x03bcdc3cL, 0x0f33d1b2L};
const uli RandomNumberGenerator::c2[] = {0x4b0f3b58L, 0xe874f0c3L, 0x6955c5a6L, 0x55a7ca46L};

#endif //USE_RAN4

// Variable(s)
RandomNumberGenerator* RandomNumberGenerator::theInstance = (RandomNumberGenerator*) 0;

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor RandomNumberGenerator()
//------------------------------------------------------------------------------
RandomNumberGenerator::RandomNumberGenerator()
{
    TRACE("RandomNumberGenerator::RandomNumberGenerator -->");
    setSeed(DEFAULT_SEED);
    TRACE("RandomNumberGenerator::RandomNumberGenerator <--");
}

//------------------------------------------------------------------------------
//  destructor ~RandomNumberGenerator()
//------------------------------------------------------------------------------
RandomNumberGenerator::~RandomNumberGenerator()
{
    TRACE("RandomNumberGenerator::~RandomNumberGenerator -->");
    delete theInstance;
    TRACE("RandomNumberGenerator::~RandomNumberGenerator <--");
}


//------------------------------------------------------------------------------
//  uli getRandomSeed()
//
//  Returns a random seed based on current time
//
//------------------------------------------------------------------------------
uli RandomNumberGenerator::getRandomSeed() const
{
    TRACE("RandomNumberGenerator::getRandomSeed -->");
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // use sec + min * hours of current time to provide random seed
    uli result = 0;
    while (result == 0)
    {
        result = timeinfo->tm_sec + timeinfo->tm_min * timeinfo->tm_hour;
    }
    TRACE("RandomNumberGenerator::getRandomSeed <--");
    return result;
}


//------------------------------------------------------------------------------
//  void setSeed()
//------------------------------------------------------------------------------
void RandomNumberGenerator::setSeed(uli seed)
{
    TRACE("RandomNumberGenerator::setSeed -->");
    idums = seed ? seed : getRandomSeed(); // get random seed if 0
#ifdef USE_RAN4
    idum = 1;
#else
    idum = idums;
#endif //USE_RAN4
    TRACE("RandomNumberGenerator::setSeed <--");
}
