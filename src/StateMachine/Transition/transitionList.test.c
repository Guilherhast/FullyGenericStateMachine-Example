#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "../state.h"
#include "../transition.h"

void trnFunc(StateMachine *smc) {}

START_TEST(test_TransitionNode_create) {
  TransitionNode *nd;

  int n;
  void *nxt = &n;

  Transition *trn = malloc(sizeof(Transition));

  trn->stateToName = malloc(sizeof(char));

  nd = TransitionNode_create(trn, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, trn);
  ck_assert_ptr_eq(nd->next, nxt);

  TransitionNode_freeWipe(nd);
}
END_TEST

START_TEST(test_TransitionNode_createRealFull) {
  int d, n;
  void *data = &d;
  void *nxt = &n;

  char name[] = "TESTNAME";
  State *stt = State_create(name, NULL, NULL, NULL, NULL, NULL);

  TransitionNode *nd;
  nd = TransitionNode_createFullReal(stt, stt->name, &trnFunc, data, nxt);

  ck_assert_ptr_nonnull(nd);
  ck_assert_ptr_eq(nd->next, nxt);

  Transition *trn = nd->dt;

  // Checking the real
  ck_assert(!trn->isTrigger);
  ck_assert_ptr_eq(trn->stateTo, stt);

  ck_assert_ptr_ne(trn->stateTo->name, trn->stateToName);

  ck_assert_str_eq(trn->stateToName, name);

  ck_assert_ptr_eq(trn->data, data);
  ck_assert_ptr_eq(trn->tFunc, &trnFunc);

  TransitionNode_freeWipe(nd);
}
END_TEST

START_TEST(test_TransitionNode_createTriggerFull) {
  int d, n;
  void *data = &d;
  void *nxt = &n;

  char name[] = "TESTNAME";

  TransitionNode *nd;
  nd = TransitionNode_createFullTrigger(name, &trnFunc, data, nxt);

  ck_assert_ptr_nonnull(nd);
  ck_assert_ptr_eq(nd->next, nxt);
  Transition *trn = nd->dt;

  // Checking the real
  ck_assert(trn->isTrigger);
  ck_assert_ptr_null(NULL);

  ck_assert_str_eq(trn->stateToName, name);

  ck_assert_ptr_eq(trn->data, data);
  ck_assert_ptr_eq(trn->tFunc, &trnFunc);

  TransitionNode_freeWipe(nd);
}
END_TEST

START_TEST(test_TransitionList_searchRealByName) {
  TransitionNode *nd1, *nd2, *nd3, *nd4;
  TransitionNode *r1, *r2, *r3, *r4;
  TransitionList *list = NULL;
  // Name of states
  char *n1 = "First", *n2 = "Second", *n3 = "Third", *n4 = "Forth";

  State *stt1 = State_create(n1, NULL, NULL, NULL, NULL, NULL);
  State *stt2 = State_create(n2, NULL, NULL, NULL, NULL, NULL);
  State *stt3 = State_create(n3, NULL, NULL, NULL, NULL, NULL);
  State *stt4 = State_create(n4, NULL, NULL, NULL, NULL, NULL);

  nd1 = TransitionNode_createFullReal(stt1, stt1->name, &trnFunc, NULL, NULL);
  nd2 = TransitionNode_createFullReal(stt2, stt2->name, &trnFunc, NULL, NULL);
  nd3 = TransitionNode_createFullReal(stt3, stt3->name, &trnFunc, NULL, NULL);
  nd4 = TransitionNode_createFullReal(stt4, stt4->name, &trnFunc, NULL, NULL);

  list = TransitionList_add(list, nd1);
  list = TransitionList_add(list, nd2);
  list = TransitionList_add(list, nd3);
  list = TransitionList_add(list, nd4);

  r1 = TransitionList_searchRealByName(list, n1);
  r2 = TransitionList_searchRealByName(list, n2);
  r3 = TransitionList_searchRealByName(list, n3);
  r4 = TransitionList_searchRealByName(list, n4);

  ck_assert_ptr_eq(r1->dt, nd1->dt);
  ck_assert_ptr_eq(r2->dt, nd2->dt);
  ck_assert_ptr_eq(r3->dt, nd3->dt);
  ck_assert_ptr_eq(r4->dt, nd4->dt);

  TransitionList_freeWipe(list);
}
END_TEST

