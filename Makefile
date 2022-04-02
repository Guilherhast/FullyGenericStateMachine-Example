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
DIRMAKE_ISN=$(SRC_DIR)/Instances_STM
DIRMAKE_NET=$(SRC_DIR)/Network

#ALLMAKES:=$(shell find $(SRC_DIR) -type f -name Makefile)
DIRALLMAKES=$(DIRMAKE_SMC)

#$(TESTBINARIES)=$(shel find $(TST_DIR)/ -type f -name '*.test.bin')

default: bin_tests

clean:
	rm -rf $(BUILD_DIR) $(TST_DIR)

$(TST_DIR):
	mkdir -p $(TST_DIR)

alltests: stateMachine_bt

bin_tests: $(TST_DIR) alltests exec_bin_tests

exec_bin_tests:
	echo -e  "\033[0;36m"
	cd $(TST_DIR); for i in *.bin; do  $(SAFE) ./$$i;  done
	echo -e "\033[0m"

#Binary tests

stateMachine_bt:
	make -C $(DIRMAKE_SMC) bin_tests

smc_instances_bt:
	make -C $(DIRMAKE_ISN) bin_tests

network_bt:
	make -C $(DIRMAKE_NET) bin_tests
