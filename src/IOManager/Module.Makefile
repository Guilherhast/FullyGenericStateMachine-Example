### Module IOManager
MODULE_IOMANAGER=$(SRC_DIR)/IOManager
MODOBJ_IOMANAGER=$(TARGET_DIR)/ioManager.o

$(MODOBJ_IOMANAGER): $(shell find $(MODULE_IOMANAGER) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_IOMANAGER) full_mod BUILD=$(BUILD)

## Adding to all modules
ALL_MODOBJS+=$(MODOBJ_IOMANAGER)
