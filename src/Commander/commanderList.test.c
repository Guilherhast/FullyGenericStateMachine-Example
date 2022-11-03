#include <check.h>

#include <stdio.h>
#include <stdlib.h>

#include "../Lists/list.h"
#include "../TestUtils/testUtils.h"
#include "commander.h"

void *cmdrf(StateMachineList *lst, char *str) { return lst; }

void *f1(StateMachineList *lst, char *str) {
  int *i = malloc(sizeof(int));
  *i = 1;
  return i;
}
void *f2(StateMachineList *lst, char *str) {
  int *i = malloc(sizeof(int));
  *i = 2;
  return i;
}
void *f3(StateMachineList *lst, char *str) {
  int *i = malloc(sizeof(int));
  *i = 3;
  return i;
}
void *f4(StateMachineList *lst, char *str) {
  int *i = malloc(sizeof(int));
  *i = 4;
  return i;
}

// Helps creating a deepForked list
CommandList *createFuncList(char *str) {
  USint sz = strlen(str);

  char nm1[sz + 2];
  strcpy(nm1, str), strcat(nm1, "1");

  char nm2[sz + 2];
  strcpy(nm2, str), strcat(nm2, "2");

  char nm3[sz + 2];
  strcpy(nm3, str), strcat(nm3, "3");

  char nm4[sz + 2];
  strcpy(nm4, str), strcat(nm4, "4");

  CommandNode *nd1 = CommandNode_createFullFunc(nm1, (void *)f1, NULL);
  CommandNode *nd2 = CommandNode_createFullFunc(nm2, (void *)f2, NULL);
  CommandNode *nd3 = CommandNode_createFullFunc(nm3, (void *)f3, NULL);
  CommandNode *nd4 = CommandNode_createFullFunc(nm4, (void *)f4, NULL);

  CommandList *list = NULL;
  list = CommandList_add(list, nd1);
  list = CommandList_add(list, nd2);
  list = CommandList_add(list, nd3);
  list = CommandList_add(list, nd4);

  ck_assert_list_size((List *)list, 4);
  return list;
}

START_TEST(test_CommandNode_create) {
  CommandNode *nd;

  int n;
  void *nxt = &n;

  Command *cmd = malloc(sizeof(Command));

  cmd->name = NULL;

  nd = CommandNode_create(cmd, nxt);

  ck_assert_ptr_nonnull(nd);

  ck_assert_ptr_eq(nd->dt, cmd);
  ck_assert_ptr_eq(nd->next, nxt);

  CommandNode_free(nd, Command_free);
  // CommandNode_freeWipe(nd);
}
END_TEST

START_TEST(test_CommandNode_createFullFork) {
  int n;
  void *nxt = &n;

  char name[] = "TESTNAME";

  CommandNode *nd;
  nd = CommandNode_createFullFunc(name, (void *)cmdrf, nxt);

  ck_assert_ptr_nonnull(nd);
  ck_assert_ptr_eq(nd->next, nxt);

  ck_assert_ptr_eq(nd->dt->func, cmdrf);

  ck_assert_ptr_ne(nd->dt->name, name);
  ck_assert_str_eq(nd->dt->name, name);

  ck_assert_ptr_null(nd->dt->list);

  // Checking the real

  CommandNode_freeWipe(nd);
}
END_TEST

START_TEST(test_CommandNode_createFullFunc) {
  int l, n;
  void *list = &l;
  void *nxt = &n;

  char name[] = "TESTNAME";

  CommandNode *nd;
  nd = CommandNode_createFullFork(name, list, nxt);

  ck_assert_ptr_nonnull(nd);
  ck_assert_ptr_eq(nd->next, nxt);

  ck_assert_ptr_eq(nd->dt->list, list);

  ck_assert_ptr_ne(nd->dt->name, name);
  ck_assert_str_eq(nd->dt->name, name);

  ck_assert_ptr_null(nd->dt->func);

  // Checking the real

  CommandNode_freeWipe(nd);
}
END_TEST

