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
DIR_GATE=.
#ALLDIRS=$(TMPDIR)/StateCondition

#Dependencies
FOLDER_LST=$(realpath ../../Lists)
DEP_LST=$(TMPDIR)/list.o

FOLDER_TST=$(realpath ../../TestUtils)
DEP_TST=$(TMPDIR)/testUtils.o

FOLDER_SMC=$(realpath ../../StateMachine)
DEP_SMC_COND=$(TMPDIR)/stateCondition.o
DEP_SMC_CONDL=$(TMPDIR)/stateConditionList.o
DEP_SMC_STT=$(TMPDIR)/state.o
DEP_SMC_STTL=$(TMPDIR)/stateList.o
DEP_SMC_TRN=$(TMPDIR)/transition.o
DEP_SMC_TRNL=$(TMPDIR)/transitionList.o
DEP_SMC_BDY=$(TMPDIR)/stateMachine.o
DEP_SMC_BDYL=$(TMPDIR)/stateMachineList.o

DEP_ALL_BASE=$(DEP_SMC_STT) $(DEP_SMC_STTL) $(DEP_SMC_TRN) $(DEP_SMC_TRNL) $(DEP_LST)

DEP_ALL_TRN=$(DEP_ALL_BASE) $(DEP_TST)
DEP_ALL_CND=$(DEP_ALL_BASE) $(DEP_SMC_COND) $(DEP_SMC_CONDL)
DEP_ALL_STT=$(DEP_ALL_CND) $(DEP_TST)
DEP_ALL_BDY=$(DEP_ALL_STT) $(DEP_SMC_BDY) $(DEP_SMC_BDYL)
DEP_ALL_GAT=$(DEP_ALL_BDY)

HDR_GATE=gate.h

#Gate files
SRC_PART_GAT=gate.c
SRC_TEST_GAT=gate.test.c
OBJ_PART_GAT=$(TMPDIR)/$(notdir $(SRC_PART_GAT:.c=.o))
OBJ_TEST_GAT=$(TMPDIR)/$(notdir $(SRC_TEST_GAT:.c=.o))
BIN_TEST_GAT=$(OBJ_TEST_GAT:.o=.bin)

#Gate transition files
DIR_GTRN=Transitions
SRC_PART_GTRN=$(DIR_GTRN)/gate.Transitions.c
SRC_TEST_GTRN=$(SRC_PART_GTRN:.c=.test.c)
OBJ_PART_GTRN=$(TMPDIR)/$(notdir $(SRC_PART_GTRN:.c=.o))
OBJ_TEST_GTRN=$(TMPDIR)/$(notdir $(SRC_TEST_GTRN:.c=.o))
BIN_TEST_GTRN=$(OBJ_TEST_GTRN:.o=.bin)

#Gate condition files
DIR_GCOND=Conditions
SRC_PART_GCOND=$(DIR_GCOND)/gate.conditions.c
SRC_TEST_GCOND=$(SRC_PART_GCOND:.c=.test.c)
OBJ_PART_GCOND=$(TMPDIR)/$(notdir $(SRC_PART_GCOND:.c=.o))
OBJ_TEST_GCOND =$(TMPDIR)/$(notdir $(SRC_TEST_GCOND:.c=.o))
BIN_TEST_GCOND=$(OBJ_TEST_GCOND:.o=.bin)

#Gate state files
DIR_GSTT=States
SRC_PART_GSTT=$(DIR_GSTT)/gate.States.c
SRC_TEST_GSTT=$(SRC_PART_GSTT:.c=.test.c)
OBJ_PART_GSTT=$(TMPDIR)/$(notdir $(SRC_PART_GSTT:.c=.o))
OBJ_TEST_GSTT=$(TMPDIR)/$(notdir $(SRC_TEST_GSTT:.c=.o))
BIN_TEST_GSTT=$(OBJ_TEST_GSTT:.o=.bin)

#Gate body files
DIR_GBDY=Body
SRC_PART_GBDY=$(DIR_GBDY)/gate.body.c
SRC_TEST_GBDY=$(SRC_PART_GBDY:.c=.test.c)
OBJ_PART_GBDY=$(TMPDIR)/$(notdir $(SRC_PART_GBDY:.c=.o))
OBJ_TEST_GBDY=$(TMPDIR)/$(notdir $(SRC_TEST_GBDY:.c=.o))
BIN_TEST_GBDY=$(OBJ_TEST_GBDY:.o=.bin)


#General rules
default: $(TMPDIR) test
#default: $(TMPDIR) bin_tests

test:  gtrn_test gcnd_test gstt_test gbdy_test gate_test

clean:
	$(SAFE) make -C ../../../ clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) mkdir -p $@

bin_tests: $(BIN_TEST_GAT) $(BIN_TEST_GCOND)

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

#Dependencies Rules
#Dependencies without Dependencies causes headches
#Adding a more generic rule to prevent it
$(DEP_TST): $(shell find $(FOLDER_TST) -type f )
	$(SAFE) make -C $(FOLDER_TST) $@

$(DEP_LST): $(shell find $(FOLDER_LST) -type f )
	$(SAFE) make -C $(FOLDER_LST) $@

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



#Gate rules
gate_test: $(BIN_TEST_GAT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GAT)
	echo -e "\033[0m"

$(BIN_TEST_GAT): $(OBJ_PART_GAT)  $(OBJ_TEST_GAT) $(OBJ_PART_GBDY) $(OBJ_PART_GSTT) $(OBJ_PART_GTRN) $(OBJ_PART_GCOND) $(DEP_ALL_GAT)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GAT): $(SRC_TEST_GAT) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GAT): $(SRC_PART_GAT) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate Transition rules
gtrn_test: $(BIN_TEST_GTRN)
	ls -d --color=auto $(BIN_TEST_GTRN)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GTRN)
	echo -e "\033[0m"

$(BIN_TEST_GTRN): $(OBJ_PART_GTRN) $(OBJ_TEST_GTRN) $(DEP_ALL_TRN)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GTRN): $(SRC_TEST_GTRN) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GTRN): $(SRC_PART_GTRN) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate condition rules
gcnd_test: $(BIN_TEST_GCOND)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GCOND)
	echo -e "\033[0m"

$(BIN_TEST_GCOND): $(OBJ_PART_GCOND)  $(OBJ_TEST_GCOND) $(DEP_ALL_CND) $(DEP_SMC_COND) $(DEP_SMC_CONDL)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GCOND): $(SRC_TEST_GCOND) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GCOND): $(SRC_PART_GCOND) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@


#Gate States rules
gstt_test: $(BIN_TEST_GSTT)
	ls -d --color=auto $(BIN_TEST_GTRN)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GSTT)
	echo -e "\033[0m"

$(BIN_TEST_GSTT): $(OBJ_PART_GSTT) $(OBJ_TEST_GSTT) $(OBJ_PART_GTRN) $(OBJ_PART_GCOND) $(DEP_ALL_STT)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GSTT): $(SRC_TEST_GSTT) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GSTT): $(SRC_PART_GSTT) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate Body rules
gbdy_test: $(BIN_TEST_GBDY)
	ls -d --color=auto $(BIN_TEST_GBDY)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GBDY)
	echo -e "\033[0m"

$(BIN_TEST_GBDY): $(OBJ_PART_GBDY) $(OBJ_TEST_GBDY) $(OBJ_PART_GSTT) $(OBJ_PART_GTRN) $(OBJ_PART_GCOND) $(DEP_ALL_BDY)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GBDY): $(SRC_TEST_GBDY) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GBDY): $(SRC_PART_GBDY) $(HDR_GATE) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

