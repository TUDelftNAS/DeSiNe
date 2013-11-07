############################################################################
##                                                                        ##
##   Makefile for Utils                                                   ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
UTILS_CLASSES=Utils TraceManager
UTILS_OBJ=$(UTILS_CLASSES:%=Utils/%)

$(UTILS_OBJ): Utils.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

Utils.init:
	-mkdir -m 755 -p $(OBJ_DIR)/Utils

Utils: $(UTILS_OBJ)
