#ifndef GATE_TEST_H
#define GATE_TEST_H

#include "../../TestUtils/testUtils.h"
#include "gate.h"

#define TESTSTR "TESTEDOK"
#define NAME_TEST "TEST"

// State functions
StateList *GateStateList_baseFactory();

// Transitions functions
TransitionList *GateTransitions_createRealTmp(StateList *sttList);
TransitionList *GateTransitions_createTriggerTmp();

#define dummyState(n)                                                          \
  StateNode_createFull(n, NULL, NULL, NULL, NULL, NULL, NULL)

#endif
