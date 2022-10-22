#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../gate.h"
#include "../gate.test.h"

//You may put it in the transitions file
boolean testTrnIsTrigger(void *vTrn) {
  Transition *trn = (Transition *)vTrn;
  return trn->isTrigger;
}
boolean testTrnIsReal(void *vTrn) { return !testTrnIsTrigger(vTrn); }

#define ttit(v) testTrnIsTrigger(v)
#define ttir(v) testTrnIsReal(v)

START_TEST(test_GateTransitions_createList) {
  StateList *sttList = NULL;
  TransitionList *trnRealList, *trnTriggerList;

  int i = 10;
  char n[2] = "A";
  while (--i) {
    sttList = StateList_add(sttList, dummyState(n));
    ++n[0];
  }

  trnRealList = GateTransitions_createRealTmp(sttList);
  trnTriggerList = GateTransitions_createTriggerTmp();

  ck_assert_list_size((List *)sttList, 9);

  ck_assert_list_size((List *)trnRealList, 9);
  ck_assert_list_size((List *)trnTriggerList, 9);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate Transitions");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_GateTransitions_createList);

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
