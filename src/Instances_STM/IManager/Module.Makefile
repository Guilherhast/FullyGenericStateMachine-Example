### Module strUtils
SUBMODULE_INSTANCES_MANAGER_IMANAGER=$(MODULE_INSTANCES_STATEMACHINE)/IManager
MODOBJ_INSTANCES_MANAGER_COMMANDER=$(TST_DIR)/instancesManager.o

$(MODOBJ_INSTANCES_MANAGER_IMANAGER): $(shell find $(SUBMODULE_INSTANCES_MANAGER_IMANAGER) $(FNDARGS) )
	$(SAFE) $(MKC) $(SUBMODULE_INSTANCES_MANAGER_IMANAGER) full_mod

