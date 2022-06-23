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
HDRS_IOM=ioManager.h
DIR_IOM=.

SRC_PART_IOM=$(DIR_IOM)/ioManager.c
SRC_TEST_IOM=$(SRC_PART_IOM:.c=.test.c)
OBJ_PART_IOM=$(TMPDIR)/$(notdir $(SRC_PART_IOM:.c=.o))
OBJ_TEST_IOM=$(TMPDIR)/$(notdir $(SRC_TEST_IOM:.c=.o))

BIN_TEST_IOM=$(OBJ_TEST_IOM:.o=.bin)

#General rules
default: dirs test

test: test_all

test_all: test_iom

bin_tests: $(BIN_TEST_IOM)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#Dependencies

#List rules
watch_iom: $(SRC_TEST_IOM) $(SRC_PART_IOM) $(HDRS_IOM) Makefile
	find $(DIR_IOM) $(FNDARGS) | entr -ncc make test

test_iom: $(BIN_TEST_IOM)
	echo -e  "\033[0;35m"
	echo $(BIN_TEST_IOM)
	$(SAFE) $(BIN_TEST_IOM)
	echo -e "\033[0m"

$(BIN_TEST_IOM): $(OBJ_PART_IOM)  $(OBJ_TEST_IOM) 
	$(SAFE) $(CC) $^  $(TST_LIBS) $(COV_LIBS) -o $@

$(OBJ_TEST_IOM): $(SRC_TEST_IOM) $(HDRS_IOM) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

$(OBJ_PART_IOM): $(SRC_PART_IOM) $(HDRS_IOM) dirs
	$(SAFE) $(CC) $(CFLAGS) $(PROFILE_FLAGS) $< -o $@

