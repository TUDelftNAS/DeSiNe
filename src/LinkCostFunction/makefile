############################################################################
##                                                                        ##
##   Makefile for LinkCostFunction                                        ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
LINKCOSTFUNCTION_CLASSES=LinkCostFunctionVisitorFactory
LINKCOSTFUNCTION_OBJ=$(LINKCOSTFUNCTION_CLASSES:%=LinkCostFunction/%)

$(LINKCOSTFUNCTION_OBJ): LinkCostFunction.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

LinkCostFunction.init:
	-mkdir -m 755 -p $(OBJ_DIR)/LinkCostFunction

LinkCostFunction: $(LINKCOSTFUNCTION_OBJ)
