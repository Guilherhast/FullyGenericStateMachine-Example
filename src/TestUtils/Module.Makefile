### Module TestUtils
MODULE_TESTUTILS=$(SRC_DIR)/TestUtils

MODOBJ_TESTUTILS=$(TARGET_DIR)/testUtils.o

$(MODOBJ_TESTUTILS): $(shell find $(MODULE_TESTUTILS) $(FNDARGS) )
	$(SAFE)  $(MKC) $(MODULE_TESTUTILS) full_mod