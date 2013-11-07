############################################################################
##                                                                        ##
##   Makefile for LinkStateUpdate                                         ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
LINKSTATEUPDATE_CLASSES=MovingAverageRelativeLSUpdateVisitor MovingAverageAbsoluteLSUpdateVisitor MovingAverageClassLSUpdateVisitor  LinkStateUpdateVisitorFactory PeriodLSUpdateVisitor ThresholdHDTimerLSUpdateVisitor ClassHDTimerLSUpdateVisitor
LINKSTATEUPDATE_OBJ=$(LINKSTATEUPDATE_CLASSES:%=LinkStateUpdate/%)

$(LINKSTATEUPDATE_OBJ): LinkStateUpdate.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

LinkStateUpdate.init:
	-mkdir -m 755 -p $(OBJ_DIR)/LinkStateUpdate

LinkStateUpdate: $(LINKSTATEUPDATE_OBJ)
