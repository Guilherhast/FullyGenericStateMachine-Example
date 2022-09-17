#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../consts.h"
#include "../stateMachine.h"

#define TESTOK "TESTOK"
#define INITIAL "INITIAL"
#define NEXT "NEXT"

boolean retTrue(void *t) { return true; }

void *testTrans(StateMachine *smc) {
  strcpy(smc->data, TESTOK);
  char *bff = malloc(64 * sizeof(char));
  bff[0] = 'T';
  bff[1] = '\0';
  return bff;
}

void *chA(State *stt, void *data) {
  char *r = malloc(sizeof(char) * 2);
  strcpy(r, "A");
  return r;
}
void *chB(State *stt, void *data) {
  char *r = malloc(sizeof(char) * 2);
  strcpy(r, "B");
  return r;
}

void *upA(State *stt, void *data) {
  char *r = malloc(sizeof(char) * 2);
  strcpy(r, "U");
  return r;
}
void *upB(State *stt, void *data) {
  char *r = malloc(sizeof(char) * 2);
  strcpy(r, "V");
  return r;
}

const void *fmgr = &StateMachine_strMerger;

START_TEST(test_stateMachine_create) {
  time_t now;

  StateMachine *smc;

  int s, n;
  void *stt = &s, *nxt = &n;

  StateNode *sttNode = StateNode_create(stt, nxt);

  int data[] = {1, 2, 3};

  time(&now);
  smc = StateMachine_create(1, sttNode, NULL, fmgr, data);

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

  ck_assert_ptr_eq(smc->merger, fmgr);

  int *a = (int *)data;

  ck_assert_int_eq(a[0], 1);
  ck_assert_int_eq(a[1], 2);
  ck_assert_int_eq(a[2], 3);

  StateMachine_free(smc);
}

END_TEST

START_TEST(test_stateMachine_testAndTransit) {
  StateMachine *smc;

  void *r;
  char testStr[32];

  // Creating the state list
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, NULL, NULL, NULL, chA, NULL);
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, chB, NULL, NULL, NULL);

  StateNode_attatch(initial, next);

  Transition *trn = Transition_createRealShort(next->dt, testTrans, NULL);

  smc = StateMachine_create(1, initial, NULL, fmgr, testStr);
  smc->transition = trn;

  r = StateMachine_testAndTransit(smc);

  ck_assert_str_eq((char *)r, "TAB");

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->data, TESTOK);
  ck_assert_ptr_eq(smc->currentState, next->dt);

  free(r);
  StateMachine_free(smc);
}
END_TEST

START_TEST(test_stateMachine_update) {
  StateMachine *smc;

  void *r;
  char testStr[32];

  // Creating the state list
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, chB, upB, NULL, NULL);
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, NULL, NULL, upA, chA, next);

  // Creating a condition and a transition it needs
  Transition *trn = Transition_createRealShort(next->dt, testTrans, NULL);
  StateConditionNode *cnd =
      StateConditionNode_createFull(retTrue, trn, 0, NULL);

  initial->dt->stateConditionList = cnd;

  smc = StateMachine_create(1, initial, NULL, fmgr, testStr);
  smc->transition = trn;

  r = StateMachine_update(smc);

  ck_assert_str_eq((char *)r, "TABV");

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->data, TESTOK);
  ck_assert_ptr_eq(smc->currentState, next->dt);

  free(r);
  StateMachine_free(smc);
}
END_TEST

START_TEST(test_stateMachine_triggerState) {
  StateMachine *smc;

  void *r;

  char testStr[32];

  TransitionNode *nd =
      TransitionNode_createFullTrigger(NEXT, testTrans, NEXT, NULL);

  // Creating the state list
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, NULL, NULL, NULL, NULL);
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, nd, NULL, NULL, NULL, next);

  // FIXME:
  // This ID management is bad.
  // If you pass the id it id will may repeat
  // Check before passing it
  smc = StateMachine_create(1, initial, NULL, fmgr, testStr);

  r = StateMachine_triggerState(smc, NEXT);

  ck_assert_str_eq((char *)r, "T");

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->data, TESTOK);

  free(r);
  StateMachine_free(smc);
}
END_TEST

START_TEST(test_stateMachine_setState) { //
  StateMachine *smc;

  char testStr[32];

  // Creating the state list
  StateNode *next =
      StateNode_createFull(NEXT, NULL, NULL, NULL, NULL, NULL, NULL);

  TransitionNode *nd =
      TransitionNode_createFullRealFromState(next->dt, NULL, NULL);
  StateNode *initial =
      StateNode_createFull(INITIAL, NULL, nd, NULL, NULL, NULL, next);

  smc = StateMachine_create(1, initial, NULL, fmgr, testStr);
  StateMachine_setState(smc, NEXT);

  ck_assert_ptr_eq(smc->currentState, next->dt);
  ck_assert_str_eq(smc->currentState->name, NEXT);

  StateMachine_free(smc);
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
  tcase_add_test(tc_sm, test_stateMachine_setState);
  tcase_add_test(tc_sm, test_stateMachine_update);

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
