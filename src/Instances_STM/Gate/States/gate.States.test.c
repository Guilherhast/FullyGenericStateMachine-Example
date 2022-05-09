#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../gate.h"

/*TODO
 *
 * This is a condition. If it is a condition it is not
 * the role of the state part.
 * The state machine should do it using the state conditions
 *
 * Implement the sendSignalInterval
 * Check if the trigger condition has occured
 * Check if the time has passed
 * test if the interval has passed
 *
 *
 * Maybe the update will:
 *	Call the ckeck
 *	Call the update functions
 *
 *	Add to the state
 *	time_t Last time entered
 *	time_t Last signal sent
 *
 *	Only tests
 *	In a signal write the waited message
 *
 *	Add to the stateMachine
 *	time_t lastStateChange
 *
 *
 *
 */

START_TEST(test_State_EnterBase) {
  data_smc_gate data;
  time_t now, long_ago;
  time(&now);

  long_ago = now - 3 * MILIS_IN_DAY;

  data.last_state_change = long_ago;

  State_Enter_base("", &data);

  int d = (int)difftime(now, data.last_state_change);

  ck_assert_int_eq(d, 0);
}
END_TEST

// TODO:
// Supress output
START_TEST(test_State_Open_enter) {
  data_smc_gate data;
  time_t now, long_ago;
  time(&now);

  long_ago = now - 3 * MILIS_IN_DAY;

  data.last_state_change = long_ago;
  data.last_open_warnning = long_ago;

  State_Open_enter(0, &data);

  int d = (int)difftime(now, data.last_open_warnning);

  ck_assert_int_eq(d, 0);
}
END_TEST

Suite *default_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate states");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_State_EnterBase);
  tcase_add_test(tc_sm, test_State_Open_enter);

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
