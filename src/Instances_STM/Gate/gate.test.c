#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "gate.h"

START_TEST(test_network_create) {
  StateMachineList *gateList = GateStateMachine_create();

  ck_assert_ptr_nonnull(gateList);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_network_create);

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
