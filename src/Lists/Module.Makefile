### Module Lists
MODULE_LIST=$(SRC_DIR)/Lists
MODOBJ_LIST=$(TARGET_DIR)/list.o

$(MODOBJ_LIST): $(shell find $(MODULE_LIST) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_LIST) full_mod BUILD=$(BUILD)

## Adding to all modules
ALL_MODOBJS+=$(MODOBJ_LIST)
