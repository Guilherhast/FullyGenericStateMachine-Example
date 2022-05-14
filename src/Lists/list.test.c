#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../TestUtils/testUtils.h"
#include "./list.h"

struct subStruct {
  int a;
  int b;
};

typedef struct subStruct subStruct;

struct testType {
  subStruct *dt;
  struct testType *next;
};

typedef struct testType testType;

void intWipper(void *dt) { free(dt); }
void subStructWipper(void *dt) { free(dt); }

short int simpleSort(void *va, void *vb) {
  short int *a = (short int *)va, *b = (short int *)vb;
  return *a - *b;
}
boolean testInt(int *nodeData, int *data) {
  return *nodeData == *data;
}
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
// LISTNODE
START_TEST(test_ListNode_create) {
  ListNode *nd;

  void *dt = malloc(sizeof(int));

  // Does this ausence of checking has
  // potential to disaster?
  int n;
  void *nxt = &n;

  nd = ListNode_create(dt, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, dt);
  ck_assert_ptr_eq(nd->next, nxt);

  ListNode_free(nd, &intWipper);
}
END_TEST

START_TEST(test_ListNode_create_typecast) {
  int n;
  void *nxt = &n;

  subStruct *dt = malloc(sizeof(subStruct));

  dt->a = 1;
  dt->b = 2;

  testType *tst;
  ListNode *nd;

  nd = ListNode_create(dt, nxt);
  tst = (testType *)ListNode_create(dt, nxt);

  ck_assert_ptr_eq(tst->next, nd->next);
  ck_assert_ptr_eq(tst->dt, nd->dt);

  ck_assert_int_eq(tst->dt->a, 1);
  ck_assert_int_eq(tst->dt->b, 2);

  ListNode_freeSafe(nd);
  ListNode_free((ListNode *)tst, subStructWipper);
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

  free(nd1);
  free(nd2);
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

  free(nd1);
  free(nd2);
}
END_TEST

START_TEST(test_ListNode_clone) {
  ListNode *nd1, *nd2;

  int d1;
  void *dt1 = &d1;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_clone(nd1);

  ck_assert_ptr_eq(nd1->dt, dt1);
  ck_assert_ptr_eq(nd1->dt, nd2->dt);
  ck_assert_ptr_eq(nd2->dt, dt1); // Redundant

  ck_assert_ptr_null(nd2->next);

  ListNode_freeSafe(nd1);
  ListNode_freeSafe(nd2);
}
END_TEST

// LISTS
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

  ck_assert_list_size(list, 4);

  ListNode_freeSafe(list);
}
END_TEST

START_TEST(test_List_cat) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  ListNode *nd5, *nd6, *nd7, *nd8;

  List *list1 = NULL, *list2 = NULL, *listr = NULL;

  int s1, s2, s3, s4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  nd5 = ListNode_create(dt1, NULL);
  nd6 = ListNode_create(dt2, NULL);
  nd8 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd7 = ListNode_create(dt3, NULL);

  list1 = List_add(list1, nd1);
  list1 = List_add(list1, nd2);
  list1 = List_add(list1, nd3);
  list1 = List_add(list1, nd4);

  list2 = List_add(list2, nd5);
  list2 = List_add(list2, nd6);
  list2 = List_add(list2, nd7);
  list2 = List_add(list2, nd8);

  listr = List_cat(list1, list2);

  ck_assert_ptr_eq(list1, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_eq(list2, nd5);
  ck_assert_ptr_eq(nd4->next, nd5);
  ck_assert_ptr_eq(nd5->next, nd6);
  ck_assert_ptr_eq(nd6->next, nd7);
  ck_assert_ptr_eq(nd7->next, nd8);

  ck_assert_ptr_null(nd8->next);

  ck_assert_list_size(list1, 8);
  ck_assert_list_size(list2, 4);
  ck_assert_list_size(listr, 8);

  ListNode_freeSafe(listr);
}
END_TEST

START_TEST(test_List_merge_noswap) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  ListNode *nd5, *nd6, *nd7, *nd8;

  void *sps = &simpleSort;

  List *list1 = NULL, *list2 = NULL, *listr = NULL;

  int s1 = 1, s2 = 2, s3 = 3, s4 = 4;
  int s5 = 5, s6 = 6, s7 = 7, s8 = 8;

  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;
  void *dt5 = &s5, *dt6 = &s6, *dt7 = &s7, *dt8 = &s8;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  nd5 = ListNode_create(dt5, NULL);
  nd6 = ListNode_create(dt6, NULL);
  nd7 = ListNode_create(dt7, NULL);
  nd8 = ListNode_create(dt8, NULL); // Inverted on purpose

  list1 = List_add(list1, nd1);
  list1 = List_add(list1, nd3);
  list1 = List_add(list1, nd5);
  list1 = List_add(list1, nd7);

  list2 = List_add(list2, nd2);
  list2 = List_add(list2, nd4);
  list2 = List_add(list2, nd6);
  list2 = List_add(list2, nd8);

  listr = List_merge(list2, list1, sps);

  ck_assert_ptr_eq(listr, list1);
  ck_assert_ptr_eq(list1, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_eq(list2, nd2);
  ck_assert_ptr_eq(nd4->next, nd5);
  ck_assert_ptr_eq(nd5->next, nd6);
  ck_assert_ptr_eq(nd6->next, nd7);
  ck_assert_ptr_eq(nd7->next, nd8);

  ck_assert_ptr_null(nd8->next);

  ck_assert_list_size(listr, 8);

  ListNode_freeSafe(listr);
}
END_TEST

