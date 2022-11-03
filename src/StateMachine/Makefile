# Makefile StateMachine
#SAFE=echo

## Imports

ROOTDIR=$(realpath ../../)

ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Watch

WDIR=$(MODULE_STATEMACHINE)

## Module  files
### Folders

DIR_SMC_TRANSITION=$(MODULE_STATEMACHINE)/Transition
DIR_SMC_CONDITION=$(MODULE_STATEMACHINE)/Condition
DIR_SMC_STATE=$(MODULE_STATEMACHINE)/State
DIR_SMC_BODY=$(MODULE_STATEMACHINE)/Body

## Local rules
test: test_all

test_all: test_mod test_side_mod

test_side_mod:
	$(SAFE) $(MKC) $(DIR_SMC_TRANSITION) test_side_mod
	$(SAFE) $(MKC) $(DIR_SMC_STATE) test_side_mod
	$(SAFE) $(MKC) $(DIR_SMC_CONDITION) test_side_mod
	$(SAFE) $(MKC) $(DIR_SMC_BODY) test_side_mod

test_mod:
	$(SAFE) $(MKC) $(DIR_SMC_TRANSITION) test_mod
	$(SAFE) $(MKC) $(DIR_SMC_STATE) test_mod
	$(SAFE) $(MKC) $(DIR_SMC_CONDITION) test_mod
	$(SAFE) $(MKC) $(DIR_SMC_BODY) test_mod

bin_tests:
	$(SAFE) $(MKC) $(DIR_SMC_TRANSITION) bin_tests
	$(SAFE) $(MKC) $(DIR_SMC_STATE) bin_tests
	$(SAFE) $(MKC) $(DIR_SMC_CONDITION) bin_tests
	$(SAFE) $(MKC) $(DIR_SMC_BODY) bin_tests

full_mod:
	$(SAFE) $(MKC) $(DIR_SMC_TRANSITION) full_mod
	$(SAFE) $(MKC) $(DIR_SMC_STATE) full_mod
	$(SAFE) $(MKC) $(DIR_SMC_CONDITION) full_mod
	$(SAFE) $(MKC) $(DIR_SMC_BODY) full_mod

