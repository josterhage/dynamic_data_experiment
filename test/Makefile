CFLAGS += -g -O0 

tests	:=		mempool test_common

all: $(tests)

mempool:
	@$(HOSTCC) $(CFLAGS) -c -o $(TEST_OUT)/mempool_allocator.o $(PROJ_SRC)/mempool_allocator.c
	@$(HOSTCC) $(CFLAGS) -c -o $(TEST_OUT)/mempool_tests.o $(TEST_DIR)/mempool_tests.c
	@$(HOSTCC) $(CFLAGS) -o $(TEST_OUT)/mempool $(TEST_OUT)/mempool_allocator.o $(TEST_OUT)/mempool_tests.o

test_common:
	$(HOSTCC) $(CFLAGS) -c -o $(TEST_OUT)/test_common.o $(PROJ_SRC)/test_common.c
	$(HOSTCC) $(CFLAGS) -c -o $(TEST_OUT)/test_common_tests.o $(TEST_DIR)/test_common_tests.c
	$(HOSTCC) $(CFLAGS) -o $(TEST_OUT)/test_common $(TEST_OUT)/test_common.o -lm $(TEST_OUT)/test_common_tests.o