# Global makefile variables

## Fast Commands
ECE=$(shell which echo) -e
ENE=$(shell which echo) -ne

LSS=$(shell which ls) -d --color=auto
LDS=$(shell which ls) -d1

MK=$(shell which make)
MKC=$(shell which make) -C

RM=$(shell which rm)

DXG=$(shell which doxygen)


## Compiler
CC=$(shell which gcc)

### Compiler flags
BASEFLAGS= -c -Wall
DEBUGFLAGS= -g3
CFLAGS= $(BASEFLAGS) $(DEBUGFLAGS)
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage

COV_LIBS= -lgcov -coverage
TST_LIBS= -lcheck -lm -lpthread -lrt

LIB_FLAGS=$(TST_LIBS) $(COV_LIBS)

#### Debian fix
DVNL=/dev/null
CEMPTY=-x c -o $(DVNL) - >$(DVNL) 2>$(DVNL)
CPROG="int main(){}"

SU=-lsubunit
HASSU=$(shell $(ECE) $(CPROG) | $(CC) $(SU) $(CEMPTY)  ; $(ECE) $$? )

ifeq ($(HASSU),0)
TST_LIBS+= $(SU)
endif

## Files

### Global directories
SRC_DIR=$(ROOTDIR)/src
TST_DIR=$(ROOTDIR)/test
BUILD_DIR=$(ROOTDIR)/bin

###Documentation
META_DIR=$(ROOTDIR)/meta
COV_DIR=$(META_DIR)/coverage
DOC_DIR=$(META_DIR)/html

DOX_CFG=$(ROOTDIR)/docs.config

### Import files
RULES_MAKE=$(ROOTDIR)/Rules.Makefile
MODULE_FIND_ARGS=-type f -name Module.Makefile

ALL_MODULE_MAKES=$(shell find $(SRC_DIR) $(MODULE_FIND_ARGS)	\
				| awk '{print length($0) " " $$0}'			\
				| sort -n										\
				| cut -f2 -d' '									\
				| tr '\n' ' '									\
				)


## Watch command
WCMD=test
FNDARGS=-type f -name 'Makefile' -o -name 'Module.Makefile' -o -name '*.[hc]'

### Files
ALWAYSWATCH=$(RULES_MAKE)	\
			$(ALL_MODULE_MAKES) \
			$(CFG_MAKE) \

## Coverage
GCOV=$(shell which gcovr)
GCOV_FOLDERS=-r $(ROOTDIR)/ --object-directory=$(TST_DIR)/ -o $(COV_DIR)/index.html
GCOV_ARGS=--html-details

GCOV_FLAGS=$(GCOV_FOLDERS) $(GCOV_ARGS)

### Server
PY=$(shell which python3)

PORT=8000

SERVERFLAGS= -m http.server --directory $(META_DIR) $(PORT)

define REDHTML
<!DOCTYPE html>
<html style="display:flex; justify-content: center; background-color: #080808;">
<head>
	<title>Docs</title>
	<style>
	a { background-color: black; color: white; height: 48px;}
		a:hover { background-color: midnightblue; }
	</style>
</head>
<body style="display:flex; max-height: 96px; flex-direction: column; font-size: 48px;">
	<a href="$(notdir $(DOC_DIR))/files.html">Docs</a>
	<a href="$(notdir $(COV_DIR))/index.html">Coverage</a>
</body>
</html>
endef

REDPAGE=$(META_DIR)/index.html

##  Auxiliar variables
COLOR_RED="\033[1;31m"
COLOR_GREEN="\033[1;32m"
COLOR_BLUE="\033[1;34m"
COLOR_YELLOW="\033[1;33m"
COLOR_MAG="\033[0;35m"
COLOR_CYAN="\033[0;36m"
COLOR_RESTORE="\033[0m"

ifndef COLOR_TEST
COLOR_TEST=$(COLOR_MAG)
endif

## Global rules
default: test

color_reset:
	$(ECE) $(COLOR_RESTORE)

clean:
	$(SAFE) rm -rf $(BUILD_DIR) $(TST_DIR) $(META_DIR) $(ENV_CFG)

watch:
	( $(LDS) $(ALWAYSWATCH);		\
	find $(WDIR) $(FNDARGS) ) |		\
	entr -nrc $(MK) color_reset $(WCMD)

dirs: $(TST_DIR) $(BUILD_DIR) $(COV_DIR) $(DOC_DIR)

gcov: $(COV_DIR) $(REDPAGE) test
	$(SAFE) $(GCOV) $(GCOV_FLAGS)

dox:
	$(SAFE) $(DXG) $(DOX_CFG)

doc: gcov dox

export REDHTML
$(REDPAGE): $(COV_DIR)
	$(ECE) "$$REDHTML" > $(REDPAGE)

serve: doc
	$(SAFE) $(PY) $(SERVERFLAGS)

count:
	$(SAFE) find $(SRC_DIR) -type f  | $(SAFE) xargs wc -l | $(SAFE) sort -n
	$(ENE) "Files count: " ; $(SAFE) find $(SRC_DIR) -type f | $(SAFE) wc -l

$(TST_DIR):
	$(SAFE) mkdir -p $(TST_DIR)

$(BUILD_DIR):
	$(SAFE) mkdir -p $(BUILD_DIR)

$(COV_DIR):
	$(SAFE) mkdir -p $(COV_DIR)

$(DOC_DIR):
	$(SAFE) mkdir -p $(COV_DIR)

## Import modules
### Defining SETUP
ifndef BUILD

TARGET_DIR=$(TST_DIR)

else

TARGET_DIR=$(BUILD_DIR)
CFLAGS=$(BASEFLAGS)
PROFILE_FLAGS=

endif

### Importing
include $(ALL_MODULE_MAKES)

## Project
### Project files
EXECUTABLE=$(TARGET_DIR)/main.bin

ENV_CFG=$(ROOTDIR)/.env

define ENV_STR
Lock=22:00
Unlock=05:00
Open1=05:30
Open2=07:00
endef

export ENV_STR
$(ENV_CFG):
	[ ! -f $@ ] && $(ECE) "$$ENV_STR" > $@

### Project rules
$(EXECUTABLE): $(MODOBJ_MAIN) $(ALL_MODOBJS)
	$(SAFE) $(CC) $^ $(LIB_FLAGS) -o $@

run: $(EXECUTABLE) $(ENV_CFG)
	$(LSS) $<
	$(ECE) $(COLOR_GREEN)
	$(SAFE) $(GDB) $< $(ENV_CFG)
	$(ECE) $(COLOR_RESTORE)

build: $(BUILD_DIR)
	$(SAFE) $(MK) BUILD=true $(BUILD_DIR)/$(notdir $(EXECUTABLE))

bin_clear:
	$(SAFE) $(RM) $(BUILD_DIR)/*.o

bin_only:
	$(MKC) $(ROOTDIR) build bin_clear


## System
CONFIG_SOURCED=true
