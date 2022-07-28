#SAFE=echo

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

FNDARGS=-name 'Makefile' -o -name '*.[hc]'

WATCHCMD='test_all'

#Directories
ROOTDIR=$(shell realpath ../../)
MIRRORDIR=$(ROOTDIR)/test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#Dependencies
SRC_ROOT=$(ROOTDIR)/src

FOLDER_STRU=$(SRC_ROOT)/StrUtils
DEP_STRU=$(TMPDIR)/strUtils.o

FOLDER_LST=$( SRC_ROOT)/Lists
DEP_LST=$(TMPDIR)/list.o

FOLDER_TUT=$(SRC_ROOT)/TestUtils
DEP_TUT=$(TMPDIR)/testUtils.o

FOLDER_SMC=$(SRC_ROOT)/StateMachine

DEP_SMC_COND=$(TMPDIR)/stateCondition.o
DEP_SMC_CONDL=$(TMPDIR)/stateConditionList.o

DEP_SMC_STT=$(TMPDIR)/state.o
DEP_SMC_STTL=$(TMPDIR)/stateList.o

DEP_SMC_TRN=$(TMPDIR)/transition.o
DEP_SMC_TRNL=$(TMPDIR)/transitionList.o

DEP_SMC_BDY=$(TMPDIR)/stateMachine.o
DEP_SMC_BDYL=$(TMPDIR)/stateMachineList.o

#Assembled deps
DEP_ALL_SMC=$(DEP_LST) $(DEP_SMC_BDY) $(DEP_SMC_BDYL) $(DEP_SMC_STT) $(DEP_SMC_STTL) $(DEP_SMC_TRN) $(DEP_SMC_TRNL) $(DEP_SMC_COND) $(DEP_SMC_CONDL)

#Cmd files
HDRS_CMDR=commander.h
DIR_CMDR=.

SRC_PART_CMDR=$(DIR_CMDR)/commander.c
SRC_TEST_CMDR=$(SRC_PART_CMDR:.c=.test.c)
OBJ_PART_CMDR=$(TMPDIR)/$(notdir $(SRC_PART_CMDR:.c=.o))
OBJ_TEST_CMDR=$(TMPDIR)/$(notdir $(SRC_TEST_CMDR:.c=.o))

BIN_TEST_CMDR=$(OBJ_TEST_CMDR:.o=.bin)

#List files
SRC_PART_CMDRL=$(DIR_CMDR)/commanderList.c
SRC_TEST_CMDRL=$(SRC_PART_CMDRL:.c=.test.c)
OBJ_PART_CMDRL=$(TMPDIR)/$(notdir $(SRC_PART_CMDRL:.c=.o))
OBJ_TEST_CMDRL=$(TMPDIR)/$(notdir $(SRC_TEST_CMDRL:.c=.o))

BIN_TEST_CMDRL=$(OBJ_TEST_CMDRL:.o=.bin)

#General rules
default: dirs test

test: test_all

test_all: test_cmdr_obj test_cmdr_list

bin_tests: $(BIN_TEST_CMDR)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#Dependencies

$(DEP_STRU): $(shell find $(FOLDER_STRU) -type f )
	$(SAFE) make -C $(FOLDER_STRU) $@

$(DEP_TUT): $(shell find $(FOLDER_TUT) -type f )
	$(SAFE) make -C $(FOLDER_TUT)

$(DEP_SMC_TRN): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_TRNL): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_COND): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_CONDL): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_STT): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_STTL): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_BDY): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_BDYL): $(shell find $(FOLDER_SMC) -type f )
	$(SAFE) make -C $(FOLDER_SMC) $@

#Command rules
watch: $(SRC_TEST_CMDR) $(SRC_PART_CMDR) $(HDRS_CMDR) Makefile
	find $(DIR_CMDR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

test_cmdr_obj: $(BIN_TEST_CMDR)
	ls --color=auto -d  $(BIN_TEST_CMDR)
	echo -ne  "\033[0;35m"
	$(SAFE) $(BIN_TEST_CMDR)
	echo -ne "\033[0m"

$(BIN_TEST_CMDR): $(OBJ_PART_CMDR)  $(OBJ_TEST_CMDR) $(DEP_STRU)
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_CMDR): $(SRC_TEST_CMDR) $(HDRS_CMDR) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_CMDR): $(SRC_PART_CMDR) $(HDRS_CMDR) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Commander list
test_cmdr_list: $(BIN_TEST_CMDRL)
	ls --color=auto -d  $(BIN_TEST_CMDRL)
	echo -ne  "\033[0;35m"
	$(SAFE) $(BIN_TEST_CMDRL)
	echo -ne "\033[0m"

$(BIN_TEST_CMDRL): $(OBJ_PART_CMDRL) $(OBJ_PART_CMDR) $(OBJ_TEST_CMDRL) $(DEP_STRU) $(DEP_LST) $(DEP_TUT)
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_CMDRL): $(SRC_TEST_CMDRL) $(HDRS_CMDRL) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_CMDRL): $(SRC_PART_CMDRL) $(HDRS_CMDRL) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@
