PROJ_SRC	:= $(CURDIR)/src
PROJ_INC	:= $(CURDIR)/include
BUILD_DIR	:= $(CURDIR)/build
TEST_DIR	:= $(CURDIR)/test
TEST_OUT	:= $(TEST_DIR)/out

HOSTCC		= gcc
HOSTCPP		= $(CC) -E
CFLAGS		:= -Wall -Wstrict-prototypes -std=gnu17
CFLAGS		+= -I$(PROJ_INC)

export PROJ_SRC PROJ_INC BUILD_DIR TEST_DIR TEST_OUT
export HOSTCC HOSTCPP CFLAGS

.PHONY += all tests clean

all:
	@$(MAKE) -C $(PROJ_SRC)

tests:
	@$(MAKE) -C $(TEST_DIR)

clean:
	@rm -rf $(BUILD_DIR)/*
	@rm -rf $(TEST_OUT)/*