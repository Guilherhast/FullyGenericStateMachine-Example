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

#List files
HDRS_STRU=strUtils.h
DIR_STRU=.

SRC_PART_STRU=$(DIR_STRU)/strUtils.c
SRC_TEST_STRU=$(SRC_PART_STRU:.c=.test.c)
OBJ_PART_STRU=$(TMPDIR)/$(notdir $(SRC_PART_STRU:.c=.o))
OBJ_TEST_STRU=$(TMPDIR)/$(notdir $(SRC_TEST_STRU:.c=.o))

BIN_TEST_STRU=$(OBJ_TEST_STRU:.o=.bin)

#General rules
default: dirs test

test: test_all

test_all: test_stru

bin_tests: $(BIN_TEST_STRU)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#Dependencies

#List rules
watch_stru: $(SRC_TEST_STRU) $(SRC_PART_STRU) $(HDRS_STRU) Makefile
	find $(DIR_STRU) $(FNDARGS) | entr -ncc make test

test_stru: $(BIN_TEST_STRU)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_STRU)
	$(SAFE) $(BIN_TEST_STRU)
	echo -e "\033[0m"

$(BIN_TEST_STRU): $(OBJ_PART_STRU)  $(OBJ_TEST_STRU)
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_STRU): $(SRC_TEST_STRU) $(HDRS_STRU) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_STRU): $(SRC_PART_STRU) $(HDRS_STRU) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

