############################################################################
##                                                                        ##
##   Makefile                                                             ##
##   version 1.0                                                          ##
############################################################################

# Directory settings
DOC_DIR=doc
SRC_DIR=src
OBJ_DIR=obj
TST_DIR=test

# Include global makefile
include $(SRC_DIR)/makefile.global

##-----------------------------------------------------------------------------##
##  Targets                                                                    ##
##-----------------------------------------------------------------------------##
# Build all packages
build: $(PACKAGES)

desine: build
	$(CXX) $(LXXFLAGS) $(ALL_OBJS) $(MAIN_DESINE_OBJ:%=$(OBJ_DIR)/%.o) -o $(OBJ_DIR)/desine

clean:
	-$(RM) -r $(PACKAGES:%=$(OBJ_DIR)/%/*) $(OBJ_DIR)/desine

cleanall: clean
	-$(RM) -r $(OBJ_DIR)/test/*
