#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./list.h"

void en(time_t dt, void *data) {}
void ex(time_t dt, void *data) {}
void up(time_t dt, void *data) {}
void ss() {}

short int simpleSort(int *a, int *b) { return *a - *b; }
boolean testInt(int *nodeData, int *data) { return *nodeData == *data; }
boolean testEven(int *nodeData, int *data) { return (*nodeData % 2) == 0; }

// Pre-tests
START_TEST(test_simpleSort) {
  int d1 = 1, d2 = 5;
  int *pd1 = &d1, *pd2 = &d2;

  int rcres, rdcres, requal;

  rcres = simpleSort(pd1, pd2);
  requal = simpleSort(pd1, pd1);
  rdcres = simpleSort(pd2, pd1);

  ck_assert_int_eq(rcres, -4);
  ck_assert_int_eq(requal, 0);
  ck_assert_int_eq(rdcres, 4);
}
END_TEST

START_TEST(test_testInt) {
  int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a0 = 8;

  ck_assert(testInt(&i1, &a1));
  ck_assert(testInt(&i2, &a2));
  ck_assert(testInt(&i3, &a3));
  ck_assert(testInt(&i4, &a4));
  ck_assert(!testInt(&i4, &a0));
}
END_TEST

START_TEST(test_testEven) {
  int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

  // True
  ck_assert(testEven(&i2, NULL));
  ck_assert(testEven(&i4, NULL));

  // False
  ck_assert(!testEven(&i1, NULL));
  ck_assert(!testEven(&i3, NULL));
}
END_TEST

// Tests
START_TEST(test_ListNode_create) {
  ListNode *nd;

  int d, n;
  void *dt = &d, *nxt = &n;

  nd = ListNode_create(dt, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, dt);
  ck_assert_ptr_eq(nd->next, nxt);
}
END_TEST

START_TEST(test_ListNode_swapData) {
  ListNode *nd1, *nd2;

  int d1, d2;
  void *dt1 = &d1, *dt2 = &d2;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);

  ListNode_swapData(nd1, nd2);

  ck_assert_ptr_eq(nd1->dt, dt2);
  ck_assert_ptr_eq(nd2->dt, dt1);
}
END_TEST

START_TEST(test_ListNode_attatch) {
  ListNode *nd1, *nd2;

  int d1, d2;
  void *dt1 = &d1, *dt2 = &d2;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);

  ListNode_attatch(nd1, nd2);

  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_null(nd2->next);
}
END_TEST

START_TEST(test_List_Add) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  List *list = NULL;

  int s1, s2, s3, s4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);
}
END_TEST

START_TEST(test_List_sortedAdd_SwapFalse) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  List *list = NULL;

  int s1 = 1, s2 = 2, s3 = 3, s4 = 4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;
  void *sps = &simpleSort;

  list = NULL;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd3 = ListNode_create(dt3, NULL);
  nd4 = ListNode_create(dt4, NULL);

  list = List_sortedAdd(list, nd2, sps, false); // Inverted on purpose
  list = List_sortedAdd(list, nd1, sps, false);
  list = List_sortedAdd(list, nd4, sps, false);
  list = List_sortedAdd(list, nd3, sps, false);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);

  ck_assert_ptr_eq(nd1->dt, dt1);
  ck_assert_ptr_eq(nd2->dt, dt2);
  ck_assert_ptr_eq(nd3->dt, dt3);
  ck_assert_ptr_eq(nd4->dt, dt4);
}
END_TEST

START_TEST(test_List_sortedAdd_SwapTrue) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  List *list = NULL;

  int s1 = 1, s2 = 2, s3 = 3, s4 = 4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;
  void *sps = &simpleSort;

  nd1 = ListNode_create(dt2, NULL); // Inverted on purpose
  nd2 = ListNode_create(dt1, NULL);
  nd3 = ListNode_create(dt3, NULL);
  nd4 = ListNode_create(dt4, NULL);

  list = List_sortedAdd(list, nd1, sps, true);
  list = List_sortedAdd(list, nd2, sps, true);
  list = List_sortedAdd(list, nd4, sps, true);
  list = List_sortedAdd(list, nd3, sps, true);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);

  ck_assert_ptr_eq(nd1->dt, dt1);
  ck_assert_ptr_eq(nd2->dt, dt2);
  ck_assert_ptr_eq(nd3->dt, dt3);
  ck_assert_ptr_eq(nd4->dt, dt4);
}
END_TEST

START_TEST(test_List_search) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  ListNode *r0, *r1, *r2, *r3, *r4;
  List *list = NULL;

  int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a0 = 8;

  void *dt1 = &i1, *dt2 = &i2, *dt3 = &i3, *dt4 = &i4;
  void *ti = &testInt;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL);
  nd3 = ListNode_create(dt3, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  r0 = List_search(list, ti, &a0);
  r1 = List_search(list, ti, &a1);
  r2 = List_search(list, ti, &a2);
  r3 = List_search(list, ti, &a3);
  r4 = List_search(list, ti, &a4);

  ck_assert_ptr_null(r0);
  ck_assert_ptr_eq(r1, nd1);
  ck_assert_ptr_eq(r2, nd2);
  ck_assert_ptr_eq(r3, nd3);
  ck_assert_ptr_eq(r4, nd4);
}
END_TEST

START_TEST(test_List_searchNth) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  ListNode *r2, *r4, *r0;
  List *list = NULL;

  int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

  void *dt1 = &i1, *dt2 = &i2, *dt3 = &i3, *dt4 = &i4;
  void *te = &testEven;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd3 = ListNode_create(dt3, NULL);
  nd4 = ListNode_create(dt4, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  r2 = List_searchNth(list, te, NULL, 1);
  r4 = List_searchNth(list, te, NULL, 2);
  r0 = List_searchNth(list, te, NULL, 3);

  ck_assert_ptr_eq(r2, nd2);
  ck_assert_ptr_eq(r4, nd4);
  ck_assert_ptr_null(r0);
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State List");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_ListNode_create);
  tcase_add_test(tc_sm, test_ListNode_swapData);
  tcase_add_test(tc_sm, test_ListNode_attatch);
  tcase_add_test(tc_sm, test_testInt);
  tcase_add_test(tc_sm, test_testEven);

  tcase_add_test(tc_sm, test_simpleSort);
  tcase_add_test(tc_sm, test_List_Add);
  tcase_add_test(tc_sm, test_List_sortedAdd_SwapFalse);
  tcase_add_test(tc_sm, test_List_sortedAdd_SwapTrue);
  tcase_add_test(tc_sm, test_List_search);
  tcase_add_test(tc_sm, test_List_searchNth);

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