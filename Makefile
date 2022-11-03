# Makefile Project
#SAFE=echo

# Documentation
#
# Every Makefile in this project should have:
#
# Rule:
#
# test: Test if the module is without errors
# bin_tests: Create test binaries but does not run
# full_mod: Create all files needed to import module
#

#TODO
# For production:
# Make the lib generation run without cov

# Imports
ROOTDIR=$(realpath .)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)
endif

# Watch command
WDIR=$(ROOTDIR)

# Tests

ALLTESTSRULES=str_utils_bt \
			list_bt \
			stateMachine_bt	\
			io_manager_bt		\
			cmdr_bt



# Local rules

test: test_all #exec_bin_tests

bin_tests: test_all

test_all: $(ALLTESTSRULES)

exec_bin_tests:
	$(SAFE) cd $(TST_DIR);				\
		for i in *.bin; do				\
			$(LSS) $$i;					\
			$(ECE) $(COLOR_CYAN);	\
			$(SAFE) ./$$i || exit 1;    \
			$(ECE) $(COLOR_RESTORE);   \
		done


# Binary tests

list_bt: $(shell find $(MODULE_LIST) -type f )
	$(SAFE) make -C $(MODULE_LIST) test COLOR_SGST='$(COLOR_CYAN)'

stateMachine_bt: $(shell find $(MODULE_STATEMACHINE) -type f )
	$(SAFE) make -C $(MODULE_STATEMACHINE) test COLOR_SGST='$(COLOR_CYAN)'

smc_instances_bt: $(shell find $(MODULE_INSTANCES_STATEMACHINE) -type f )
	$(SAFE) make -C $(MODULE_INSTANCES_STATEMACHINE) test COLOR_SGST='$(COLOR_CYAN)'

io_manager_bt: $(shell find $(MODULE_IOMANAGER) -type f )
	$(SAFE) make -C $(MODULE_IOMANAGER) test COLOR_SGST='$(COLOR_CYAN)'

str_utils_bt: $(shell find $(MODMODULE_STRUTILS) -type f )
	$(SAFE) make -C $(MODULE_STRUTILS) test COLOR_SGST='$(COLOR_CYAN)'

cmdr_bt: $(shell find $(MODULE_COMMANDER) -type f )
	$(SAFE) make -C $(MODULE_COMMANDER) test COLOR_SGST='$(COLOR_CYAN)'

