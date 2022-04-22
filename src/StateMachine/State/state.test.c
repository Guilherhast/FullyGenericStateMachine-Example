#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../consts.h"
#include "../state.h"

#define STR_ENTER "ENTERED"
#define STR_EXIT "EXITED"
#define STR_UPDATED "UPDATED"
#define STR_EMPTY ""

void en(time_t dt, void *data) {
  char *s = (char *)data;
  strcpy(s,STR_ENTER);
}
void ex(time_t dt, void *data) {
  char *s = (char *)data;
  strcpy(s,STR_EXIT);
}
void up(time_t dt, void *data) {
  char *s = (char *)data;
  strcpy(s,STR_UPDATED);
}
void ss() { }

START_TEST(test_State_create) {
  State *stt;

  char *name = "StateName";

  stt = State_create(name, NULL, &en, &up, &ex, &ss);

  ck_assert_str_eq(stt->name, name);

  ck_assert_int_eq(stt->lastSignalSent, 0);
  ck_assert_int_eq(stt->lastTimeEntered, 0);
  ck_assert_int_eq(stt->lastUpdated, 0);

  ck_assert_ptr_eq(stt->enter, &en);
  ck_assert_ptr_eq(stt->update, &up);
  ck_assert_ptr_eq(stt->exit, &ex);
  ck_assert_ptr_eq(stt->sendSignal, &ss);
}
END_TEST
START_TEST(test_State_enter) {
  State *stt;
  char *name = "StateName";
  char test[8] = STR_EMPTY;

  stt = State_create(name, NULL, &en, &up, &ex, &ss);

  State_enter(stt, 0, test);

  time_t now;
  time(&now);

  int d = difftime(now, stt->lastTimeEntered);

  ck_assert_int_eq(d, 0);
  ck_assert_str_eq(test,STR_ENTER);
}
END_TEST
START_TEST(test_State_update) {
  State *stt;
  char *name = "StateName";
  char test[8] = STR_EMPTY;

  stt = State_create(name, NULL, &en, &up, &ex, &ss);

  State_update(stt, 0, test);

  time_t now;
  time(&now);

  int d = difftime(now, stt->lastUpdated);

  ck_assert_int_eq(d, 0);
  ck_assert_str_eq(test,STR_UPDATED);
}
END_TEST

START_TEST(test_State_exit) {
  State *stt;
  char *name = "StateName";
  char test[8] = STR_EMPTY;

  stt = State_create(name, NULL, &en, &up, &ex, &ss);

  State_exit(stt, 0, test);

  ck_assert_str_eq(test,STR_EXIT);
}
END_TEST
START_TEST(test_State_sendSignal) {
  State *stt;
  char *name = "StateName";

  stt = State_create(name, NULL, &en, &up, &ex, &ss);

  State_sendSignal(stt);

  time_t now;
  time(&now);

  int d = difftime(now, stt->lastSignalSent);

  ck_assert_int_eq(d, 0);
}
END_TEST
// TODO
// After State_sendSignal
// Should be 0
// It is done sir!

Suite *smc_state_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_State_create);
  tcase_add_test(tc_sm, test_State_enter);
  tcase_add_test(tc_sm, test_State_update);
  tcase_add_test(tc_sm, test_State_exit);
  tcase_add_test(tc_sm, test_State_sendSignal);

  suite_add_tcase(s, tc_sm);

  return s;
}

#ifndef COMPLETE_TEST

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = smc_state_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
#endif
