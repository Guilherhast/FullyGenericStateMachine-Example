#SAFE=echo

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

FNDARGS=-name 'Makefile' -o -name '*.[hc]'

#Directories
ROOTDIR=$(shell realpath ../../)
MIRRORDIR=$(ROOTDIR)/test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#DEPENDENCIES
FOLDER_TUT=../TestUtils
DEP_TUT=$(TMPDIR)/testUtils.o

#List files
HDRS_LST=list.h
DIR_LST=.

SRC_PART_LST=$(DIR_LST)/list.c
SRC_TEST_LST=$(SRC_PART_LST:.c=.test.c)
OBJ_PART_LST=$(TMPDIR)/$(notdir $(SRC_PART_LST:.c=.o))
OBJ_TEST_LST=$(TMPDIR)/$(notdir $(SRC_TEST_LST:.c=.o))

BIN_TEST_LST=$(OBJ_TEST_LST:.o=.bin)

#General rules
defualt: dirs test

test: test_all

test_all: test_list

bin_tests: $(BIN_TEST_LST)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#Dependencies
$(DEP_TUT):
	$(SAFE) make -C $(FOLDER_TUT)

#List rules
watch_list: $(SRC_TEST_LST) $(SRC_PART_LST) $(HDRS_LST) Makefile
	find $(DIR_LST) $(FNDARGS) | entr -ncc make test

test_list: $(BIN_TEST_LST)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_LST)
	$(SAFE) $(BIN_TEST_LST)
	echo -e "\033[0m"

$(BIN_TEST_LST): $(OBJ_PART_LST)  $(OBJ_TEST_LST) $(DEP_TUT)
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_LST): $(SRC_TEST_LST) $(HDRS_LST) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TEST_LST) -o $@

$(OBJ_PART_LST): $(SRC_PART_LST) $(HDRS_LST) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_LST) -o $@

