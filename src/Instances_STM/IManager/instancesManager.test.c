#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Avoid importing mocked functions
#define IOMANAGER_H
#define COMMANDER_H

typedef struct CommandList CommandList;

#include "../../TestUtils/fff.h"
#include "instancesManager.h"

DEFINE_FFF_GLOBALS;

// IOManager Mocks
FAKE_VALUE_FUNC(char *, IOManager_getNext);
FAKE_VOID_FUNC(IOManager_updateCur, char *);
FAKE_VOID_FUNC(IOManager_updateAll, char *);

// Commander Mocks
FAKE_VALUE_FUNC(void *, Commander_updateAll);
FAKE_VALUE_FUNC(void *, CommandList_deepRun, CommandList *, List *, char *);
/*
 */

void testSetup() {
  RESET_FAKE(IOManager_getNext);
  RESET_FAKE(IOManager_updateCur);
  RESET_FAKE(IOManager_updateAll);

  RESET_FAKE(Commander_updateAll);
  RESET_FAKE(CommandList_deepRun);
}

START_TEST(test_isntancesManager_create) {
  int a, c;
  void *smcs = &a, *cmdr = &c;

  InstancesManager *inm = InstancesManager_create(cmdr, smcs, 500);

  ck_assert_ptr_eq(inm->commander, cmdr);
  ck_assert_ptr_eq(inm->stateMachines, smcs);
  ck_assert_int_eq(inm->delay, 500);
}
END_TEST

START_TEST(test_isntancesManager_timeUp) {
  int a, c;
  void *smcs = &a, *cmdr = &c;

  InstancesManager *inmT = InstancesManager_create(cmdr, smcs, 200);
  InstancesManager *inmF = InstancesManager_create(cmdr, smcs, 500);

  unsigned int sleepTime = inmT->delay * 1000 + 1;
  usleep(sleepTime);

  boolean tu_true, tu_false;

  tu_true = InstancesManager_timeUp(inmT);
  tu_false = InstancesManager_timeUp(inmF);

  ck_assert(tu_true);
  ck_assert(!tu_false);
}
END_TEST

START_TEST(test_isntancesManager_cycle_null) {
  testSetup();
  int a, c;
  void *smcs = &a, *cmdr = &c;

  IOManager_getNext_fake.return_val = NULL;
  Commander_updateAll_fake.return_val = NULL;

  InstancesManager *inm = InstancesManager_create(cmdr, smcs, 100);

  // Call cycle
  InstancesManager_cycle(inm);

  // Test functions
  ck_assert_int_eq(IOManager_getNext_fake.call_count, 1);

  /*
  ck_assert_int_eq(CommandList_deepRun_fake.call_count,0);
  ck_assert_int_eq(IOManager_updateCur_fake.call_count,0);
  */

  ck_assert_int_eq(Commander_updateAll_fake.call_count, 1);
  ck_assert_int_eq(IOManager_updateAll_fake.call_count, 1);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Instances Manager");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_isntancesManager_create);
  tcase_add_test(tc_sm, test_isntancesManager_timeUp);
  tcase_add_test(tc_sm, test_isntancesManager_cycle_null);

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
