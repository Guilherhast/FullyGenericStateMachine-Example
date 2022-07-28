#include "commander.h"
#include <check.h>

USint sampleFuncTimesRun = 0;

void before(char *line) {}

void after() {}

void *sampleFunc(StateMachineList *list, char *str) {
  sampleFuncTimesRun++;
  return &str[3];
}

START_TEST(test_Commander_create) {
  int t;
  void *l = &t;

  char name1[] = "Command name 1";
  char name2[] = "Command name 2";

  Command *cmd1 = Command_create(name1, sampleFunc, NULL);
  Command *cmd2 = Command_create(name2, NULL, l);

  ck_assert_ptr_ne(name1, cmd1->name);
  ck_assert_str_eq(name1, cmd1->name);

  ck_assert_ptr_eq(sampleFunc, cmd1->func);
  ck_assert_ptr_null(cmd1->list);

  // TEST cmd2
  ck_assert_ptr_ne(name2, cmd2->name);
  ck_assert_str_eq(name2, cmd2->name);

  ck_assert_ptr_null(cmd2->func);
  ck_assert_ptr_eq(l, cmd2->list);

  // Freeing the tested
  Command_free(cmd1);
  Command_free(cmd2);
}
END_TEST

START_TEST(test_Commander_createError) {
  int t;
  void *l = &t;

  char name1[] = "Command name 1";
  char name2[] = "Command name 2";

  Command *cmd1 = Command_create(NULL, NULL, l);
  Command *cmd2 = Command_create(name2, sampleFunc, l);
  Command *cmd3 = Command_create(name1, NULL, NULL);

  ck_assert_ptr_null(cmd1);
  ck_assert_ptr_null(cmd2);
  ck_assert_ptr_null(cmd3);

  // Freeing the tested
  Command_free(cmd1);
  Command_free(cmd2);
}
END_TEST

START_TEST(test_Commander_exec) {
  int t;
  void *l = &t;
  char str[] = "abcd";

  char name[] = "Command name";
  Command *cmd = Command_create(name, sampleFunc, NULL);

  sampleFuncTimesRun = 0;

  void *r = Command_exec(cmd,l,str);

  ck_assert_ptr_eq(r,&str[3]);
  ck_assert_int_eq(sampleFuncTimesRun,1);

  Command_free(cmd);
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Commander");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_Commander_create);
  tcase_add_test(tc_sm, test_Commander_exec);
  tcase_add_test(tc_sm, test_Commander_createError);

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
