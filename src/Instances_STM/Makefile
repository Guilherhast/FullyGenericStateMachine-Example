# Makefile Instances StateMachine
#SAFE=echo

## Imports

ROOTDIR=$(realpath ../../)

ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Watch

WDIR=$(MODULE_INSTANCES_STATEMACHINE)
MODULE_DIRECTORY=$(MODULE_INSTANCES_STATEMACHINE)

## Module  files
### Folders

DIR_INSTANCE_COMMANDER=$(MODULE_DIRECTORY)/Commander_inst
DIR_INSTANCE_GATE=$(MODULE_DIRECTORY)/Gate
DIR_INSTANCE_MANAGER=$(MODULE_DIRECTORY)/IManager

## Local rules
test: test_all

test_all: test_mod

test_mod:
	$(SAFE) $(MKC) $(DIR_INSTANCE_COMMANDER) test_mod
	$(SAFE) $(MKC) $(DIR_INSTANCE_GATE) test_mod
	$(SAFE) $(MKC) $(DIR_INSTANCE_MANAGER) test_mod

bin_tests:
	$(SAFE) $(MKC) $(DIR_INSTANCE_COMMANDER) bin_tests
	$(SAFE) $(MKC) $(DIR_INSTANCE_GATE) bin_tests
	$(SAFE) $(MKC) $(DIR_INSTANCE_MANAGER) bin_tests

full_mod:
	$(SAFE) $(MKC) $(DIR_INSTANCE_COMMANDER) full_mod
	$(SAFE) $(MKC) $(DIR_INSTANCE_GATE) full_mod
	$(SAFE) $(MKC) $(DIR_INSTANCE_MANAGER) full_mod

