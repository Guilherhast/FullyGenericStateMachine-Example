#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../state.h"
#include "../stateCondition.h"

void trnFunc(StateMachine *smc) {}

START_TEST(test_transition_create) {
  int d;

  Transition *trnReal, *trnTrigger;

  char name[] = "TESTNAME";

  void *data = &d;
  State *stt = State_create(name, NULL, NULL, NULL, NULL, NULL);

  trnReal = Transition_create(stt, stt->name, &trnFunc, false, data);
  trnTrigger = Transition_create(NULL, name, &trnFunc, true, data);
  // trn = Transition_create(stt, &trnFunc, data, true);
  // ck_assert(trn->temporary);

  // Checks for realTransition
  ck_assert_ptr_eq(trnReal->stateTo, stt);

  ck_assert_ptr_ne(trnReal->stateTo->name, trnReal->stateToName);

  ck_assert_str_eq(trnReal->stateToName, name);

  ck_assert(!trnReal->isTrigger);

  ck_assert_ptr_eq(trnReal->data, data);
  ck_assert_ptr_eq(trnReal->tFunc, &trnFunc);

  // Checks for realTransition
  ck_assert_ptr_eq(trnTrigger->stateTo, NULL);

  ck_assert_ptr_ne(trnTrigger->stateToName, name);

  ck_assert_str_eq(trnTrigger->stateToName, name);

  ck_assert(trnTrigger->isTrigger);

  ck_assert_ptr_eq(trnTrigger->data, data);
  ck_assert_ptr_eq(trnTrigger->tFunc, &trnFunc);

  Transition_free(trnReal);
  Transition_free(trnTrigger);
  State_free(stt);
}
END_TEST

START_TEST(test_transition_createError) {
  int d;

  Transition *trn1, *trn2, *trn3, *trn4;

  char name[] = "TESTNAME";

  void *data = &d;

  State *stt = State_create(name, NULL, NULL, NULL, NULL, NULL);

  trn1 = Transition_create(NULL, "Other state", NULL, false, data);
  trn2 = Transition_create(stt, "Other state", NULL, false, data);
  trn3 = Transition_create(stt, "Other state", &trnFunc, false, data);
  trn4 = Transition_create(stt, name, &trnFunc, true, data);

  // trn = Transition_create(stt, &trnFunc, data, true);
  // ck_assert(trn->temporary);

  ck_assert_ptr_null(trn1);
  ck_assert_ptr_null(trn2);
  ck_assert_ptr_null(trn3);
  ck_assert_ptr_null(trn4);

  State_free(stt);
}
END_TEST

/*
START_TEST(test_transition_createTmp) {
int s, d;

Transition *trn;

void *stt = &s, *data = &d;
trn = Transition_createTmp(stt, &trnFunc, data);

ck_assert(trn->temporary);
ck_assert_ptr_eq(trn->stateTo, stt);
ck_assert_ptr_eq(trn->data, data);
ck_assert_ptr_eq(trn->tFunc, &trnFunc);

Transition_free(trn);
}
END_TEST

START_TEST(test_transition_createPrm) {
int s, d;

Transition *trn;

void *stt = &s, *data = &d;
trn = Transition_createPrm(stt, &trnFunc, data);

ck_assert(!trn->temporary);
ck_assert_ptr_eq(trn->stateTo, stt);
ck_assert_ptr_eq(trn->data, data);
ck_assert_ptr_eq(trn->tFunc, &trnFunc);

Transition_free(trn);
}
END_TEST

*/
Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine Transition");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_transition_create);
  tcase_add_test(tc_sm, test_transition_createError);
  /*
  tcase_add_test(tc_sm, test_transition_createTmp);
  tcase_add_test(tc_sm, test_transition_createPrm);
  */

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