START_TEST(test_TransitionList_searchTriggerByName) {
  TransitionNode *nd1, *nd2, *nd3, *nd4;
  TransitionNode *r1, *r2, *r3, *r4;
  TransitionList *list = NULL;
  // Name of states
  char *n1 = "First", *n2 = "Second", *n3 = "Third", *n4 = "Forth";

  nd1 = TransitionNode_createFullTrigger(n1, &trnFunc, NULL, NULL);
  nd2 = TransitionNode_createFullTrigger(n2, &trnFunc, NULL, NULL);
  nd3 = TransitionNode_createFullTrigger(n3, &trnFunc, NULL, NULL);
  nd4 = TransitionNode_createFullTrigger(n4, &trnFunc, NULL, NULL);

  list = TransitionList_add(list, nd1);
  list = TransitionList_add(list, nd2);
  list = TransitionList_add(list, nd3);
  list = TransitionList_add(list, nd4);

  r1 = TransitionList_searchTriggerByName(list, n1);
  r2 = TransitionList_searchTriggerByName(list, n2);
  r3 = TransitionList_searchTriggerByName(list, n3);
  r4 = TransitionList_searchTriggerByName(list, n4);

  ck_assert_ptr_eq(r1->dt, nd1->dt);
  ck_assert_ptr_eq(r2->dt, nd2->dt);
  ck_assert_ptr_eq(r3->dt, nd3->dt);
  ck_assert_ptr_eq(r4->dt, nd4->dt);

  TransitionList_freeSafe(list);
}
END_TEST

START_TEST(test_TransitionList_searchMixedByName) {
  TransitionNode *nd1, *nd2, *nd3, *nd4;
  TransitionNode *rr1, *rr2, *rr3, *rr4;
  TransitionNode *rt1, *rt2, *rt3, *rt4;
  TransitionList *list = NULL;
  // Name of states
  char *n1 = "First", *n2 = "Second", *n3 = "Third", *n4 = "Forth";

  State *stt1 = State_create(n1, NULL, NULL, NULL, NULL, NULL);
  State *stt3 = State_create(n3, NULL, NULL, NULL, NULL, NULL);

  nd1 = TransitionNode_createFullReal(stt1, stt1->name, &trnFunc, NULL, NULL);
  nd2 = TransitionNode_createFullTrigger(n2, &trnFunc, NULL, NULL);
  nd3 = TransitionNode_createFullReal(stt3, stt3->name, &trnFunc, NULL, NULL);
  nd4 = TransitionNode_createFullTrigger(n4, &trnFunc, NULL, NULL);

  list = TransitionList_add(list, nd1);
  list = TransitionList_add(list, nd2);
  list = TransitionList_add(list, nd3);
  list = TransitionList_add(list, nd4);

  // Searching real ones
  rr1 = TransitionList_searchRealByName(list, n1);
  rr2 = TransitionList_searchRealByName(list, n2);
  rr3 = TransitionList_searchRealByName(list, n3);
  rr4 = TransitionList_searchRealByName(list, n4);

  // Searching trigger ones
  rt1 = TransitionList_searchTriggerByName(list, n1);
  rt2 = TransitionList_searchTriggerByName(list, n2);
  rt3 = TransitionList_searchTriggerByName(list, n3);
  rt4 = TransitionList_searchTriggerByName(list, n4);

  // Test real results
  ck_assert_ptr_eq(rr1->dt, nd1->dt);
  ck_assert_ptr_eq(rr3->dt, nd3->dt);

  ck_assert_ptr_null(rr2);
  ck_assert_ptr_null(rr4);

  // Test trigger results
  ck_assert_ptr_eq(rt2->dt, nd2->dt);
  ck_assert_ptr_eq(rt4->dt, nd4->dt);

  ck_assert_ptr_null(rt1);
  ck_assert_ptr_null(rt3);

  TransitionList_freeWipe(list);
}
END_TEST

