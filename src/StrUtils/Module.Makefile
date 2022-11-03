### Module strUtils
MODULE_STRUTILS=$(SRC_DIR)/StrUtils
MODOBJ_STRUTILS=$(TST_DIR)/strUtils.o

$(MODOBJ_STRUTILS): $(shell find $(MODULE_STRUTILS) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_STRUTILS) full_mod

