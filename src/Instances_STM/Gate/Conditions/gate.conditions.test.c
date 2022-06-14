#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../gate.h"

boolean openState_timeOutCheck(void *data);
boolean lockState_timeOutCheck(void *data);
boolean unlockState_timeOutCheck(void *data);

START_TEST(test_timeOutCheck) {
  time_t now, few_secs_ago, many_secs_ago, secs_from_now;

  time(&now);

  few_secs_ago = now - 10;
  many_secs_ago = now - 100;
  secs_from_now = now + 10;

  boolean check_now = timeOutCheck(now, 2);
  boolean check_few_secs_ago = timeOutCheck(few_secs_ago, 30);
  boolean check_many_secs_ago = timeOutCheck(many_secs_ago, 30);
  boolean check_secs_from_now = timeOutCheck(secs_from_now, 30);

  // ck_assert(check_now);
  ck_assert(check_now);
  ck_assert(check_few_secs_ago);
  ck_assert(!check_many_secs_ago);
  ck_assert(!check_secs_from_now);
}
END_TEST

START_TEST(test_timeOutCheckOnlyTime) {
  time_t now, few_secs_ago, many_secs_ago, secs_from_now;

  time(&now);

  now -= 4 * MILIS_IN_DAY;

  few_secs_ago = now - 10;
  many_secs_ago = now - 100;
  secs_from_now = now + 10;

  boolean check_now = timeOutCheckOnlyTime(now, 2);
  boolean check_few_secs_ago = timeOutCheckOnlyTime(few_secs_ago, 30);
  boolean check_many_secs_ago = timeOutCheckOnlyTime(many_secs_ago, 30);
  boolean check_secs_from_now = timeOutCheckOnlyTime(secs_from_now, 30);

  ck_assert(check_now);
  ck_assert(check_few_secs_ago);
  ck_assert(!check_many_secs_ago);
  ck_assert(!check_secs_from_now);
}
END_TEST

START_TEST(test_State_checks) {
  time_t now;
  time(&now);

  data_smc_gate data;
  // If it does not ignore all them will trigger
  data.auto_lock_time = data.auto_unlock_time = data.auto_open_time = now;

  // Checking all states not ignoring triggers
  data.ignoreAutoTriggers = false;

  boolean stt_unlock_true = unlockState_timeOutCheck(&data);
  boolean stt_lock_true = lockState_timeOutCheck(&data);
  boolean stt_open_true = openState_timeOutCheck(&data);

  // Checking all states ignoring triggers
  data.ignoreAutoTriggers = true;

  boolean stt_unlock_false = unlockState_timeOutCheck(&data);
  boolean stt_lock_false = lockState_timeOutCheck(&data);
  boolean stt_open_false = openState_timeOutCheck(&data);

  ck_assert(stt_unlock_true);
  ck_assert(stt_lock_true);
  ck_assert(stt_open_true);

  ck_assert(!stt_unlock_false);
  ck_assert(!stt_lock_false);
  ck_assert(!stt_open_false);
  /*
   */
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate conditions");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_timeOutCheck);
  tcase_add_test(tc_sm, test_timeOutCheckOnlyTime);
  tcase_add_test(tc_sm, test_State_checks);

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
