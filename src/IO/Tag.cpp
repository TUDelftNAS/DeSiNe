/******************************************************************************

    source file Tag.cpp for struct: Tag

    Defines all the strings

    Author : T. Kleiberg
    Version: 1
    Date   : July 2004

******************************************************************************/

// Include(s)
#include "IO/Tag.h"

// Constanst(s)
// Definitions
char* const Tag::COMMENT = "#";

// Log options
char* const Tag::LOG_DIR = "LogDir";
char* const Tag::LOG_TYPE = "LogType";
char* const Tag::LOG_TYPE_IGOR = "LogTypeIgor";


// Simulation parameters
char* const Tag::FLOWS = "Flows";
char* const Tag::WARMUP = "Warmup";
char* const Tag::ITERATIONS = "Iterations";
char* const Tag::TOPOLOGY = "Topology";
char* const Tag::ENDPOINTS = "Endpoints";
char* const Tag::F_ARRIVAL = "Farrival";
char* const Tag::F_DURATION = "Fduration";
char* const Tag::F_BANDWIDTH = "Fbandwidth";
char* const Tag::SPLIT_NUM = "Split_Num";
char* const Tag::QOS_CONS = "QoSCons";
char* const Tag::ALGORITHM = "Algorithm";
//char* const Tag::NODES = "Nodes";
char* const Tag::L_CAPACITY = "Lcapacity";
char* const Tag::LSUPDATEINFO = "LsupdateInfo";

// Random Gen parameter
char* const Tag::SEED = "Seed";

// current used link state update policy
char* const Tag::LSU_MOVINGAVERAGE_RELATIVE = "Moving_Average_Relative";
char* const Tag::LSU_MOVINGAVERAGE_ABSOLUTE = "Moving_Average_Absolute";
char* const Tag::LSU_MOVINGAVERAGE_CLASS = "Moving_Average_class";
char* const Tag::LSU_PERIOD = "Period";
char* const Tag::LSU_HOLDDOWNTIMER_CLASS = "Holddown_Timer_class";
char* const Tag::LSU_HOLDDOWNTIMER_THRESHOLD = "Holddown_Timer_threshold";

// the algorithms that are implemented so far
char* const Tag::ALG_NEW_MIRA = "NewMIRA";
char* const Tag::ALG_SMIRA = "MI-PA";
char* const Tag::ALG_SHORTEST_PATH = "SP";
char* const Tag::ALG_WIDEST_SHORTEST_PATH = "WSP";
char* const Tag::ALG_SAMCRA_AFTER = "Samcra_after";
char* const Tag::ALG_SAMCRA_BEFORE = "SAMCRA";
char* const Tag::ALG_SAMCRA_B = "SAMCRA-B";
char* const Tag::ALG_TEDB = "TE-DB";
char* const Tag::ALG_SSP = "SSP";
char* const Tag::ALG_KARSMIRA = "KARSMIRA";
char* const Tag::ALG_KARSMIRA_ONE = "KARSMIRAone";
char* const Tag::ALG_KARSMIRA_CAP = "KARSMIRACap";
// the linkcost functions that are implemented so far
char* const Tag::LCF_INVERSE = "Inverse";
char* const Tag::LCF_PWRDOT75 = "PowerDot75";
char* const Tag::LCF_DELTA = "Delta";
char* const Tag::LCF_DELTA3 = "Delta3";
char* const Tag::LCF_SQUARE_SIN = "SquareSin";
char* const Tag::LCF_MIN_DELAY = "MinDelay";
char* const Tag::LCF_MIN_HOP = "MinHop";
char* const Tag::LCF_TEDB = "TEDB"; // used internally

// the different topologies
char* const Tag::TOP_ADJACENCY = "Adjacency";
char* const Tag::TOP_BARABASI = "Barabasi";
char* const Tag::TOP_ERDOS = "Erdos";
char* const Tag::TOP_FILE = "File";
char* const Tag::TOP_FULL = "Full";
char* const Tag::TOP_GRID2D = "Grid2D";
char* const Tag::TOP_RANDOM = "Random";