START_TEST(test_CommandNode_searchByMame) {
  int l;
  void *nList = &l;

  char nm1[] = "C1";
  char nm2[] = "C2";
  char nm3[] = "C3";
  char nm4[] = "C4";

  CommandNode *nd1 = CommandNode_createFullFork(nm1, nList, NULL);
  CommandNode *nd2 = CommandNode_createFullFork(nm2, nList, NULL);
  CommandNode *nd3 = CommandNode_createFullFork(nm3, nList, NULL);
  CommandNode *nd4 = CommandNode_createFullFork(nm4, nList, NULL);

  CommandList *list = NULL;

  list = CommandList_add(list, nd1);
  list = CommandList_add(list, nd2);
  list = CommandList_add(list, nd3);
  list = CommandList_add(list, nd4);

  CommandNode *r1 = CommandList_searchByName(list, nm1);
  CommandNode *r2 = CommandList_searchByName(list, nm2);
  CommandNode *r3 = CommandList_searchByName(list, nm3);
  CommandNode *r4 = CommandList_searchByName(list, nm4);

  ck_assert_ptr_eq(r1, nd1);
  ck_assert_ptr_eq(r2, nd2);
  ck_assert_ptr_eq(r3, nd3);
  ck_assert_ptr_eq(r4, nd4);

  // Cleaning up
  CommandList_freeWipe(list);
}
END_TEST

START_TEST(test_CommandNode_deepRun) {
  CommandList *mainList = NULL;

  // List level 3 ( function lists )
  // First second third and quarto ( fourth )
  CommandList *l3f = createFuncList("f");
  CommandList *l3s = createFuncList("s");
  CommandList *l3t = createFuncList("t");
  CommandList *l3q = createFuncList("q");

  // LISTS LEVEL 2
  //  fork list a
  CommandNode *l2a2 = CommandNode_createFullFork("a2", l3s, NULL);
  CommandNode *l2a1 = CommandNode_createFullFork("a1", l3f, l2a2);

  // fork list b
  CommandNode *l2b2 = CommandNode_createFullFork("b2", l3q, NULL);
  CommandNode *l2b1 = CommandNode_createFullFork("b1", l3t, l2b2);

  // LISTS LEVEL 1
  CommandNode *l1B = CommandNode_createFullFork("B", l2b1, NULL);
  CommandNode *l1A = CommandNode_createFullFork("A", l2a1, l1B);

  mainList = l1A;

  ck_assert_list_size((List *)mainList, 2);

  int *rn1, *rn2, *rn3, *rn4, *rn5;
  // Null checks
  rn1 = (int *)CommandList_deepRun(mainList, NULL, "A a2 f1");
  ck_assert_ptr_null(rn1);

  rn2 = (int *)CommandList_deepRun(mainList, NULL, "A a1 s1");
  ck_assert_ptr_null(rn2);

  rn3 = (int *)CommandList_deepRun(mainList, NULL, "B a1 s1");
  ck_assert_ptr_null(rn3);

  rn4 = (int *)CommandList_deepRun(mainList, NULL, "B b1 q1");
  ck_assert_ptr_null(rn4);

  rn5 = (int *)CommandList_deepRun(mainList, NULL, "D b1 t1");
  ck_assert_ptr_null(rn5);
  // To store answers

  // Answer checks
  int *r1, *r2, *r3, *r4, *r5;

  r1 = (int *)CommandList_deepRun(mainList, NULL, "A a1 f1");
  ck_assert_ptr_nonnull(r1); // Avoid segfault
  ck_assert_int_eq(*r1, 1);

  r2 = (int *)CommandList_deepRun(mainList, NULL, "A a2 s2");
  ck_assert_ptr_nonnull(r2); // Avoid segfault
  ck_assert_int_eq(*r2, 2);

  r3 = (int *)CommandList_deepRun(mainList, NULL, "B b1 t3");
  ck_assert_ptr_nonnull(r3); // Avoid segfault
  ck_assert_int_eq(*r3, 3);

  r4 = (int *)CommandList_deepRun(mainList, NULL, "B b2 q4");
  ck_assert_ptr_nonnull(r4); // Avoid segfault
  ck_assert_int_eq(*r4, 4);

  r5 = (int *)CommandList_deepRun(mainList, NULL, "A a2 s2");
  ck_assert_ptr_nonnull(r5); // Avoid segfault
  ck_assert_int_eq(*r5, 2);

  CommandList_deepFreeWipe(mainList);
}
END_TEST

// No need for search in smoke

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Commander List");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_CommandNode_create);
  tcase_add_test(tc_sm, test_CommandNode_createFullFork);
  tcase_add_test(tc_sm, test_CommandNode_createFullFunc);
  tcase_add_test(tc_sm, test_CommandNode_searchByMame);
  tcase_add_test(tc_sm, test_CommandNode_deepRun);

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
