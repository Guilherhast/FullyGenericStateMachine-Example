#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../gate.test.h"
#include "gate.states.h"

boolean testTrnIsTrigger(void *vTrn) {
  Transition *trn = (Transition *)vTrn;
  return trn->isTrigger;
}
boolean testTrnIsReal(void *vTrn) { return !testTrnIsTrigger(vTrn); }

#define ttit &testTrnIsTrigger
#define ttir &testTrnIsReal

START_TEST(test_GateStateList_baseFactory) {
  // StateList *list = GateStateList_baseFactory();
  StateList *list;
  list = GateStateList_baseFactory();

  ck_assert_list_size((List *)list, 9);
}
END_TEST

START_TEST(test_GateStateList_transitions) {
  // StateList *list = GateStateList_baseFactory();
  StateList *list = GateStateList_createAll();

  ck_assert_list_size((List *)list, 9);

  //State nodes
  StateNode *stt_LOCKED = StateList_searchByName(list, NAME_LOCKED);
  StateNode *stt_CLOSED = StateList_searchByName(list, NAME_CLOSED);

  StateNode *stt_FORCEDOPENING =
      StateList_searchByName(list, NAME_FORCEDOPENING);

  StateNode *stt_OPENING = StateList_searchByName(list, NAME_OPENING);
  StateNode *stt_INTERRUPTEDOPENING =
      StateList_searchByName(list, NAME_INTERRUPTEDOPENING);

  StateNode *stt_FORCEDCLOSING =
      StateList_searchByName(list, NAME_FORCEDCLOSING);

  StateNode *stt_CLOSING = StateList_searchByName(list, NAME_CLOSING);
  StateNode *stt_INTERRUPTEDCLOSING =
      StateList_searchByName(list, NAME_INTERRUPTEDCLOSING);

  StateNode *stt_OPEN = StateList_searchByName(list, NAME_OPEN);

  // Real
  //  Closed states states
  ck_assert_list_sizeWithFunc((List *)stt_LOCKED->dt->transitions, 1, ttir);
  ck_assert_list_sizeWithFunc((List *)stt_CLOSED->dt->transitions, 3, ttir);
  // Act of openning
  ck_assert_list_sizeWithFunc((List *)stt_FORCEDOPENING->dt->transitions, 3,
                              ttir);
  ck_assert_list_sizeWithFunc((List *)stt_OPENING->dt->transitions, 3, ttir);
  // Interrupted actions
  ck_assert_list_sizeWithFunc((List *)stt_INTERRUPTEDOPENING->dt->transitions,
                              3, ttir);
  // Act of closing
  ck_assert_list_sizeWithFunc((List *)stt_INTERRUPTEDCLOSING->dt->transitions,
                              3, ttir);
  ck_assert_list_sizeWithFunc((List *)stt_CLOSING->dt->transitions, 3, ttir);
  ck_assert_list_sizeWithFunc((List *)stt_FORCEDCLOSING->dt->transitions, 3,
                              ttir);
  // Opened state
  ck_assert_list_sizeWithFunc((List *)stt_OPEN->dt->transitions, 2, ttir);

  // Triggers
  //  Closed states states
  ck_assert_list_sizeWithFunc((List *)stt_LOCKED->dt->transitions, 1, ttit);
  ck_assert_list_sizeWithFunc((List *)stt_CLOSED->dt->transitions, 3, ttit);
  // Act of openning
  ck_assert_list_sizeWithFunc((List *)stt_FORCEDOPENING->dt->transitions, 2,
                              ttit);
  ck_assert_list_sizeWithFunc((List *)stt_OPENING->dt->transitions, 2, ttit);
  // Interrupted actions
  ck_assert_list_sizeWithFunc((List *)stt_INTERRUPTEDOPENING->dt->transitions,
                              4, ttit);
  ck_assert_list_sizeWithFunc((List *)stt_INTERRUPTEDCLOSING->dt->transitions,
                              4, ttit);
  // Act of closing
  ck_assert_list_sizeWithFunc((List *)stt_CLOSING->dt->transitions, 2, ttit);
  ck_assert_list_sizeWithFunc((List *)stt_FORCEDCLOSING->dt->transitions, 2,
                              ttit);
  // Opened state
  ck_assert_list_sizeWithFunc((List *)stt_OPEN->dt->transitions, 2, ttit);
}
END_TEST

START_TEST(test_GateStateList_conditions) {
  // StateList *list = GateStateList_baseFactory();
  StateList *list = GateStateList_createAll();

  ck_assert_list_size((List *)list, 9);

  StateNode *stt_LOCKED = StateList_searchByName(list, NAME_LOCKED);
  StateNode *stt_CLOSED = StateList_searchByName(list, NAME_CLOSED);

  ck_assert_list_size((List *)stt_CLOSED->dt->stateConditionList, 2);
  ck_assert_list_size((List *)stt_LOCKED->dt->stateConditionList, 1);
}
END_TEST


Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate states");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_GateStateList_baseFactory);
  tcase_add_test(tc_sm, test_GateStateList_transitions);
  tcase_add_test(tc_sm, test_GateStateList_conditions);

  suite_add_tcase(s, tc_sm);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = default_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