START_TEST(test_List_findAndClone) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  ListNode *c0, *c1, *c2, *c3, *c4;
  List *list = NULL;

  void *ti = &testInt;

  int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a0 = 8;

  int s1 = 1, s2 = 2, s3 = 3, s4 = 4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  c0 = List_findAndClone(list, ti, &a0);
  c1 = List_findAndClone(list, ti, &a1);
  c2 = List_findAndClone(list, ti, &a2);
  c3 = List_findAndClone(list, ti, &a3);
  c4 = List_findAndClone(list, ti, &a4);

  ck_assert_ptr_null(c0);

  ck_assert_ptr_eq(c1->dt, nd1->dt);
  ck_assert_ptr_eq(c2->dt, nd2->dt);
  ck_assert_ptr_eq(c3->dt, nd3->dt);
  ck_assert_ptr_eq(c4->dt, nd4->dt);

  ListNode_freeSafe(list);
  ListNode_freeSafe(c0);
  ListNode_freeSafe(c1);
  ListNode_freeSafe(c2);
  ListNode_freeSafe(c3);
  ListNode_freeSafe(c4);
}
END_TEST

START_TEST(test_List_findAndCloneMany) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  List *list = NULL;
  List *cloned = NULL;

  void *ti = &testInt;


  int a2 = 2, a4 = 4;
  int *dataArr[] = {&a2, &a4};

  int s1 = 1, s2 = 2, s3 = 3, s4 = 4;
  void *dt1 = &s1, *dt2 = &s2, *dt3 = &s3, *dt4 = &s4;

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  cloned = List_findAndCloneMany(list, ti, NULL, 2, (void **)dataArr);

  ck_assert_list_size(cloned, 2);

  ck_assert_ptr_eq(cloned->dt, dt2);
  ck_assert_ptr_eq(cloned->next->dt, dt4);

  ck_assert_ptr_null(cloned->next->next);

  ListNode_freeSafe(list);

}
END_TEST

START_TEST(test_List_free) {
  ListNode *nd1, *nd2, *nd3, *nd4;
  List *list = NULL;

  void *dt1 = malloc(sizeof(int)), *dt2 = malloc(sizeof(int)),
       *dt3 = malloc(sizeof(int)), *dt4 = malloc(sizeof(int));

  nd1 = ListNode_create(dt1, NULL);
  nd2 = ListNode_create(dt2, NULL);
  nd4 = ListNode_create(dt4, NULL); // Inverted on purpose
  nd3 = ListNode_create(dt3, NULL);

  list = List_add(list, nd1);
  list = List_add(list, nd2);
  list = List_add(list, nd3);
  list = List_add(list, nd4);

  List_free(list, intWipper);
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

  ck_assert_list_size(list, 4);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);

  ck_assert_ptr_eq(nd1->dt, dt1);
  ck_assert_ptr_eq(nd2->dt, dt2);
  ck_assert_ptr_eq(nd3->dt, dt3);
  ck_assert_ptr_eq(nd4->dt, dt4);

  List_freeSafe(list);
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

  ck_assert_list_size(list, 4);

  ck_assert_ptr_eq(list, nd1);
  ck_assert_ptr_eq(nd1->next, nd2);
  ck_assert_ptr_eq(nd2->next, nd3);
  ck_assert_ptr_eq(nd3->next, nd4);

  ck_assert_ptr_null(nd4->next);

  ck_assert_ptr_eq(nd1->dt, dt1);
  ck_assert_ptr_eq(nd2->dt, dt2);
  ck_assert_ptr_eq(nd3->dt, dt3);
  ck_assert_ptr_eq(nd4->dt, dt4);

  free(nd1);
  free(nd2);
  free(nd3);
  free(nd4);
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

  free(nd1);
  free(nd2);
  free(nd3);
  free(nd4);
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

  free(nd1);
  free(nd2);
  free(nd3);
  free(nd4);
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("List");
  tc_sm = tcase_create("Smoke");

  // Pre
  tcase_add_test(tc_sm, test_testInt);
  tcase_add_test(tc_sm, test_testEven);
  tcase_add_test(tc_sm, test_simpleSort);

  // Node
  tcase_add_test(tc_sm, test_ListNode_create);
  tcase_add_test(tc_sm, test_ListNode_create_typecast);
  tcase_add_test(tc_sm, test_ListNode_swapData);
  tcase_add_test(tc_sm, test_ListNode_attatch);
  tcase_add_test(tc_sm, test_ListNode_clone);

  // List
  tcase_add_test(tc_sm, test_List_Add);
  tcase_add_test(tc_sm, test_List_cat);
  tcase_add_test(tc_sm, test_List_findAndClone);
  tcase_add_test(tc_sm, test_List_findAndCloneMany);
  tcase_add_test(tc_sm, test_List_merge_noswap);
  tcase_add_test(tc_sm, test_List_free);
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
