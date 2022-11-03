# Makefile Commander

## Import config
ROOTDIR=$(realpath ../../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Module files
SRC_BASE=state
MODULE_DIRECTORY=$(MODULE_STATEMACHINE)/State

## Side module info
HAS_SIDEMOD=true

SIDEMOD_SUFIX=List

## Dependencies
DEP_MOD=
DEP_SIDE_MOD=$(DEP_MOD) $(OBJ_MOD_PART) $(MODOBJ_LIST)

# System
include $(RULES_MAKE)
