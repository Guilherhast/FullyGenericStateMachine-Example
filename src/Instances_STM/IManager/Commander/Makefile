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
ROOTDIR=$(realpath ../../../../)
SOURCEDIR=$(ROOTDIR)/src
MIRRORDIR=$(ROOTDIR)/test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#Dependencies
FOLDER_STRU=$(SOURCEDIR)/StrUtils
DEP_STRU=$(TMPDIR)/strUtils.o

FOLDER_LST=$(SOURCEDIR)/Lists
DEP_LST=$(TMPDIR)/list.o

FOLDER_TUT=$(SOURCEDIR)/TestUtils
DEP_TUT=$(TMPDIR)/testUtils.o

FOLDER_CMD=$(SOURCEDIR)/Commander
DEP_CMDR=$(TMPDIR)/commander.o
DEP_CMDL=$(TMPDIR)/commanderList.o

FOLDER_SMC=$(SOURCEDIR)/StateMachine

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

#Instance files
DIR_CMDRI=.
SRC_PART_CMDRI=$(DIR_CMDRI)/instance.c
SRC_TEST_CMDRI=$(SRC_PART_CMDRI:.c=.test.c)
OBJ_PART_CMDRI=$(TMPDIR)/$(notdir $(SRC_PART_CMDRI:.c=.o))
OBJ_TEST_CMDRI=$(TMPDIR)/$(notdir $(SRC_TEST_CMDRI:.c=.o))

BIN_TEST_CMDRI=$(OBJ_TEST_CMDRI:.o=.bin)


#General rules
default: dirs test

test: test_all

test_all: test_cmdr_inst

bin_tests: $(BIN_TEST_CMDR)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#Dependencies
$(DEP_STRU): $(shell find $(FOLDER_STRU) -type f )
	$(SAFE) make -C $(FOLDER_STRU) $@

$(DEP_LST): $(shell find $(FOLDER_LST) -type f )
	$(SAFE) make -C $(FOLDER_LST) $@

$(DEP_TUT): $(shell find $(FOLDER_TUT) -type f )
	$(SAFE) make -C $(FOLDER_TUT) $@

$(DEP_CMDR): $(shell find $(FOLDER_CMD) -type f )
	$(SAFE) make -C $(FOLDER_CMD) $@

$(DEP_CMDL): $(shell find $(FOLDER_CMD) -type f )
	$(SAFE) make -C $(FOLDER_CMD) $@

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

#Commander inst
watch: $(SRC_TEST_CMDR) $(SRC_PART_CMDR) $(HDRS_CMDR) Makefile
	find $(DIR_CMDR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

test_cmdr_inst: $(BIN_TEST_CMDRI)
	ls --color=auto -d  $(BIN_TEST_CMDRI)
	echo -ne  "\033[0;35m"
	$(SAFE) $(BIN_TEST_CMDRI)
	echo -ne "\033[0m"

$(BIN_TEST_CMDRI): $(OBJ_PART_CMDRI) $(OBJ_TEST_CMDRI) $(DEP_STRU) $(DEP_TUT) $(DEP_ALL_SMC) $(DEP_CMDR) $(DEP_CMDL)
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_CMDRI): $(SRC_TEST_CMDRI) $(HDRS_CMDRI) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_CMDRI): $(SRC_PART_CMDRI) $(HDRS_CMDRI) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

