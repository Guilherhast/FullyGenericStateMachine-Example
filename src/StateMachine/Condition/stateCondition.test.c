#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../state.h"
#include "../stateCondition.h"

boolean cf_false(void *data) { return false; };
boolean cf_true(void *data) { return true; };

void trnF(StateMachine *smc);

START_TEST(test_stateCondition_create) {
  Transition trn;

  StateCondition *sttCond;

  sttCond = StateCondition_create(&cf_true, &trn, 1);

  ck_assert_int_eq(sttCond->priority, 1);
  ck_assert_ptr_eq(sttCond->transition, &trn);

  StateCondition_free(sttCond);
}
END_TEST

START_TEST(test_stateCondition_priorityComparator) {
  Transition trn;

  int r11, r12, r13, r23, r31;

  void *sttCond1, *sttCond2, *sttCond3;

  sttCond1 = StateCondition_create(&cf_true, &trn, 1);
  sttCond2 = StateCondition_create(&cf_true, &trn, 2);
  sttCond3 = StateCondition_create(&cf_true, &trn, 3);

  r11 = priorityComparator(sttCond1, sttCond1);
  r12 = priorityComparator(sttCond1, sttCond2);
  r13 = priorityComparator(sttCond1, sttCond3);
  r23 = priorityComparator(sttCond2, sttCond3);
  r31 = priorityComparator(sttCond3, sttCond1);

  ck_assert_int_eq(r11, 0);
  ck_assert_int_eq(r12, -1);
  ck_assert_int_eq(r13, -2);
  ck_assert_int_eq(r23, -1);
  ck_assert_int_eq(r31, 2);

  StateCondition_free(sttCond1);
}
END_TEST

START_TEST(test_stateCondition_check) {
  Transition trn1, trn2;

  StateCondition *sttCond1, *sttCond2;
  boolean tst_true, tst_false;

  sttCond1 = StateCondition_create(&cf_true , &trn1, 1);
  sttCond2 = StateCondition_create(&cf_false, &trn2, 2);

  tst_true = StateCondition_check(sttCond1, NULL);
  tst_false = StateCondition_check(sttCond2, NULL);

  ck_assert(tst_true);
  ck_assert(!tst_false);

  StateCondition_free(sttCond1);
  StateCondition_free(sttCond2);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State Contition");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_stateCondition_create);
  tcase_add_test(tc_sm, test_stateCondition_priorityComparator);
  tcase_add_test(tc_sm, test_stateCondition_check);

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
