objs 	:= main.o tests.o test_common.o mempool_allocator.o

CFLAGS	+= -O2

all: $(objs)
	$(HOSTCC) $(CFLAGS) -o $(BUILD_DIR)/exp $(addprefix $(BUILD_DIR)/, $(objs))

$(objs):
	$(HOSTCC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $(patsubst %.o, %.c, $@)