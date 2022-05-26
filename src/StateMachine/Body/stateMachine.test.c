#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../consts.h"
#include "../stateMachine.h"

#define TESTOK "TESTOK"
#define INITIAL "INITIAL"
#define NEXT "NEXT"

void testTrans(StateMachine *smc) { strcpy(smc->data, TESTOK); }

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

  ck_assert(smc->online);

  ck_assert_int_eq(dCreation, 0);
  ck_assert_int_eq(dUpdate, 0);
  ck_assert_int_eq(dInfo, 0);
  ck_assert_int_eq(dChange, 0);

  ck_assert_int_eq(smc->id, 1);

  ck_assert_ptr_eq(smc->possibleStates, sttNode);
  ck_assert_ptr_eq(smc->initialState, stt);
  ck_assert_ptr_eq(smc->currentState, stt);
  ck_assert_ptr_eq(smc->transition, NULL);

  int *a = (int *)data;

  ck_assert_int_eq(a[0], 1);
  ck_assert_int_eq(a[1], 2);
  ck_assert_int_eq(a[2], 3);

  StateMachine_free(smc);
}
END_TEST

START_TEST(test_stateMachine_testAndTransit) {
  StateMachine *smc;

  char testStr[32];

  // Creating the state list
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, NULL, NULL, NULL, NULL, NULL);
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, NULL, NULL, NULL, NULL);
  StateNode_attatch(initial, next);

  // Transition *trn = Transition_createTmp(next->dt, testTrans, NULL);
  Transition *trn = Transition_createRealShort(next->dt, testTrans, NULL);

  smc = StateMachine_create(1, initial, NULL, testStr);
  smc->transition = trn;

  StateMachine_testAndTransit(smc);

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->data, TESTOK);
  ck_assert_ptr_eq(smc->currentState, next->dt);

  StateMachine_free(smc);
}
END_TEST

START_TEST(test_stateMachine_triggerState) {
  StateMachine *smc;

  char testStr[32];

  // Transition *trn = Transition_createTmp(next->dt, testTrans, NULL);
  TransitionNode *nd =
      TransitionNode_createFullTrigger(NEXT, testTrans, NEXT, NULL);

  // Creating the state list
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, nd, NULL, NULL, NULL, NULL);
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, NULL, NULL, NULL, NULL);
  StateNode_attatch(initial, next);

  // FIXME:
  // This ID management is bad.
  // If you pass the id it id will maybe repeat
  smc = StateMachine_create(1, initial, NULL, testStr);
  // smc->transition = trn;

  StateMachine_triggerState(smc, NEXT);

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->data, TESTOK);

  StateMachine_free(smc);
  /*
   */
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State Machine");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_stateMachine_create);
  tcase_add_test(tc_sm, test_stateMachine_testAndTransit);
  tcase_add_test(tc_sm, test_stateMachine_triggerState);
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
