# Rules makefile

## Module files
ifndef WDIR

WDIR=$(MODULE_DIRECTORY)

endif

## Defining colors

ifdef COLOR_OVRD
COLOR_TEST=$(COLOR_OVRD)
else ifdef COLOR_SGST
COLOR_TEST=$(COLOR_SGST)
endif

### Header
MOD_HDR=$(MODULE_DIRECTORY)/$(SRC_BASE).h

### Sources
SRC_MOD_PART=$(MOD_HDR:.h=.c)
SRC_MOD_TEST=$(SRC_MOD_PART:.c=.test.c)

### Objects
OBJ_MOD_PART=$(TST_DIR)/$(notdir $(SRC_MOD_PART:.c=.o))
OBJ_MOD_TEST=$(TST_DIR)/$(notdir $(SRC_MOD_TEST:.c=.o))

### Binary tests
BIN_MOD_TEST=$(OBJ_MOD_TEST:.o=.bin)
## Module Rules
test_mod: $(BIN_MOD_TEST)
	$(LSS) $<
	$(ECE) $(COLOR_TEST)
	$(SAFE) $<
	$(ECE) $(COLOR_RESTORE)

$(BIN_MOD_TEST): $(DEP_MOD) $(OBJ_MOD_PART) $(OBJ_MOD_TEST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_MOD_TEST): $(SRC_MOD_TEST) $(MOD_HDR) $(TST_DIR)
	$(SAFE) $(CC) $(CFLAGS)  $< -o $@

$(OBJ_MOD_PART): $(SRC_MOD_PART) $(MOD_HDR) $(TST_DIR)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@


# Side module config
ifeq ($(HAS_SIDEMOD),true)

ifndef SIDEMOD_SUFIX
$(error SIDEMOD_SUFIX not defined)
endif
## Make variables
TESTED_MODULES=test_mod test_side_mod

### Sources
SRC_SIDE_MOD_PART=$(MOD_HDR:.h=$(SIDEMOD_SUFIX).c)
SRC_SIDE_MOD_TEST=$(SRC_SIDE_MOD_PART:.c=.test.c)

### Objects
OBJ_SIDE_MOD_PART=$(TST_DIR)/$(notdir $(SRC_SIDE_MOD_PART:.c=.o))
OBJ_SIDE_MOD_TEST=$(TST_DIR)/$(notdir $(SRC_SIDE_MOD_TEST:.c=.o))

### Binary tests
BIN_SIDE_MOD_TEST=$(OBJ_SIDE_MOD_TEST:.o=.bin)

## Side module rules
test_side_mod: $(BIN_SIDE_MOD_TEST)
	$(LSS) $<
	$(ECE) $(COLOR_TEST)
	$(SAFE) $<
	$(ECE) $(COLOR_RESTORE)


$(BIN_SIDE_MOD_TEST): $(DEP_SIDE_MOD) $(OBJ_SIDE_MOD_PART) $(OBJ_SIDE_MOD_TEST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_SIDE_MOD_TEST): $(SRC_SIDE_MOD_TEST) $(MOD_HDR) $(TST_DIR)
	$(SAFE) $(CC) $(CFLAGS) $<  -o $@

$(OBJ_SIDE_MOD_PART): $(SRC_SIDE_MOD_PART) $(MOD_HDR) $(TST_DIR)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

else

## Make variables
TESTED_MODULES=test_mod
## Cleaning just in case
undefine OBJ_SIDE_MOD_PART
undefine BIN_SIDE_MOD_TEST

endif

# Local rules
test: test_all

test_all: $(TESTED_MODULES)

full_mod: $(OBJ_MOD_PART) $(OBJ_SIDE_MOD_PART)

bin_tests: $(BIN_MOD_TEST) $(BIN_SIDE_MOD_TEST)
