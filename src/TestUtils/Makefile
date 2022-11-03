# Makefile Commander

## Import config
ROOTDIR=$(realpath ../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Module files
SRC_BASE=testUtils
MODULE_DIRECTORY=$(MODULE_TESTUTILS)

SRC_MOD_PART=$(MODULE_DIRECTORY)/$(SRC_BASE).c
OBJ_MOD_PART=$(TST_DIR)/$(notdir $(SRC_MOD_PART:.c=.o))

## Rule definitions
test:  test_all

test_all: test_mod

test_mod: full_mod msg

bin_tests: full_mod

full_mod: $(OBJ_MOD_PART)

$(OBJ_MOD_PART): $(SRC_MOD_PART) $(TST_DIR)
	$(SAFE) $(CC) $(CFLAGS) $< -o $@

# Configuration overwrite
msg:
	$(ECE) $(COLOR_TEST) This module has no tests $(COLOR_RESTORE)
