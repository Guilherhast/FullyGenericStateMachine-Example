#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../consts.h"
#include "../stateMachine.h"

START_TEST(test_stateMachine_create) {

  StateMachine *smc;
  State *stt = malloc(sizeof(State));

  int data[] = {1, 2, 3};

  smc = StateMachine_create(1, stt, NULL, NULL, data);

  ck_assert_int_eq(smc->id, 1);
  ck_assert_ptr_eq(smc->possibleStates, stt);
  ck_assert_ptr_eq(smc->initialState, stt);
  ck_assert_ptr_eq(smc->currentState, stt);
  ck_assert_ptr_eq(smc->stateTo, NULL);
  ck_assert_ptr_eq(smc->next, NULL);

  int *a = (int *)data;

  ck_assert_int_eq(a[0], 1);
  ck_assert_int_eq(a[1], 2);
  ck_assert_int_eq(a[2], 3);
}
END_TEST

START_TEST(test_stateMachine_attatch) {
  StateMachine *smc1, *smc2, *list = NULL;
  State *stt = malloc(sizeof(State));

  smc1 = StateMachine_create(1, stt, NULL, NULL, NULL);
  smc2 = StateMachine_create(2, stt, NULL, NULL, NULL);

  list = StateMachine_attatch(list, smc1);
  list = StateMachine_attatch(smc1, smc2);

  ck_assert_ptr_eq(list, smc1);
  ck_assert_ptr_eq(smc1->next, smc2);
}
END_TEST

START_TEST(test_stateMachine_listAdd) {
  StateMachine *smc1, *smc2, *smc3, *smc4, *list = NULL;
  State *stt = malloc(sizeof(State));

  smc1 = StateMachine_create(1, stt, NULL, NULL, NULL);
  smc2 = StateMachine_create(2, stt, NULL, NULL, NULL);

  smc3 = StateMachine_create(3, stt, NULL, NULL, NULL);
  smc4 = StateMachine_create(4, stt, NULL, NULL, NULL);

  list = StateMachine_listAdd(list, smc1);
  list = StateMachine_listAdd(list, smc2);
  list = StateMachine_listAdd(list, smc3);
  list = StateMachine_listAdd(list, smc4);
  /*
   */

  ck_assert_ptr_eq(list, smc1);
  ck_assert_ptr_eq(smc1->next, smc2);
  ck_assert_ptr_eq(smc2->next, smc3);
  ck_assert_ptr_eq(smc3->next, smc4);
  /*
   */
}
END_TEST

Suite *stateCondition_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State Machine");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_stateMachine_create);
  tcase_add_test(tc_sm, test_stateMachine_attatch);
  tcase_add_test(tc_sm, test_stateMachine_listAdd);
  /*
   */

  suite_add_tcase(s, tc_sm);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = stateCondition_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
