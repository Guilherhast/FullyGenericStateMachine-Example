#SAFE=echo

#Watch command
WATCHCMD=test
WATCHDIR=.
FNDARGS=-name 'Makefile' -o -name '*.[hc]'

CC=$(shell which gcc)
LSS=ls --color=auto -d

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

#Directories
ROOTDIR=$(realpath ../../)
MIRRORDIR=$(ROOTDIR)/test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#Dependencies
FOLDER_LST=../Lists
DEP_LST=$(TMPDIR)/list.o

#Transition  files
HDRS_TRANS=transition.h
DIR_TRANS=Transition

SRC_PART_TRANS=$(DIR_TRANS)/transition.c
SRC_TEST_TRANS=$(SRC_PART_TRANS:.c=.test.c)
OBJ_PART_TRANS=$(TMPDIR)/$(notdir $(SRC_PART_TRANS:.c=.o))
OBJ_TEST_TRANS=$(TMPDIR)/$(notdir $(SRC_TEST_TRANS:.c=.o))

BIN_TEST_TRANS=$(OBJ_TEST_TRANS:.o=.bin)

SRC_PART_LTRANS=$(DIR_TRANS)/transitionList.c
SRC_TEST_LTRANS=$(SRC_PART_LTRANS:.c=.test.c)
OBJ_PART_LTRANS=$(TMPDIR)/$(notdir $(SRC_PART_LTRANS:.c=.o))
OBJ_TEST_LTRANS=$(TMPDIR)/$(notdir $(SRC_TEST_LTRANS:.c=.o))

BIN_TEST_LTRANS=$(OBJ_TEST_LTRANS:.o=.bin)

#State condition files
HDRS_SCOND=stateCondition.h
DIR_SCOND=Condition

SRC_PART_SCOND=$(DIR_SCOND)/stateCondition.c
SRC_TEST_SCOND=$(SRC_PART_SCOND:.c=.test.c)
OBJ_PART_SCOND=$(TMPDIR)/$(notdir $(SRC_PART_SCOND:.c=.o))
OBJ_TEST_SCOND=$(TMPDIR)/$(notdir $(SRC_TEST_SCOND:.c=.o))

BIN_TEST_SCOND=$(OBJ_TEST_SCOND:.o=.bin)

SRC_PART_LSCOND=$(DIR_SCOND)/stateConditionList.c
SRC_TEST_LSCOND=$(SRC_PART_LSCOND:.c=.test.c)
OBJ_PART_LSCOND=$(TMPDIR)/$(notdir $(SRC_PART_LSCOND:.c=.o))
OBJ_TEST_LSCOND=$(TMPDIR)/$(notdir $(SRC_TEST_LSCOND:.c=.o))

BIN_TEST_LSCOND=$(OBJ_TEST_LSCOND:.o=.bin)

#ALL_OBJ_SCOND=$(OBJ_PART_SCOND) $(OBJ_PART_LSCOND)

#State files
HDRS_STT=state.h
DIR_STT=State

SRC_PART_STT=$(DIR_STT)/state.c
SRC_TEST_STT=$(SRC_PART_STT:.c=.test.c)
OBJ_PART_STT=$(TMPDIR)/$(notdir $(SRC_PART_STT:.c=.o))
OBJ_TEST_STT=$(TMPDIR)/$(notdir $(SRC_TEST_STT:.c=.o))

BIN_TEST_STT=$(OBJ_TEST_STT:.o=.bin)

SRC_PART_LSTT=$(DIR_STT)/stateList.c
SRC_TEST_LSTT=$(SRC_PART_LSTT:.c=.test.c)
OBJ_PART_LSTT=$(TMPDIR)/$(notdir $(SRC_PART_LSTT:.c=.o))
OBJ_TEST_LSTT=$(TMPDIR)/$(notdir $(SRC_TEST_LSTT:.c=.o))

BIN_TEST_LSTT=$(OBJ_TEST_LSTT:.o=.bin)

#State Machine files
HDRS_SMC=stateMachine.h
DIR_PART_SMC=Body

SRC_PART_SMC=$(DIR_PART_SMC)/stateMachine.c
SRC_TEST_SMC=$(SRC_PART_SMC:.c=.test.c)
OBJ_PART_SMC=$(TMPDIR)/$(notdir $(SRC_PART_SMC:.c=.o))
OBJ_TEST_SMC=$(TMPDIR)/$(notdir $(SRC_TEST_SMC:.c=.o))

BIN_TEST_SMC=$(OBJ_TEST_SMC:.o=.bin)

SRC_PART_LSMC=$(DIR_PART_SMC)/stateMachineList.c
SRC_TEST_LSMC=$(SRC_PART_LSMC:.c=.test.c)
OBJ_PART_LSMC=$(TMPDIR)/$(notdir $(SRC_PART_LSMC:.c=.o))
OBJ_TEST_LSMC=$(TMPDIR)/$(notdir $(SRC_TEST_LSMC:.c=.o))

BIN_TEST_LSMC=$(OBJ_TEST_LSMC:.o=.bin)

#Genral rules
defualt: dirs test

test: test_objs test_lists

test_objs: test_transition_obj test_stateCondition_obj test_state_obj test_stateMachine_obj
#test_objs:  test_stateMachine_obj

test_lists: test_transition_list test_state_list test_stateCondition_list test_stateMachine_list
#test_lists: test_stateMachine_list

list_bin_test: $(BIN_TEST_LSMC) $(BIN_TEST_LSCOND) $(BIN_TEST_LSTT) $(BIN_TEST_LTRANS)

