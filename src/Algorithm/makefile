############################################################################
##                                                                        ##
##   Makefile for Algorithm                                               ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
ALGORITHM_CLASSES=Algorithm DijkstraAlgorithm WSDijkstraAlgorithm NewMIRAAlgorithm SMIRAAlgorithm AbstractShortestPathAlgorithm SamcraAfterAlgorithm SamcraBeforeAlgorithm SamcraBAlgorithm TEDBAlgorithm AlgorithmFactory
ALGORITHM_OBJ=$(ALGORITHM_CLASSES:%=Algorithm/%)

$(ALGORITHM_OBJ): Algorithm.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

Algorithm.init:
	-mkdir -m 755 -p $(OBJ_DIR)/Algorithm

Algorithm: $(ALGORITHM_OBJ)
