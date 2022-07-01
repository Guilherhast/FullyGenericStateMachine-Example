#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "../state.h"

void* en(State *stt,  void *data) {return data;}
void* ex(State *stt,  void *data) {return data;}
void* up(State *stt,  void *data) {return data;}

START_TEST(test_StateNode_create) {
  StateNode *nd;

  int n;
  void *stt = malloc(sizeof(State)), *nxt = &n;

  nd = StateNode_create(stt, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, stt);
  ck_assert_ptr_eq(nd->next, nxt);

  StateNode_freeWipe(nd);
}
END_TEST

START_TEST(test_StateNode_createFull) {
  StateNode *nd;
  State *stt;

  char *name = "StateName";

  int n;
  void *nxt = &n;

  nd = StateNode_createFull(name, NULL, NULL,  &en, &up, &ex, nxt);
  stt = nd->dt;

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, stt);
  ck_assert_ptr_eq(nd->next, nxt);

  ck_assert_int_eq(stt->lastSignalSent, 0);
  ck_assert_int_eq(stt->lastTimeEntered, 0);
  ck_assert_int_eq(stt->lastUpdated, 0);

  ck_assert_ptr_eq(stt->enter, &en);
  ck_assert_ptr_eq(stt->update, &up);
  ck_assert_ptr_eq(stt->exit, &ex);

  StateNode_freeWipe(nd);
}
END_TEST

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

  nd1 = StateNode_createFull(n1, NULL, NULL,  &en, &up, &ex,  NULL);
  nd2 = StateNode_createFull(n2, NULL, NULL,  &en, &up, &ex,  NULL);
  nd3 = StateNode_createFull(n3, NULL, NULL,  &en, &up, &ex,  NULL);
  nd4 = StateNode_createFull(n4, NULL, NULL,  &en, &up, &ex,  NULL);

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

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State List");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_StateNode_create);
  tcase_add_test(tc_sm, test_StateNode_createFull);
  tcase_add_test(tc_sm, test_StateNode_attatch);
  tcase_add_test(tc_sm, test_StateList_Add);
  tcase_add_test(tc_sm, test_StateList_searchByName);
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
