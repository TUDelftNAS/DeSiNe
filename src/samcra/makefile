SAMCRA_CLASSES=Fibonacci_mod linked_list_mod samcra_mod samcra2_mod samcra3_mod tamcra_mod samcra_util
SAMCRA_OBJ=$(SAMCRA_CLASSES:%=samcra/%)

$(SAMCRA_OBJ): samcra.init
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@.o -c $(SRC_DIR)/$@.c

samcra.init:
	-mkdir -m 755 -p $(OBJ_DIR)/samcra

samcra: $(SAMCRA_OBJ)
