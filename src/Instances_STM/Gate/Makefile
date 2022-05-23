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
FOLDER_LST=../../Lists
DEP_LST=$(TMPDIR)/list.o

FOLDER_TST=../../TestUtils
DEP_TST=$(TMPDIR)/testUtils.o

FOLDER_SMC=../../StateMachine
DEP_SMC_COND=$(TMPDIR)/stateCondition.o
DEP_SMC_STT=$(TMPDIR)/state.o
DEP_SMC_STTL=$(TMPDIR)/stateList.o
DEP_SMC_TRN=$(TMPDIR)/transition.o
DEP_SMC_TRNL=$(TMPDIR)/transitionList.o
DEP_SMC=$(TMPDIR)/stateMachine.o

HDR_GATE=gate.h

#Gate files
SRC_PART_GAT=gate.c
SRC_TEST_GAT=gate.test.c
OBJ_PART_GAT=$(TMPDIR)/$(notdir $(SRC_PART_GAT:.c=.o))
OBJ_TEST_GAT=$(TMPDIR)/$(notdir $(SRC_TEST_GAT:.c=.o))
BIN_TEST_GAT=$(OBJ_TEST_GAT:.o=.bin)

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

#Gate transition files
DIR_GTRN=Transitions
SRC_PART_GTRN=$(DIR_GTRN)/gate.Transitions.c
SRC_TEST_GTRN=$(SRC_PART_GTRN:.c=.test.c)
OBJ_PART_GTRN=$(TMPDIR)/$(notdir $(SRC_PART_GTRN:.c=.o))
OBJ_TEST_GTRN=$(TMPDIR)/$(notdir $(SRC_TEST_GTRN:.c=.o))
BIN_TEST_GTRN=$(OBJ_TEST_GTRN:.o=.bin)

#General rules
default: $(TMPDIR) test
#default: $(TMPDIR) bin_tests

test:  gate_cond_test
#test: gate_cond_test gstt_test gate_test

clean:
	$(SAFE) rm $(TMPDIR)/*

$(TMPDIR):
	$(SAFE) mkdir -p $@

bin_tests: $(BIN_TEST_GAT) $(BIN_TEST_GCOND)

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

dirs:
	$(SAFE) mkdir $(TMPDIR)

#Dependencies Rules
$(DEP_TST):
	$(FOLDER_TST)

$(DEP_LST):
	$(SAFE) make -C $(FOLDER_LST) $@

$(DEP_SMC_TRN):
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_TRNL):
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_COND):
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_STT):
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC_STTL):
	$(SAFE) make -C $(FOLDER_SMC) $@

$(DEP_SMC):
	$(SAFE) make -C $(FOLDER_SMC) $@


#Gate rules
gate_test: $(BIN_TEST_GAT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GAT)
	echo -e "\033[0m"

$(BIN_TEST_GAT): $(OBJ_PART_GAT)  $(OBJ_TEST_GAT) $(DEP_SMC) $(DEP_SMC_STT) $(DEP_SMC_COND)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GAT): $(SRC_TEST_GAT) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GAT): $(SRC_PART_GAT) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate condition rules
gate_cond_test: $(BIN_TEST_GCOND)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GCOND)
	echo -e "\033[0m"

$(BIN_TEST_GCOND): $(OBJ_PART_GCOND)  $(OBJ_TEST_GCOND) $(DEP_SMC_COND)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GCOND): $(SRC_TEST_GCOND) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GCOND): $(SRC_PART_GCOND) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate States rules
gstt_test: $(BIN_TEST_GSTT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GSTT)
	echo -e "\033[0m"

$(BIN_TEST_GSTT): $(OBJ_PART_GSTT) $(OBJ_TEST_GSTT) $(DEP_SMC_STT) $(DEP_SMC_STTL) $(DEP_LST) $(DEP_TST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GSTT): $(SRC_TEST_GSTT) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GSTT): $(SRC_PART_GSTT) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

#Gate Transition rules
gtrn_test: $(BIN_TEST_GTRN)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_GTRN)
	echo -e "\033[0m"

$(BIN_TEST_GTRN): $(OBJ_PART_GTRN) $(OBJ_TEST_GTRN) $(DEP_SMC_TRNL) $(DEP_SMC_TRN) $(DEP_SMC_STT) $(DEP_TST) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_GTRN): $(SRC_TEST_GTRN) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_GTRN): $(SRC_PART_GTRN) $(HDR_GATE)
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

