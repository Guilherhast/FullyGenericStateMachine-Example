#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "stateMachine.h"

#define INITIAL "INITIAL"
#define NEXT "NEXT"

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

char *upBase(char *c) {
  char *r = malloc(sizeof(char) * 2);
  strcpy(r, c);
  return r;
}
void *upA(State *stt, void *data) { return upBase("A"); }
void *upB(State *stt, void *data) { return upBase("B"); }
void *upC(State *stt, void *data) { return upBase("C"); }
void *upD(State *stt, void *data) { return upBase("D"); }

// const void *mgrF(void *d1, void *d2) { return NULL; }
const void *mgrF = &StateMachine_strMerger;

START_TEST(test_StateMachineNode_create) {
  StateMachineNode *nd;

  int n;
  void *stt = malloc(sizeof(StateMachine)), *nxt = &n;

  nd = StateMachineNode_create(stt, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, stt);
  ck_assert_ptr_eq(nd->next, nxt);

  StateMachineNode_freeWipe(nd);
}
END_TEST

START_TEST(test_StateMachineNode_createFull) {
  StateMachineNode *nd;

  int n, s;
  void *nxt = &n, *stt = &s;

  nd = StateMachineNode_createFull(1, stt, NULL, mgrF, NULL, nxt);

  ck_assert_ptr_nonnull(nd->dt);
  ck_assert_ptr_eq(nd->next, nxt);

  StateMachineNode_freeWipe(nd);
}
END_TEST

START_TEST(test_StateMachine_idMatch) {
  int s;
  void *stt = &s;

  unsigned int id, *p = &id;

  StateMachine *smc = StateMachine_create(5, stt, NULL, mgrF, NULL);

  id = 5;
  ck_assert(idMatch(smc, p));

  id = 3;
  ck_assert(!idMatch(smc, p));

  StateMachine_free(smc);
}
END_TEST

START_TEST(test_StateMachineList_searchById) {
  StateMachineNode *nd1, *nd2, *nd3, *nd4;
  StateMachineNode *res;
  StateMachineList *list = NULL;

  int s;
  void *stt = &s;

  unsigned int id = 3, *p = &id;

  nd1 = StateMachineNode_createFull(1, stt, NULL, mgrF, NULL, NULL);
  nd2 = StateMachineNode_createFull(2, stt, NULL, mgrF, NULL, NULL);
  nd3 = StateMachineNode_createFull(3, stt, NULL, mgrF, NULL, NULL);
  nd4 = StateMachineNode_createFull(4, stt, NULL, mgrF, NULL, NULL);

  list = StateMachineList_add(list, nd1);
  list = StateMachineList_add(list, nd2);
  list = StateMachineList_add(list, nd3);
  list = StateMachineList_add(list, nd4);

  res = StateMachineList_searchById(list, p);

  ck_assert_ptr_eq(res, nd3);

  StateMachineList_freeWipe(list);
}
END_TEST

START_TEST(test_StateMachineList_updateAll) {
  StateMachineNode *nd1, *nd2, *nd3, *nd4;
  StateMachineList *list = NULL;

  StateNode *nextStt =
      StateNode_createFull(NEXT, NULL, NULL, chB, NULL, NULL, NULL);

  // Creating different states for different updates
  StateNode *sttA =
      StateNode_createFull("sttA", NULL, NULL, NULL, upA, chA, nextStt);
  StateNode *sttB =
      StateNode_createFull("sttB", NULL, NULL, NULL, upB, chA, nextStt);
  StateNode *sttC =
      StateNode_createFull("sttC", NULL, NULL, NULL, upC, chA, nextStt);
  StateNode *sttD =
      StateNode_createFull("sttD", NULL, NULL, NULL, upD, chA, nextStt);

  nd4 = StateMachineNode_createFull(4, sttD, NULL, mgrF, NULL, NULL);
  nd3 = StateMachineNode_createFull(3, sttC, NULL, mgrF, NULL, nd4);
  nd2 = StateMachineNode_createFull(2, sttB, NULL, mgrF, NULL, nd3);
  nd1 = StateMachineNode_createFull(1, sttA, NULL, mgrF, NULL, nd2);

  list = nd1;

  char *r;
  r = StateMachineList_updateAll(list, NULL);

  ck_assert_str_eq(r, "ABCD");

  StateMachineList_freeWipe(list);
}
END_TEST

Suite *smc_stateMachine_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("StateMachine Machine Body");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_StateMachineNode_create);
  tcase_add_test(tc_sm, test_StateMachineNode_createFull);
  tcase_add_test(tc_sm, test_StateMachine_idMatch);
  tcase_add_test(tc_sm, test_StateMachineList_searchById);
  tcase_add_test(tc_sm, test_StateMachineList_updateAll);
  /*
   */

  suite_add_tcase(s, tc_sm);

  return s;
}

#ifndef COMPLETE_TEST

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = smc_stateMachine_list_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
#endif
