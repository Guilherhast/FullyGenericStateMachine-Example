### Module strUtils
MODULE_STRUTILS=$(SRC_DIR)/StrUtils
MODOBJ_STRUTILS=$(TARGET_DIR)/strUtils.o

$(MODOBJ_STRUTILS): $(shell find $(MODULE_STRUTILS) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_STRUTILS) full_mod

## Adding to all modules
ALL_MODOBJS+=$(MODOBJ_STRUTILS)
