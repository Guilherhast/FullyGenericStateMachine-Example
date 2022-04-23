#SAFE=echo

CC=$(shell which gcc)

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
SRC_PART_SMC=$(DIR_PART_SMC)/stateMachine.part.c
SRC_TEST_SMC=$(SRC_PART_SMC:.part.c=.test.c)
OBJ_PART_SMC=$(TMPDIR)/$(notdir $(SRC_PART_SMC:.c=.o))
OBJ_TEST_SMC=$(TMPDIR)/$(notdir $(SRC_TEST_SMC:.c=.o))
BIN_TEST_SMC=$(OBJ_TEST_SMC:.o=.bin)

#Genral rules
defualt: dirs test

test: test_objs test_lists

#test_objs: test_state_obj test_stateCondition_obj test_stateMachine_obj
test_objs:  test_stateCondition_obj

#test_lists: test_state_list test_stateCondition_list
test_lists: test_stateCondition_list

bin_tests: $(BIN_TEST_SCOND) $(BIN_TEST_SMC) $(BIN_TEST_STT)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs:
	$(SAFE) mkdir -p $(TMPDIR)

#Dependencies Rules

$(DEP_LST):
	$(SAFE) make -C $(FOLDER_LST) $@

#State condition rules
test_stateCondition_obj: $(BIN_TEST_SCOND)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_SCOND)
	$(SAFE) $(BIN_TEST_SCOND)
	echo -e "\033[0m"

$(BIN_TEST_SCOND): $(OBJ_PART_SCOND)  $(OBJ_TEST_SCOND)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_SCOND): $(SRC_TEST_SCOND) $(HDRS_SCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_SCOND) -o $@

$(OBJ_PART_SCOND): $(SRC_TEST_SCOND) $(HDRS_SCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_SCOND) -o $@

test_stateCondition_list: $(BIN_TEST_LSCOND)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_LSCOND)
	$(SAFE) $(BIN_TEST_LSCOND)
	echo -e "\033[0m"

$(BIN_TEST_LSCOND): $(OBJ_PART_LSCOND) $(OBJ_PART_SCOND) $(OBJ_TEST_LSCOND) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LSCOND): $(SRC_TEST_LSCOND) $(HDRS_LSCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LSCOND) -o $@

$(OBJ_PART_LSCOND): $(SRC_TEST_LSCOND) $(HDRS_LSCOND) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LSCOND) -o $@

#State rules
test_state_all: test_state_obj test_state_list

test_state_obj: $(BIN_TEST_STT)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_STT)
	$(SAFE) $(BIN_TEST_STT)
	echo -e "\033[0m"

$(BIN_TEST_STT): $(OBJ_PART_STT)  $(OBJ_TEST_STT)
	$(SAFE) $(CC) $(OBJ_PART_STT) $(OBJ_TEST_STT) $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_STT): $(SRC_TEST_STT) $(HDRS_STT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_STT) -o $@

$(OBJ_PART_STT): $(SRC_PART_STT) $(HDRS_STT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_STT) -o $@

test_state_list: $(BIN_TEST_LSTT)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_LSTT)
	$(SAFE) $(BIN_TEST_LSTT)
	echo -e "\033[0m"

$(BIN_TEST_LSTT): $(OBJ_PART_LSTT)  $(OBJ_TEST_LSTT) $(OBJ_PART_STT) $(DEP_LST)
	$(SAFE) $(CC) $^ $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LSTT): $(SRC_TEST_LSTT) $(HDRS_LSTT) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LSTT) -o $@

$(OBJ_PART_LSTT): $(SRC_PART_LSTT) $(SRC_PART_STT) $(HDRS_LSTT)  dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LSTT) -o $@



#State rules
test_stateMachine_obj: $(BIN_TEST_SMC)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_SMC)
	$(SAFE) $(BIN_TEST_SMC)
	echo -e "\033[0m"

$(BIN_TEST_SMC): $(OBJ_PART_SMC)  $(OBJ_TEST_SMC)
	$(SAFE) $(CC) $(OBJ_PART_SMC) $(OBJ_TEST_SMC) $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_SMC): $(SRC_TEST_SMC) $(HDRS_SMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_SMC) -o $@

$(OBJ_PART_SMC): $(SRC_PART_SMC) $(HDRS_SMC) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_SMC) -o  $@

