SAFE=echo

CC=$(shell which gcc)

#Compiler flags
CFLAGS = -c -Wall -g3
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

TST_LIBS = -lcheck -lm -lpthread -lrt
COV_LIBS = -lgcov -coverage

#Directories
MIRRORDIR=../../test/src/
TMPDIR=$(MIRRORDIR)/Network
#ALLDIRS=$(TMPDIR)/StateCondition

#State condition files
SRC_PNET=network.part.c
SRC_TNET=network.test.c
OPNET=$(TMPDIR)/$(SRC_PNET:.c=.o)
OTNET=$(TMPDIR)/$(SRC_TSCOND:.c=.o)
BTNET=$(OTSCOND:.o=.bin)


#Genral rules
defualt: dirs test

test: test_network

clean:
	$(SAFE) rm $(TMPDIR)/*

dirs:
	$(SAFE) mkdir -p $(ALLDIRS)

#State condition rules
test_network: $(BTNET)
	echo -e  "\033[0;35m"
	$(SAFE) $(BTNET)
	echo -e "\033[0m"

$(BTNET): $(OPNET)  $(OTSCOND)
	$(SAFE) $(CC) $(OPNET) $(OTNET) $(TST_LIBS) $(COV_LIBS) -o $(BTSCOND)

$(OTNET): $(SRC_TSCOND)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_TNET) -o $(OTSCOND)

$(OPNET): $(SRC_TNET)
	$(SAFE) gcc $(CFLAGS) $(PROFILE_FLAGS) $(SRC_PNET) -o $(OPNET)

