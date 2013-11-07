############################################################################
##                                                                        ##
##   Makefile for Main - Desine                                           ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
MAIN_DESINE_CLASSES=DesineMain DesineData DesineSumData DesineModel
MAIN_DESINE_OBJ=$(MAIN_DESINE_CLASSES:%=Main/Desine/%)

$(MAIN_DESINE_OBJ): Main.Desine.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

Main.Desine.init:
	-mkdir -m 755 -p $(OBJ_DIR)/Main/Desine

Main.Desine: $(MAIN_DESINE_OBJ)
