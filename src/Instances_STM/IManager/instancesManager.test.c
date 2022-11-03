#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "instancesManager.h"

START_TEST(test_isntancesManager_create) {
  int a, c;
  void *smcs = &a, *cmdr = &c;

  InstancesManager *inm = InstancesManager_create(cmdr, smcs, 500);

  ck_assert_int_eq(inm->last_updated, 0);
  ck_assert_ptr_eq(inm->commander, cmdr);
  ck_assert_ptr_eq(inm->stateMachines, smcs);
  ck_assert_int_eq(inm->delay, 500);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Instances Manager");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_isntancesManager_create);

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
