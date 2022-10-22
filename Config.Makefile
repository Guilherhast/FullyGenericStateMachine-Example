# Global makefile variables

## Fast Commands
ECE=echo -e
ENE=echo -ne

LSS=ls -d --color=auto
LDS=ls -d1

MK=make
MKC=make -C


## Compiler
CC=$(shell which gcc)

### Compiler flags
CFLAGS= -c -Wall -g3
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage

TST_LIBS= -lcheck -lm -lpthread -lrt
COV_LIBS= -lgcov -coverage

## Files

### Global directories
SRC_DIR=$(ROOTDIR)/src
TST_DIR=$(ROOTDIR)/test
BUILD_DIR=$(ROOTDIR)/build
COV_DIR=$(ROOTDIR)/coverage

### Import files
RULES_MAKE=$(ROOTDIR)/Rules.Makefile
ALL_MODULE_MAKES=$(shell find $(SRC_DIR) -type f -name Module.Makefile -printf '%p ')

## Watch command
WCMD=test
FNDARGS=-type f -name 'Makefile' -o -name 'Module.Makefile' -o -name '*.[hc]'

### Files
ALWAYSWATCH=$(RULES_MAKE)	\
			$(ALL_MODULE_MAKES) \
			$(CFG_MAKE) \

## Coverage
GCOV=$(shell which gcovr)
GCOV_FOLDERS=-r $(ROOTDIR)/ --object-directory=$(TST_DIR)/ -o $(COV_DIR)/
GCOV_ARGS=--html-details

GCOV_FLAGS=$(GCOV_FOLDERS) $(GCOV_ARGS)

### Server
PY=$(shell which python)

PORT=8000

SERVERFLAGS= -m http.server --directory $(COV_DIR) $(PORT)

REDHTML= '<html>										\
		<head>											\
			<meta http-equiv="refresh"					\
			content="0; url=coverage_details.html" />	\
		</head>											\
	</html>'

REDPAGE=$(COV_DIR)/index.html

##  Auxiliar variables
COLOR_RED="\033[1;31m"
COLOR_GREEN="\033[1;32m"
COLOR_BLUE="\033[1;33m"
COLOR_MAG="\033[0;35m"
COLOR_CYAN="\033[0;36m"
COLOR_RESTORE="\033[0m"

ifndef COLOR_TEST
COLOR_TEST=$(COLOR_MAG)
endif

## Global rules
default: test

clean:
	$(SAFE) rm -rf $(BUILD_DIR) $(TST_DIR) $(COV_DIR)

watch:
	( $(LDS) $(ALWAYSWATCH); find $(WDIR) $(FNDARGS) ) | entr -nrc $(MK) $(WCMD)

dirs: $(TST_DIR) $(BUILD_DIR) $(COV_DIR)

gcov: $(COV_DIR) $(REDPAGE) test
	$(SAFE) $(GCOV) $(GCOV_FLAGS)

$(REDPAGE): $(COV_DIR)
	$(ECE) $(REDHTML) > $(REDPAGE)

serve: gcov
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

## Import modules
include $(ALL_MODULE_MAKES)

## System
CONFIG_SOURCED=true
