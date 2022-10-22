# Makefile Commander

## Import config
ROOTDIR=$(realpath ../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Module files
SRC_BASE=commander
MODULE_DIRECTORY=$(MODULE_COMMANDER)

## Side module info
HAS_SIDEMOD=true

SIDEMOD_SUFIX=List

## Dependencies
DEP_STATEMACHINE_FULL=$(MODOBJ_STATEMACHINE) $(MODOBJ_LIST)
DEP_MOD=$(DEP_STATEMACHINE_FULL) $(MODOBJ_STRUTILS) $(MODOBJ_TESTUTILS)
DEP_SIDE_MOD=$(OBJ_MOD_PART) $(DEP_MOD)

# System
include $(RULES_MAKE)
