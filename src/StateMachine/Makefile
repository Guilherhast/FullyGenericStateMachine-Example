#SAFE=echo

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

#Directories
MIRRORDIR=../../test
TMPDIR=$(MIRRORDIR)
#ALLDIRS=$(TMPDIR)/StateCondition $(TMPDIR)/StateMachine $(TMPDIR)/State

#State condition files
SRC_PSCOND=StateCondition/stateCondition.part.c
SRC_TSCOND=$(SRC_PSCOND:.part.c=.test.c)
OPSCOND=$(TMPDIR)/$(notdir $(SRC_PSCOND:.c=.o))
OTSCOND=$(TMPDIR)/$(notdir $(SRC_TSCOND:.c=.o))
BTSCOND=$(OTSCOND:.o=.bin)

#State files
SRC_PSTT=State/state.part.c
SRC_TSTT=$(SRC_PSTT:.part.c=.test.c)
OPSTT=$(TMPDIR)/$(notdir $(SRC_PSTT:.c=.o))
OTSTT=$(TMPDIR)/$(notdir $(SRC_TSTT:.c=.o))

BTSTT=$(OTSTT:.o=.bin)

#State Machine files
SRC_PSMC=StateMachine/stateMachine.part.c
SRC_TSMC=$(SRC_PSMC:.part.c=.test.c)

OPSMC=$(TMPDIR)/$(notdir $(SRC_PSMC:.c=.o))
OTSMC=$(TMPDIR)/$(notdir $(SRC_TSMC:.c=.o))

BTSMC=$(OTSMC:.o=.bin)

#Genral rules
defualt: dirs test

test: test_stateCondition test_state test_stateMachine

bin_tests: $(BTSCOND) $(BTSMC) $(BTSTT)

clean:
	$(SAFE) rm -rf $(TMPDIR)/

dirs:
	$(SAFE) mkdir -p $(TMPDIR)

#State condition rules
test_stateCondition: $(BTSCOND)
	echo -e  "\033[0;35m"
	$(SAFE) $(BTSCOND)
	echo -e "\033[0m"

$(BTSCOND): $(OPSCOND)  $(OTSCOND)
	$(SAFE) $(CC) $(OPSCOND) $(OTSCOND) $(TST_LIBS) $(COV_LIBS) -o $(BTSCOND)

$(OTSCOND): $(SRC_TSCOND)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TSCOND) -o $(OTSCOND)

$(OPSCOND): $(SRC_TSCOND)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PSCOND) -o $(OPSCOND)

#State rules
test_state: $(BTSTT)
	echo -e  "\033[0;35m"
	$(SAFE) $(BTSTT)
	echo -e "\033[0m"

$(BTSTT): $(OPSTT)  $(OTSTT)
	$(SAFE) $(CC) $(OPSTT) $(OTSTT) $(TST_LIBS) $(COV_LIBS) -o $(BTSTT)

$(OTSTT): $(SRC_TSTT)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TSTT) -o $(OTSTT)

$(OPSTT): $(SRC_PSTT)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PSTT) -o $(OPSTT)


#State rules
test_stateMachine: $(BTSMC)
	echo -e  "\033[0;35m"
	$(SAFE) $(BTSMC)
	echo -e "\033[0m"

$(BTSMC): $(OPSMC)  $(OTSMC)
	$(SAFE) $(CC) $(OPSMC) $(OTSMC) $(TST_LIBS) $(COV_LIBS) -o $(BTSMC)

$(OTSMC): $(SRC_TSMC)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TSMC) -o $(OTSMC)

$(OPSMC): $(SRC_PSMC)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PSMC) -o $(OPSMC)

