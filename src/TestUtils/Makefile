#SAFE=echo

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

#Directories
ROOTDIR=$(shell realpath ../../)
MIRRORDIR=$(ROOTDIR)/test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#Dependencies
DIR_LST=../Lists
HDR_LST=list.h
DEP_HDR_LST=$(DIR_LST)/$(HDR_LST)

#List files
DIR_TUT=.
SRC_PART_TUT=$(DIR_TUT)/testUtils.c
OBJ_PART_TUT=$(TMPDIR)/$(notdir $(SRC_PART_TUT:.c=.o))

#General rules
defualt: dirs objs

objs:  $(OBJ_PART_TUT)

clean:
	$(SAFE) make -C $(ROOTDIR) clean

dirs: $(TMPDIR)

$(TMPDIR):
	$(SAFE) make -C $(ROOTDIR) test

#List rules
$(OBJ_PART_TUT): $(SRC_PART_TUT) $(DEP_HDR_LST) dirs
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PART_TUT) -o $@

