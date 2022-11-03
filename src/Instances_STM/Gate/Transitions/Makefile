# Makefile Commander

## Import config
ROOTDIR=$(realpath ../../../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Module files
SRC_BASE=gate.transitions
MODULE_DIRECTORY=$(MODULE_INSTANCES_STATEMACHINE)/Gate/Transitions

## Side module info
HAS_SIDEMOD=false

## Dependencies
DEP_STATEMACHINE=$(MODOBJ_STATEMACHINE) $(MODOBJ_LIST)
DEP_MOD=$(DEP_STATEMACHINE) $(MODOBJ_TESTUTILS) $(MODOBJ_STRUTILS)

# System
include $(RULES_MAKE)
