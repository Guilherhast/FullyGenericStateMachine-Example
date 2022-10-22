### Module Commander
MODULE_COMMANDER=$(SRC_DIR)/Commander
MODOBJ_COMMANDER=$(TST_DIR)/commander.o

$(MODOBJ_COMMANDER): $(shell find $(MODULE_COMMANDER) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_COMMANDER) full_mod

