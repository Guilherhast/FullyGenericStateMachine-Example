# Makefile Commander

## Import config
ROOTDIR=$(realpath ../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Module files
SRC_BASE=list
MODULE_DIRECTORY=$(MODULE_LIST)

## Side module info
HAS_SIDEMOD=false

## Dependencies
DEP_MOD=$(MODOBJ_TESTUTILS)

# System
include $(RULES_MAKE)
