# Makefile Main

## Import config
ROOTDIR=$(realpath ../../)
ifndef CONFIG_SOURCED

CFG_MAKE=$(ROOTDIR)/Config.Makefile
include $(CFG_MAKE)

endif

## Files
### Header
HDR_MAIN_MOD=$(MAIN_MODULE)/main.h

### Sources
SRC_MAIN_CORE=$(HDR_MAIN_MOD:.h=.c)
SRC_MAIN_FUNC=$(MAIN_MODULE)/functions.c

### Objects
MODOBJ_MAIN_CORE=$(TARGET_DIR)/$(notdir $(SRC_MAIN_CORE:.c=.o))
MODOBJ_MAIN_FUNC=$(TARGET_DIR)/$(notdir $(SRC_MAIN_FUNC:.c=.o))

## Colors
COLOR_TEST=$(COLOR_RED)

## Rules
### Main rules
$(MODOBJ_MAIN): $(MODOBJ_MAIN_CORE) $(MODOBJ_MAIN_FUNC)
	$(ECE) $(COLOR_MAG) Trying to make obj $(COLOR_RESTORE)

$(MODOBJ_MAIN_CORE): $(SRC_MAIN_CORE) $(HDR_MAIN_MOD) $(TARGET_DIR)
	$(SAFE) $(CC) $(CFLAGS) $< -o $@

$(MODOBJ_MAIN_FUNC): $(SRC_MAIN_FUNC) $(HDR_MAIN_MOD) $(TARGET_DIR)
	$(SAFE) $(CC) $(CFLAGS) $< -o $@

### Genreral rules
test:  test_mod

test_all: test_mod

test_mod: full_mod msg

bin_tests: full_mod

full_mod: $(MODOBJ_MAIN_CORE) $(MODOBJ_MAIN_FUNC)

# Configuration overwrite
msg:
	$(ECE) $(COLOR_TEST) This module has no tests $(COLOR_RESTORE)
