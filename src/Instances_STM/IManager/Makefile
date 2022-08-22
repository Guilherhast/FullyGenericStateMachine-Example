#SAFE=echo
WATCHCMD=test
WATCHDIR=.
FNDARGS=-name 'Makefile' -o -name '*.[hc]'

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage


#Directories
ROOTDIR=$(realpath ../../../)
TMPDIR=$(ROOTDIR)/test
DIR_INM=.
#ALLDIRS=$(TMPDIR)/StateCondition

#Dependencies
FOLDER_IOM=$(realpath ../../IOManager)
DEP_IOM=$(TMPDIR)/ioManager.o

FOLDER_CMD=$(realpath Commander)
DEP_CMD=$(TMPDIR)/commander.o

#Assembled dependencies
DEP_ALL_BASE=$(DEP_SMC_STT)

HDR_INM=instancesManager.h

#Instances manager files
SRC_PART_INM=instancesManager.c
SRC_TEST_INM=instancesManager.test.c
OBJ_PART_INM=$(TMPDIR)/$(notdir $(SRC_PART_INM:.c=.o))
OBJ_TEST_INM=$(TMPDIR)/$(notdir $(SRC_TEST_INM:.c=.o))
BIN_TEST_INM=$(OBJ_TEST_INM:.o=.bin)

#FOLDERS
DIRMAKE_CMDR=Commander
ALLDIRS+=$(DIRMAKE_CMDR)


#General rules
default: $(TMPDIR) test
#default: $(TMPDIR) bin_tests

test: cmdr_tests

clean:
	$(SAFE) make -C ../../../ clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) mkdir -p $@

bin_tests: cmdr_bin_tests

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

#Dependencies Rules
#Dependencies without Dependencies causes headches
#Adding a more generic rule to prevent it
$(DEP_IOM): $(shell find $(FOLDER_IOM) -type f )
	$(SAFE) make -C $(FOLDER_IOM) $@

$(DEP_CMD): $(shell find $(FOLDER_CMD) -type f )
	$(SAFE) make -C $(FOLDER_CMD) $@

#Gate common
$(OBJ_PART_GCMM): $(SRC_PART_GCMM)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Commander rules
cmdr_bin_tests:
	$(SAFE) make -C $(DIRMAKE_CMDR) bin_tests

cmdr_tests:
	$(SAFE) make -C $(DIRMAKE_CMDR)

#Gate rules
inm_test: $(BIN_TEST_INM)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_INM)
	echo -e "\033[0m"

$(BIN_TEST_INM): $(OBJ_PART_INM)  $(OBJ_TEST_INM) $(DEP_IOM) $(DEP_CMD)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_INM): $(SRC_TEST_INM) $(HDR_INM) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_INM): $(SRC_PART_INM) $(HDR_INM) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@
