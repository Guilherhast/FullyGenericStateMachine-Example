#SAFE=echo
WATCHCMD=test
WATCHDIR=.
FNDARGS=-name 'Makefile' -o -name '*.[hc]'

#Project parts
#Gate
#IManager
DIRMAKE_INM=IManager
ALLDIRS+=$(DIRMAKE_INM)

DIRMAKE_GATE=Gate
ALLDIRS+=$(DIRMAKE_GATE)


#Rules
default: test

test: gate_tests

bin_tests: gate_bin_tests

clean:
	make -C ../../ clean

watch:
	find $(WATCHDIR) $(FNDARGS) | entr -ncc make $(WATCHCMD)

#IManager rules
inm_bin_tests:
	$(SAFE) make -C $(DIRMAKE_INM) bin_tests

inm_tests:
	$(SAFE) make -C $(DIRMAKE_INM)

#Gate rules
gate_bin_tests:
	$(SAFE) make -C $(DIRMAKE_GATE) bin_tests

gate_tests:
	$(SAFE) make -C $(DIRMAKE_GATE)

