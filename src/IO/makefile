############################################################################
##                                                                        ##
##   Makefile for IO                                                      ##
##   version 1.0                                                          ##
############################################################################

# Objects used for this class-group
IO_CLASSES=Tag FileReader IgorBinaryLog IgorTextLog LogFactory
IO_OBJ=$(IO_CLASSES:%=IO/%)

$(IO_OBJ): IO.init
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.cpp

IO.init:
	-mkdir -m 755 -p $(OBJ_DIR)/IO

IO: $(IO_OBJ)
