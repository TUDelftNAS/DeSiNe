############################################################################
##                                                                        ##
##   Makefile for prf                                                     ##
##   version 1.0                                                          ##
############################################################################
# Objects used for this class-group
PRF_CLASSES=h_prf_t
PRF_OBJ=$(PRF_CLASSES:%=prf/%)

$(PRF_OBJ): prf.init
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.c

prf.init:
	-mkdir -m 755 -p $(OBJ_DIR)/prf

prf: $(PRF_OBJ)
