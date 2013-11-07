############################################################################
##                                                                        ##
##   Makefile for Network                                                 ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
NETWORK_CLASSES=Cluster DegreeDistributionVisitor Flow FlowList FlowManager Link LinkList LinkListIterator LinkListMemento Topology TopologyFactory
NETWORK_OBJ=$(NETWORK_CLASSES:%=Network/%)

$(NETWORK_OBJ): Network.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

Network.init:
	-mkdir -m 755 -p $(OBJ_DIR)/Network

Network: $(NETWORK_OBJ)
