### Module cfgUtils
MODULE_CFGUTILS=$(SRC_DIR)/CfgUtils
MODOBJ_CFGUTILS=$(TARGET_DIR)/cfgUtils.o

$(MODOBJ_CFGUTILS): $(shell find $(MODULE_CFGUTILS) $(FNDARGS) )
	$(SAFE) $(MKC) $(MODULE_CFGUTILS) full_mod BUILD=$(BUILD)

## Adding to all modules
ALL_MODOBJS+=$(MODOBJ_CFGUTILS)
