#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "../state.h"
#include "../stateCondition.h"

boolean cf_false(void *data) { return false; };
boolean cf_true(void *data) { return true; };

START_TEST(test_StateConditionNode_create) {
  StateConditionNode *nd;
  int n;
  void *nxt = &n;

  State *stt = malloc(sizeof(State));
  stt->name = "test";

  StateCondition *sttCond = StateCondition_create(cf_true, stt, 0);

  nd = StateConditionNode_create(sttCond, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, sttCond);
  ck_assert_ptr_eq(nd->next, nxt);

  StateConditionNode_freeWipe(nd);
}
END_TEST

START_TEST(test_StateConditionNode_createFull) {
  StateConditionNode *nd;
  StateCondition *sttCond;

  State *stt1 = malloc(sizeof(State));
  stt1->name = "State1";

  int n;
  void *nxt = &n;

  nd = StateConditionNode_createFull(cf_true, stt1, 0, nxt);
  sttCond = nd->dt;

  ck_assert_int_eq(sttCond->priority, 0);
  ck_assert_str_eq(sttCond->stateToName, "State1");
  ck_assert_ptr_eq(sttCond->stateToPtr, stt1);

  StateConditionNode_freeWipe(nd);
}
END_TEST

START_TEST(test_StateConditionNode_attatch) {
  StateConditionNode *nd1, *nd2;

  int s1, s2;
  void *sttCond1 = &s1, *sttCond2 = &s2;

  nd1 = StateConditionNode_create(sttCond1, NULL);
  nd2 = StateConditionNode_create(sttCond2, NULL);

  StateConditionNode_attatch(nd1, nd2);

  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_null(nd2->next);

  StateConditionNode_freeSafe(nd1);
  StateConditionNode_freeSafe(nd2);
}
END_TEST

// No need for add for now
//(Using only sorted add)
START_TEST(test_StateConditionList_sortedAdd) {
  StateConditionNode *nd1, *nd2, *nd3, *nd4;
  StateConditionList *list = NULL;

  State stt1, stt2, stt3, stt4;

  stt1.name = "State1";
  stt2.name = "State2";
  stt3.name = "State3";
  stt4.name = "State4";

  nd1 = StateConditionNode_createFull(cf_true, &stt1, 1, NULL);
  nd2 = StateConditionNode_createFull(cf_true, &stt2, 2, NULL);
  nd3 = StateConditionNode_createFull(cf_true, &stt3, 3, NULL);
  nd4 = StateConditionNode_createFull(cf_true, &stt4, 4, NULL);

  list = StateConditionList_add(list, nd1);
  list = StateConditionList_add(list, nd2);
  list = StateConditionList_add(list, nd4); // Swapped on purpose
  list = StateConditionList_add(list, nd3);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);

  StateConditionList_freeWipe(list);
}
END_TEST

//Not using search in smoke.
//Only ckeching for next state
START_TEST(test_StateConditionList_checkForNextState) {
  StateConditionNode *nd1, *nd2, *nd3, *nd4;
  StateConditionList *list = NULL;

  State stt1, stt2, stt3, stt4;
  State *r;

  stt1.name = "State1";
  stt2.name = "State2";
  stt3.name = "State3";
  stt4.name = "State4";

  nd1 = StateConditionNode_createFull(cf_false, &stt1, 1, NULL);
  nd2 = StateConditionNode_createFull(cf_false, &stt2, 2, NULL);
  nd3 = StateConditionNode_createFull(cf_true, &stt3, 3, NULL);
  nd4 = StateConditionNode_createFull(cf_false, &stt4, 4, NULL);

  list = StateConditionList_add(list, nd1);
  list = StateConditionList_add(list, nd2);
  list = StateConditionList_add(list, nd4); // Swapped on purpose
  list = StateConditionList_add(list, nd3);

  r = StateConditionList_checkForNextState(list, NULL);

  ck_assert_ptr_eq(r,&stt3);

  StateConditionList_freeWipe(list);
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine StateCondition List");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_StateConditionNode_create);
  tcase_add_test(tc_sm, test_StateConditionNode_createFull);
  tcase_add_test(tc_sm, test_StateConditionNode_attatch);
  tcase_add_test(tc_sm, test_StateConditionList_sortedAdd);
  tcase_add_test(tc_sm, test_StateConditionList_checkForNextState);

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
