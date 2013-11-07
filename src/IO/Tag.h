#ifndef TAG_H
#define TAG_H
/******************************************************************************

    header file Tag.h for struct: Tag

    Structure that is used for holding all possible tags.
    Use is eg: Tag::COMMENT instead of the value "#"

    Author : T. Kleiberg
    Version: 1
    Date   : July 2004

******************************************************************************/


// Include(s)


struct Tag
{
    // Constanst(s)
    // Global Tags
    static char* const COMMENT;

    // Log options
    static char* const LOG_DIR;
    static char* const LOG_TYPE;
    static char* const LOG_TYPE_IGOR;

    // Simulation parameters
    static char* const FLOWS;
    static char* const WARMUP;
    static char* const ITERATIONS;
    static char* const TOPOLOGY;
    static char* const ENDPOINTS;
    static char* const F_ARRIVAL;
    static char* const F_DURATION;
    static char* const F_BANDWIDTH;
    static char* const SPLIT_NUM;
    static char* const QOS_CONS;
    static char* const ALGORITHM;
    //static char* const NODES;
    static char* const L_CAPACITY;
    static char* const LSUPDATEINFO;

    // Random Gen parameter
    static char* const SEED;

    // the link sate update information policies
    static char* const LSU_MOVINGAVERAGE_RELATIVE;
    static char* const LSU_MOVINGAVERAGE_ABSOLUTE;
    static char* const LSU_MOVINGAVERAGE_CLASS;
	static char* const LSU_PERIOD;
	static char* const LSU_HOLDDOWNTIMER_CLASS;
	static char* const LSU_HOLDDOWNTIMER_THRESHOLD;


    // the algorithms that are implemented so far
    static char* const ALG_NEW_MIRA;
    static char* const ALG_SMIRA;
    static char* const ALG_SHORTEST_PATH;
    static char* const ALG_WIDEST_SHORTEST_PATH;
    static char* const ALG_SAMCRA_AFTER;
    static char* const ALG_SAMCRA_BEFORE;
    static char* const ALG_SAMCRA_B;
    static char* const ALG_SSP;
    static char* const ALG_TEDB;
	static char* const ALG_KARSMIRA;
	static char* const ALG_KARSMIRA_ONE;
	static char* const ALG_KARSMIRA_CAP;

    // the linkcost functions that are implemented so far
    static char* const LCF_INVERSE;
    static char* const LCF_PWRDOT75;
    static char* const LCF_DELTA;
    static char* const LCF_DELTA3;
    static char* const LCF_SQUARE_SIN;
    static char* const LCF_MIN_DELAY;
    static char* const LCF_MIN_HOP;
    static char* const LCF_TEDB; // used internally

    // the different topologies
    static char* const TOP_ADJACENCY;
    static char* const TOP_BARABASI;
    static char* const TOP_ERDOS;
    static char* const TOP_FILE;
    static char* const TOP_FULL;
    static char* const TOP_GRID2D;
    static char* const TOP_RANDOM;

    // Tags used in Topoogy file and/or TopolReader class
/*
static char* const EDGE_NODES = "Edgenodes";
    static char* const EDGE_NODE_LIST = "Edgenodeslist";
    static char* const LINK = "Link";
*/
};
#endif // TAG_H
