############################################################################
##                                                                        ##
##   Makefile for Parameter                                               ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
PARAMETER_CLASSES=ParamsReader Parameters
PARAMETER_OBJ=$(PARAMETER_CLASSES:%=Parameter/%)

$(PARAMETER_OBJ): Parameter.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

Parameter.init:
	-mkdir -m 755 -p $(OBJ_DIR)/Parameter

Parameter: $(PARAMETER_OBJ)
