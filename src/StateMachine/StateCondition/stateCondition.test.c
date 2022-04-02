#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../stateCondition.h"
#include "../state.h"

boolean cf_false(unsigned long int dt, void *data) { return false; };
boolean cf_true(unsigned long int dt,  void *data) { return true; };

START_TEST(test_stateCondition_create) {
  State stt;
  stt.name = "test";


  StateCondition *sttCond;
  sttCond = StateCondition_create(&cf_true,&stt, 1, NULL);

  ck_assert_int_eq(sttCond->priority, 1);
  ck_assert_str_eq(sttCond->stateToName, "test");
  ck_assert_ptr_eq(sttCond->stateToPtr,&stt);
}
END_TEST

START_TEST(test_stateCondition_attatch) {
  StateCondition *sttCond1, *sttCond2, *ptr;

  State stt;
  stt.name = "test";

  sttCond1 = StateCondition_create(&cf_true,&stt, 1, NULL);
  sttCond2 = StateCondition_create(&cf_true,&stt, 2, NULL);

  ptr = StateCondition_attatch(sttCond1, sttCond2);

  ck_assert_ptr_eq(ptr, sttCond1);
  ck_assert_ptr_eq(sttCond1->next, sttCond2);
}
END_TEST

START_TEST(test_stateCondition_list_add) {
  StateCondition *sttCond1, *sttCond2, *sttCond3, *sttCond4, *list;

  State stt;
  stt.name = "Name";

  list = NULL;

  sttCond1 = StateCondition_create(&cf_true,&stt, 1, NULL);
  sttCond2 = StateCondition_create(&cf_true,&stt, 2, NULL);
  sttCond3 = StateCondition_create(&cf_true,&stt, 3, NULL);
  sttCond4 = StateCondition_create(&cf_true,&stt, 4, NULL);

  list = StateCondition_listAdd(list, sttCond1);
  list = StateCondition_listAdd(list, sttCond2);
  list = StateCondition_listAdd(list, sttCond4); // Let this one out of other
  list = StateCondition_listAdd(list, sttCond3);

  ck_assert_ptr_eq(list, sttCond1);
  ck_assert_ptr_eq(sttCond1->next, sttCond2);
  ck_assert_ptr_eq(sttCond2->next, sttCond3);
  ck_assert_ptr_eq(sttCond3->next, sttCond4);
}
END_TEST

START_TEST(test_stateCondition_listCheckForNextState) {
  StateCondition *sttCond1, *sttCond2, *sttCond3, *sttCond4, *list;

  State stt;
  stt.name = "Third";

  list = NULL;

  sttCond1 = StateCondition_create(&cf_false,NULL, 1, NULL);
  sttCond2 = StateCondition_create(&cf_false,NULL, 2, NULL);
  sttCond3 = StateCondition_create(&cf_true,&stt, 3, NULL);
  sttCond4 = StateCondition_create(&cf_false,NULL, 4, NULL);

  list = StateCondition_listAdd(list, sttCond1);
  list = StateCondition_listAdd(list, sttCond2);
  list = StateCondition_listAdd(list, sttCond4); // Let this one out of other
  list = StateCondition_listAdd(list, sttCond3);

  char *nextStateName;
  nextStateName = StateCondition_listCheckForNextState(list, 0,NULL);
  ck_assert_str_eq("Third", nextStateName);
}
END_TEST

START_TEST(test_stateCondition_listCheckForNextStatePtr) {
  StateCondition *sttCond1, *sttCond2, *sttCond3, *sttCond4, *list;

  State stt;
  stt.name = "test";

  list = NULL;

  sttCond1 = StateCondition_create(&cf_false,NULL, 1, NULL);
  sttCond2 = StateCondition_create(&cf_false,NULL, 2, NULL);
  sttCond3 = StateCondition_create(&cf_true,&stt, 3, NULL);
  sttCond4 = StateCondition_create(&cf_false,NULL, 4, NULL);

  list = StateCondition_listAdd(list, sttCond1);
  list = StateCondition_listAdd(list, sttCond2);
  list = StateCondition_listAdd(list, sttCond4); // Let this one out of other
  list = StateCondition_listAdd(list, sttCond3);

  State *sttPtr;
  sttPtr = StateCondition_listCheckForNextStatePtr(list, 0,NULL);
  ck_assert_ptr_eq(sttPtr, &stt);
}
END_TEST

Suite *stateCondition_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State Contition");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_stateCondition_create);
  tcase_add_test(tc_sm, test_stateCondition_attatch);
  tcase_add_test(tc_sm, test_stateCondition_list_add);
  tcase_add_test(tc_sm, test_stateCondition_listCheckForNextState);
  tcase_add_test(tc_sm, test_stateCondition_listCheckForNextStatePtr);
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
