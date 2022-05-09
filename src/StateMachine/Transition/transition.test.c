#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../state.h"
#include "../stateCondition.h"

void trnFunc(StateMachine *smc) {}

START_TEST(test_transition_create) {
  int d;

  Transition *trn;

  char name[] = "TESTNAME";

  void *data = &d;
  State *stt = State_create(name, NULL, NULL, NULL, NULL, NULL);

  trn = Transition_create(stt, stt->name, &trnFunc, data);
  // trn = Transition_create(stt, &trnFunc, data, true);
  // ck_assert(trn->temporary);

  ck_assert_ptr_eq(trn->stateTo, stt);

  ck_assert_ptr_ne(trn->stateTo->name, trn->stateToName);

  ck_assert_str_eq(trn->stateToName, name);

  ck_assert_ptr_eq(trn->data, data);
  ck_assert_ptr_eq(trn->tFunc, &trnFunc);

  Transition_free(trn);
  State_free(stt);
}
END_TEST

START_TEST(test_transition_createError) {
  int d;

  Transition *trn1, *trn2, *trn3;

  char name[] = "TESTNAME";

  void *data = &d;

  State *stt = State_create(name, NULL, NULL, NULL, NULL, NULL);

  trn1 = Transition_create(NULL, "Other state", NULL, data);
  trn2 = Transition_create(stt, "Other state", NULL, data);
  trn3 = Transition_create(stt, "Other state", &trnFunc, data);

  // trn = Transition_create(stt, &trnFunc, data, true);
  // ck_assert(trn->temporary);

  ck_assert_ptr_null(trn1);
  ck_assert_ptr_null(trn2);
  ck_assert_ptr_null(trn3);

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
