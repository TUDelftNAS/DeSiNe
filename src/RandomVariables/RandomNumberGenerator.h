#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
/******************************************************************************

    header file RandomNumberGenerator.h for class: RandomNumberGenerator

    This class is a random number generator that produces random numbers ranging
    (0, 1].
    RandomNumberGenerator is implemented as a singleton.

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"
#include "Utils/Types.h"
using Types::uli;
using Types::usi;


#define USE_RAN4
#define DEFAULT_SEED 1

class RandomNumberGenerator
{
    // Variable(s)
    private:
    uli idums; // the seed
    uli idum;  // counter in the sequence

    static RandomNumberGenerator* theInstance;

    // Function(s) declarations

//------------------------------------------------------------------------------
//
//  constructor RandomNumberGenerator();
//
//  Constructs RandomNumberGenerator and sets the seed. If seed is 0. a
//  random seed will be choosen based on the current time.
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    RandomNumberGenerator();


//------------------------------------------------------------------------------
//
//  destructor ~RandomNumberGenerator()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~RandomNumberGenerator();


//------------------------------------------------------------------------------
//  uli getRandomSeed()
//
//  Returns a random seed based on current time
//
//------------------------------------------------------------------------------
     uli getRandomSeed() const;

    public:
//------------------------------------------------------------------------------
//  uli getSeed()
//
//  Returns the seed
//
//------------------------------------------------------------------------------
    uli getSeed() const
    {
        return idums;
    }

//------------------------------------------------------------------------------
//  void setSeed()
//
//  This function provides random number generators with a new seed. If no
//  argument is given, or the seed is 0 (zero), a random value will be choosen.
//  by using the current time.
//
//------------------------------------------------------------------------------
    void setSeed(uli seed);


//------------------------------------------------------------------------------
//  RandomNumberGenerator* getRandomNumberGenerator();
//------------------------------------------------------------------------------
    static RandomNumberGenerator* getRandomNumberGenerator()
    {
        if (theInstance == (RandomNumberGenerator*) 0)
        {
            theInstance = new RandomNumberGenerator();
        }
        return theInstance;
    }


#ifdef USE_RAN4  //////////////////////////////  ran4 //////////////////////////
////////////////////////////////////////////////////////////////////////////////
    private:
    // Constanst(s) taken from Numerical recipie in C, pg 303
    static const uli jflone = 0x3f800000;
    static const uli jflmsk = 0x007fffff;
    static const usi NI = 4;
    static const uli c1[];
    static const uli c2[];


//------------------------------------------------------------------------------
//  void psdes
//
//  Used by ran4. Taken from Numerical Recipies
//
//------------------------------------------------------------------------------
    void psdes(uli &lword, uli &irword)
    {
        uli ia, ib, iswap, itmph = 0, itmpl = 0;
        for (uli i = 0; i < NI; ++i)
        {
            ia = (iswap = irword) ^ c1[i];
            itmpl = ia & 0xffff;
            itmph = ia >> 16;
            ib = itmpl * itmpl + ~(itmph * itmph);
            irword = lword ^ (((ia = (ib >> 16) |
                              ((ib & 0xffff) << 16)) ^ c2[i]) + itmpl * itmph);
            lword = iswap;
        }
    }


    public:
//------------------------------------------------------------------------------
//  double generate()
//
//  This is the ran4 generator.
//  A random number generator. Very good, but very slow. Taken from Numerical
//  Recipies
//
//------------------------------------------------------------------------------
    double generate()
    {
        uli irword = idum;
        uli lword = idums;
        psdes(lword, irword);
        uli itemp = jflone | (jflmsk & irword);
        ++idum;
// Original line here, is replaced by next line to change range
// from [0, 1) to (0, 1]
//        return (double) (*(float*) &itemp) - 1.0;
        return (double) 2.0 - (*(float*) &itemp);
    }


#else //////////////////////////////  ran0 /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    private:
    // Constanst(s) taken from Numerical recipie in C, pg 279
    static const uli IA = 16807;      //7^5
    static const uli IM = 2147483647;  //2^31 - 1
    static const double AM = 1.0/IM;
    static const uli IQ = 127773;
    static const uli IR = 2836;
    static const uli MASK = 123459876;


    public:
//------------------------------------------------------------------------------
//  double generate()
//
//  This is the ran0 generator.
//  A random number generator. In most cases sufficient, and fast. Taken from
//  Numerical Recipies
//
//------------------------------------------------------------------------------
    double generate()
    {
    	idum ^= MASK;
    	uli k = (uli) idum/IQ;
    	idum = IA * idum - k * IQ - IR * k;
    	idum += idum < 0 ? IM : 0;
    	double result = AM * idum;
    	idum ^= MASK;
    	return result;
    }
#endif //USE_RAN4 //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}; //end declarations

#endif //RANDOMNUMBERGENERATOR_H
