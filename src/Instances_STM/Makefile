#SAFE=echo
WATCHCMD=test
WATCHDIR=.
FNDARGS=-name 'Makefile' -o -name '*.[hc]'

#Project parts
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


#Gate rules
gate_bin_tests:
	$(SAFE) make -C $(DIRMAKE_GATE) bin_tests

gate_tests:
	$(SAFE) make -C $(DIRMAKE_GATE)
