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

ALLTESTSRULES=str_utils_bt		\
			cfg_utils_bt		\
			list_bt				\
			stateMachine_bt		\
			io_manager_bt		\
			cmdr_bt				\
			smc_instances_bt
# Colors

COLOR_SGST=$(COLOR_CYAN)

# Local rules

test: test_all #exec_bin_tests

bin_tests: test_all

test_all: $(ALLTESTSRULES)

exec_bin_tests:
	$(SAFE) cd $(TST_DIR);				\
		for i in *.bin; do				\
			$(LSS) $$i;					\
			$(ECE) $(COLOR_CYAN);		\
			$(SAFE) ./$$i || exit 1;    \
			$(ECE) $(COLOR_RESTORE);	\
		done


## Build


# TODO
# Change TST_DIR to TARGET_DIR
# When test use TARGET_DIR = TST_DIR
# When build use TARGET_DIR = BUILD_DIR
#
# Inside full_mod receive TARGET_DIR
# If empty use TST_DIR
# So full_mod_build is full_mod with altered:
# 1. TARGET_DIR
# 2. PROFILE_FLAGS
#

## Binary tests

list_bt: $(shell find $(MODULE_LIST) -type f )
	$(SAFE) $(MKC) $(MODULE_LIST) test COLOR_SGST='$(COLOR_SGST)'

stateMachine_bt: $(shell find $(MODULE_STATEMACHINE) -type f )
	$(SAFE) $(MKC) $(MODULE_STATEMACHINE) test COLOR_SGST='$(COLOR_SGST)'

smc_instances_bt: $(shell find $(MODULE_INSTANCES_STATEMACHINE) -type f )
	$(SAFE) $(MKC) $(MODULE_INSTANCES_STATEMACHINE) test COLOR_SGST='$(COLOR_SGST)'

io_manager_bt: $(shell find $(MODULE_IOMANAGER) -type f )
	$(SAFE) $(MKC) $(MODULE_IOMANAGER) test COLOR_SGST='$(COLOR_SGST)'

str_utils_bt: $(shell find $(MODMODULE_STRUTILS) -type f )
	$(SAFE) $(MKC) $(MODULE_STRUTILS) test COLOR_SGST='$(COLOR_SGST)'

cfg_utils_bt: $(shell find $(MODMODULE_CFGUTILS) -type f )
	$(SAFE) $(MKC) $(MODULE_CFGUTILS) test COLOR_SGST='$(COLOR_SGST)'

cmdr_bt: $(shell find $(MODULE_COMMANDER) -type f )
	$(SAFE) $(MKC) $(MODULE_COMMANDER) test COLOR_SGST='$(COLOR_SGST)'
