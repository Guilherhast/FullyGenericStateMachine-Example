### Module Commander
MODULE_COMMANDER=$(SRC_DIR)/Commander
MODOBJ_COMMANDER_OBJ=$(TARGET_DIR)/commander.o
MODOBJ_COMMANDER_LIST=$(TARGET_DIR)/commanderList.o

MODOBJ_COMMANDER=$(MODOBJ_COMMANDER_OBJ) $(MODOBJ_COMMANDER_LIST)

$(MODOBJ_COMMANDER): $(shell find $(MODULE_COMMANDER) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_COMMANDER) full_mod

## Adding to all modules
ALL_MODOBJS+=$(MODOBJ_COMMANDER)