/*

START_TEST(test_StateNode_attatch) {
StateNode *nd1, *nd2;

int s1, s2;
void *stt1 = &s1, *stt2 = &s2;

nd1 = StateNode_create(stt1, NULL);
nd2 = StateNode_create(stt2, NULL);

StateNode_attatch(nd1, nd2);

ck_assert_ptr_eq(nd1->next, nd2);
ck_assert_ptr_null(nd2->next);

StateNode_freeSafe(nd1);
StateNode_freeSafe(nd2);
}
END_TEST

// No need for sorted add for now
START_TEST(test_StateList_Add) {
StateNode *nd1, *nd2, *nd3, *nd4;
StateList *list = NULL;

int s1, s2, s3, s4;
void *stt1 = &s1, *stt2 = &s2, *stt3 = &s3, *stt4 = &s4;

nd1 = StateNode_create(stt1, NULL);
nd2 = StateNode_create(stt2, NULL);
nd3 = StateNode_create(stt3, NULL);
nd4 = StateNode_create(stt4, NULL);

list = StateList_add(list, nd1);
list = StateList_add(list, nd2);
list = StateList_add(list, nd3);
list = StateList_add(list, nd4);

ck_assert_ptr_eq(list, nd1);
ck_assert_ptr_eq(nd1->next, nd2);
ck_assert_ptr_eq(nd2->next, nd3);
ck_assert_ptr_eq(nd3->next, nd4);

ck_assert_ptr_null(nd4->next);

StateList_freeSafe(list);
}
END_TEST

// No need for search in smoke
START_TEST(test_StateList_searchByName) {
StateNode *nd1, *nd2, *nd3, *nd4;
StateNode *r1, *r2, *r3, *r4;
StateList *list = NULL;
// Name of states
char *n1 = "First", *n2 = "Second", *n3 = "Third", *n4 = "Forth";

nd1 = StateNode_createFull(n1, NULL, &en, &up, &ex,  NULL);
nd2 = StateNode_createFull(n2, NULL, &en, &up, &ex,  NULL);
nd3 = StateNode_createFull(n3, NULL, &en, &up, &ex,  NULL);
nd4 = StateNode_createFull(n4, NULL, &en, &up, &ex,  NULL);

list = StateList_add(list, nd1);
list = StateList_add(list, nd2);
list = StateList_add(list, nd3);
list = StateList_add(list, nd4);

r1 = StateList_searchByName(list, n1);
r2 = StateList_searchByName(list, n2);
r3 = StateList_searchByName(list, n3);
r4 = StateList_searchByName(list, n4);

ck_assert_ptr_eq(r1->dt, nd1->dt);
ck_assert_ptr_eq(r2->dt, nd2->dt);
ck_assert_ptr_eq(r3->dt, nd3->dt);
ck_assert_ptr_eq(r4->dt, nd4->dt);

ck_assert_str_eq(r1->dt->name, n1);
ck_assert_str_eq(r2->dt->name, n2);
ck_assert_str_eq(r3->dt->name, n3);
ck_assert_str_eq(r4->dt->name, n4);

StateList_freeWipe(list);
}
END_TEST

*/

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine Transition List");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_TransitionNode_create);
  tcase_add_test(tc_sm, test_TransitionNode_createTriggerFull);
  tcase_add_test(tc_sm, test_TransitionNode_createRealFull);
  tcase_add_test(tc_sm, test_TransitionList_searchRealByName);
  tcase_add_test(tc_sm, test_TransitionList_searchTriggerByName);
  tcase_add_test(tc_sm, test_TransitionList_searchMixedByName);
  /*
  tcase_add_test(tc_sm, test_StateList_Add);
  tcase_add_test(tc_sm, test_State_attatch);
  tcase_add_test(tc_sm, test_StateList_Add);
  */

  suite_add_tcase(s, tc_sm);

  return s;
}

#ifndef COMPLETE_TEST

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = smc_state_list_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
#endif
