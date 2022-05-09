

#SAFE=echo

#Project parts
DIRMAKE_GATE=Gate
ALLDIRS+=$(DIRMAKE_GATE)

defualt: test

test: gate_tests

bin_tests: gate_bin_tests

clean:
	make -C ../../ clean

#Gate rules
gate_bin_tests:
	$(SAFE) make -C $(DIRMAKE_GATE) bin_tests

gate_tests:
	$(SAFE) make -C $(DIRMAKE_GATE)