obj_bin_test: $(BIN_TEST_TRANS) $(BIN_TEST_SMC) $(BIN_TEST_SCOND) $(BIN_TEST_STT)

bin_tests:  obj_bin_test list_bin_test

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs:
	$(SAFE) mkdir -p $(TMPDIR)

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)


#Dependencies Rules

$(DEP_LST):
	$(SAFE) make -C $(FOLDER_LST) $@

#State condition rules
test_transition_obj: $(BIN_TEST_TRANS)
	$(LSS) $(BIN_TEST_TRANS)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_TRANS)
	echo -e "\033[0m"

$(BIN_TEST_TRANS): $(OBJ_PART_TRANS)  $(OBJ_TEST_TRANS) $(OBJ_PART_STT)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_TRANS): $(SRC_TEST_TRANS) $(HDRS_TRANS) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_TRANS) -o $@

$(OBJ_PART_TRANS): $(SRC_TEST_TRANS) $(HDRS_TRANS) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_TRANS) -o $@


test_transition_list: $(BIN_TEST_LTRANS)
	$(LSS) $(BIN_TEST_LTRANS)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_LTRANS)
	echo -e "\033[0m"

$(BIN_TEST_LTRANS): $(OBJ_PART_TRANS)  $(OBJ_PART_LTRANS)  $(OBJ_TEST_LTRANS) $(OBJ_PART_STT) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LTRANS): $(SRC_TEST_LTRANS) $(HDRS_LTRANS) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LTRANS) -o $@

$(OBJ_PART_LTRANS): $(SRC_TEST_LTRANS) $(HDRS_LTRANS) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LTRANS) -o $@

#State condition rules
test_stateCondition_obj: $(BIN_TEST_SCOND)
	$(LSS) $(BIN_TEST_SCOND)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_SCOND)
	echo -e "\033[0m"

$(BIN_TEST_SCOND): $(OBJ_PART_SCOND)  $(OBJ_TEST_SCOND) $(OBJ_PART_TRANS)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_SCOND): $(SRC_TEST_SCOND) $(HDRS_SCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_SCOND) -o $@

$(OBJ_PART_SCOND): $(SRC_TEST_SCOND) $(HDRS_SCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_SCOND) -o $@

test_stateCondition_list: $(BIN_TEST_LSCOND)
	$(LSS) $(BIN_TEST_LSCOND)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_LSCOND)
	echo -e "\033[0m"

$(BIN_TEST_LSCOND): $(OBJ_PART_LSCOND) $(OBJ_PART_SCOND) $(OBJ_TEST_LSCOND) $(OBJ_PART_TRANS) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LSCOND): $(SRC_TEST_LSCOND) $(HDRS_LSCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LSCOND) -o $@

$(OBJ_PART_LSCOND): $(SRC_TEST_LSCOND) $(HDRS_LSCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LSCOND) -o $@

#State rules
test_state_all: test_state_obj test_state_list

test_state_obj: $(BIN_TEST_STT)
	$(LSS) $(BIN_TEST_STT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_STT)
	echo -e "\033[0m"

$(BIN_TEST_STT): $(OBJ_PART_STT)  $(OBJ_TEST_STT)
	$(SAFE) $(CC) $(OBJ_PART_STT) $(OBJ_TEST_STT) $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_STT): $(SRC_TEST_STT) $(HDRS_STT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_STT) -o $@

$(OBJ_PART_STT): $(SRC_PART_STT) $(HDRS_STT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_STT) -o $@

test_state_list: $(BIN_TEST_LSTT)
	$(LSS) $(BIN_TEST_LSTT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_LSTT)
	echo -e "\033[0m"

$(BIN_TEST_LSTT): $(OBJ_PART_LSTT)  $(OBJ_TEST_LSTT) $(OBJ_PART_STT) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LSTT): $(SRC_TEST_LSTT) $(HDRS_LSTT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LSTT) -o $@

$(OBJ_PART_LSTT): $(SRC_PART_LSTT) $(SRC_PART_STT) $(HDRS_LSTT)  dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LSTT) -o $@



#State Machine rules
test_stateMachine_obj: $(BIN_TEST_SMC)
	$(LSS) $(BIN_TEST_SMC)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_SMC)
	echo -e "\033[0m"

$(BIN_TEST_SMC): $(OBJ_PART_SMC)  $(OBJ_TEST_SMC) $(OBJ_PART_STT) $(OBJ_PART_LSTT) $(OBJ_PART_LSCOND) $(OBJ_PART_SCOND) $(OBJ_PART_TRANS) $(OBJ_PART_LTRANS) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_SMC): $(SRC_TEST_SMC) $(HDRS_SMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_SMC) -o $@

$(OBJ_PART_SMC): $(SRC_PART_SMC) $(HDRS_SMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_SMC) -o  $@


test_stateMachine_list: $(BIN_TEST_LSMC)
	$(LSS) $(BIN_TEST_LSMC)
	echo -e  "\033[0;35m"
	$(SAFE) $(BIN_TEST_LSMC)
	echo -e "\033[0m"

#It is becomming too long
#Find a way to reduce it
$(BIN_TEST_LSMC): $(OBJ_PART_LSMC)  $(OBJ_TEST_LSMC) $(OBJ_PART_SMC) $(OBJ_PART_LSCOND) $(OBJ_PART_SCOND) $(OBJ_PART_STT) $(OBJ_PART_LSTT) $(OBJ_PART_TRANS) $(OBJ_PART_LTRANS) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LSMC): $(SRC_TEST_LSMC) $(HDRS_LSMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LSMC) -o $@

$(OBJ_PART_LSMC): $(SRC_PART_LSMC) $(HDRS_LSMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LSMC) -o  $@

