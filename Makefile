#Makefile

#SAFE=echo

#Watch command
WATCHCMD=bin_tests
WATCHDIR=.
FNDARGS=-name 'Makefile' -o -name '*.[hc]'


#Directories
SRC_DIR=src
TST_DIR=test
BUILD_DIR=build
O_FILES = $(addprefix $(TEST_DIR)/, $(P_FILES:.c=.o))
OT_FILES = $(addprefix $(TEST_DIR)/, $(T_FILES:.c=.o))
TBIN_FILES=$(OT_FILES:.o=.bin)
#Not using gcov
#It would take even more time
GCOV=gcovr
GCONV_FLAGS=-r . --html --html-details
#Colors
COLOR_GREEN="\033[1;32m"
COLOR_CYAN="\033[0;36m"
COLOR_RESTORE="\033[0m"
#Project parts
DIRMAKE_SMC=$(SRC_DIR)/StateMachine
DIRMAKE_LST=$(SRC_DIR)/Lists
DIRMAKE_ISN=$(SRC_DIR)/Instances_STM

DIRMAKE_IOM=$(SRC_DIR)/IOManager

DIRMAKE_STRU=$(SRC_DIR)/StrUtils

DIRMAKE_CMDR=$(SRC_DIR)/Commander

DIRMAKE_NET=$(SRC_DIR)/Network
#DIRMAKE_TUT=$(SRC_DIR)/TestUtils

#ALLMAKES:=$(shell find $(SRC_DIR) -type f -name Makefile)
DIRALLMAKES=$(DIRMAKE_SMC)

#$(TESTBINARIES)=$(shel find $(TST_DIR)/ -type f -name '*.test.bin')

#All test bin
ALLTESTBIN= list \
			stateMachine \
			stateMachineList \
			state \
			stateList \
			stateCondition \
			stateConditionList \


ALLTESTPATH=$(addsuffix .test.bin,$(addprefix $(TST_DIR)/,$(ALLTESTBIN)))

default: bin_tests

clean:
	$(SAFE) rm -rf $(BUILD_DIR) $(TST_DIR)

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

$(TST_DIR):
	$(SAFE) mkdir -p $(TST_DIR)

#alltests: stateMachine_bt smc_instances_bt
alltests: list_bt stateMachine_bt io_manager_bt str_utils_bt cmdr_bt

bin_tests: $(TST_DIR) alltests exec_bin_tests

count:
	$(SAFE) find $(SRC_DIR) -type f  | $(SAFE) xargs wc -l | $(SAFE) sort -n
	echo -n "Files count: " ; $(SAFE) find $(SRC_DIR) -type f | $(SAFE) wc -l

exec_bin_tests:
	$(SAFE) cd $(TST_DIR);				\
		for i in *.bin; do				\
			ls --color=auto -d $$i;		\
			echo  -e $(COLOR_CYAN);     \
			$(SAFE) ./$$i || exit 1;    \
			echo -e $(COLOR_RESTORE);   \
		done

#Binary tests
echoTests:
	echo $(ALLTESTPATH)

list_bt: $(shell find $(DIRMAKE_LST) -type f )
	$(SAFE) make -C $(DIRMAKE_LST) bin_tests

stateMachine_bt: $(shell find $(DIRMAKE_SMC) -type f )
	$(SAFE) make -C $(DIRMAKE_SMC) bin_tests

smc_instances_bt: $(shell find $(DIRMAKE_ISN) -type f )
	$(SAFE) make -C $(DIRMAKE_ISN) bin_tests

io_manager_bt: $(shell find $(DIRMAKE_IOM) -type f )
	$(SAFE) make -C $(DIRMAKE_IOM) bin_tests

str_utils_bt: $(shell find $(DIRMAKE_STRU) -type f )
	$(SAFE) make -C $(DIRMAKE_STRU) bin_tests

cmdr_bt: $(shell find $(DIRMAKE_CMDR) -type f )
	$(SAFE) make -C $(DIRMAKE_CMDR) bin_tests


network_bt: $(shell find $(DIRMAKE_SMC) -type f )
	$(SAFE) make -C $(DIRMAKE_NET) bin_tests

