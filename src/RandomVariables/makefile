############################################################################
##                                                                        ##
##   Makefile for RandomVariables                                         ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
RANDVAR_CLASSES=RandomNumberGenerator RandomVar ConstantVar UniformVar ExponentialVar MixedVar
RANDVAR_OBJ=$(RANDVAR_CLASSES:%=RandomVariables/%)

$(RANDVAR_OBJ): RandomVariables.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

RandomVariables.init:
	-mkdir -m 755 -p $(OBJ_DIR)/RandomVariables

RandomVariables: $(RANDVAR_OBJ)
