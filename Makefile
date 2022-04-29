#Makefile

#SAFE=echo


#Directories
SRC_DIR=src
TST_DIR=test
BUILD_DIR=build

O_FILES = $(addprefix $(TEST_DIR)/, $(P_FILES:.c=.o))
OT_FILES = $(addprefix $(TEST_DIR)/, $(T_FILES:.c=.o))

TBIN_FILES=$(OT_FILES:.o=.bin)

#Not using gcov
#It would take even more time
GCOV = gcovr
GCONV_FLAGS = -r . --html --html-details


#Project parts
DIRMAKE_SMC=$(SRC_DIR)/StateMachine
DIRMAKE_LST=$(SRC_DIR)/Lists
DIRMAKE_ISN=$(SRC_DIR)/Instances_STM
DIRMAKE_NET=$(SRC_DIR)/Network

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

$(TST_DIR):
	$(SAFE) mkdir -p $(TST_DIR)

#alltests: stateMachine_bt smc_instances_bt
alltests: stateMachine_bt list_bt $(ALLTESTPATH)


bin_tests: $(TST_DIR) alltests exec_bin_tests

count:
	echo -n "Files count: " ; $(SAFE) find $(SRC_DIR) -type f | $(SAFE) wc -l
	$(SAFE) find $(SRC_DIR) -type f  | $(SAFE) xargs wc -l | $(SAFE) sort -n

exec_bin_tests:
	echo -e  "\033[0;36m"
	$(SAFE) cd $(TST_DIR); for i in *.bin; do  echo $$i; $(SAFE) ./$$i;  done
	echo -e "\033[0m"

#Binary tests
echoTests:
	echo $(ALLTESTPATH)

stateMachine_bt:
	$(SAFE) make -C $(DIRMAKE_SMC) bin_tests

smc_instances_bt:
	$(SAFE) make -C $(DIRMAKE_ISN) bin_tests

network_bt:
	$(SAFE) make -C $(DIRMAKE_NET) bin_tests

list_bt:
	$(SAFE) make -C $(DIRMAKE_LST) bin_tests
