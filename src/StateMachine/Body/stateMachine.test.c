#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "../stateMachine.h"

START_TEST(test_stateMachine_create) {
  time_t now;

  StateMachine *smc;

  int s, n;
  void *stt = &s, *nxt = &n;

  StateNode *sttNode = StateNode_create(stt, nxt);

  int data[] = {1, 2, 3};

  time(&now);
  smc = StateMachine_create(1, sttNode, NULL, data);

  int dCreation, dUpdate, dInfo, dChange;

  dCreation = difftime(smc->creation, now);
  dUpdate = difftime(smc->lastUpdate, now);
  dInfo = difftime(smc->lastInfo, now);
  dChange = difftime(smc->lastStateChange, now);

  ck_assert_int_eq(dCreation, 0);
  ck_assert_int_eq(dUpdate, 0);
  ck_assert_int_eq(dInfo, 0);
  ck_assert_int_eq(dChange, 0);

  ck_assert_int_eq(smc->id, 1);

  ck_assert_ptr_eq(smc->possibleStates, sttNode);
  ck_assert_ptr_eq(smc->initialState, stt);
  ck_assert_ptr_eq(smc->currentState, stt);
  ck_assert_ptr_eq(smc->stateTo, NULL);

  int *a = (int *)data;

  ck_assert_int_eq(a[0], 1);
  ck_assert_int_eq(a[1], 2);
  ck_assert_int_eq(a[2], 3);
}
END_TEST

START_TEST(test_stateMachine_testAndTransit) {
  StateMachine *smc;

  //Creating the state list
  StateNode *initial = StateNode_createFull("Initial",NULL,NULL,NULL,NULL,NULL,NULL);
  StateNode *next = StateNode_createFull("Next",NULL,NULL,NULL,NULL,NULL,NULL);
  StateNode_attatch(initial,next);

  smc = StateMachine_create(1, initial, NULL, NULL);
  smc->stateTo = next->dt;

  ck_assert_ptr_eq(smc->stateTo,next->dt);

  StateMachine_testAndTransit(smc);

  ck_assert_ptr_null(smc->stateTo);
  ck_assert_ptr_eq(smc->currentState,next->dt);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State Machine");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_stateMachine_create);
  tcase_add_test(tc_sm, test_stateMachine_testAndTransit);
  /*
  tcase_add_test(tc_sm, test_stateMachine_attatch);
  tcase_add_test(tc_sm, test_stateMachine_listAdd);
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
