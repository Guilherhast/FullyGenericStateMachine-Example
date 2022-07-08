#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "strUtils.h"

#define LINEIN "getinfo 1990"
#define LINEOUT "Machine online"

START_TEST(test_cp_word) {
  //
  char tst[] = "Get info 2120 1337";

  char tmp[MAXSTR];
  char *nxt = tst;

  nxt = cp_word(nxt, tmp);

  ck_assert_str_eq(tmp, "GET");
  ck_assert_ptr_eq(nxt, &tst[4]);

  nxt = cp_word(nxt, tmp);

  ck_assert_str_eq(tmp, "INFO");
  ck_assert_ptr_eq(nxt, &tst[9]);

  nxt = cp_word(nxt, tmp);

  ck_assert_str_eq(tmp, "2120");
  ck_assert_ptr_eq(nxt, &tst[14]);

  nxt = cp_word(nxt, tmp);

  ck_assert_str_eq(tmp, "1337");
  ck_assert_ptr_null(nxt);
}
END_TEST

START_TEST(test_reverse) {
  //
  char tmp[MAXSTR];

  strcpy(tmp, "ARARA");
  reverse(tmp);
  ck_assert_str_eq(tmp, "ARARA");

  strcpy(tmp, "Carros");
  reverse(tmp);
  ck_assert_str_eq(tmp, "sorraC");

  strcpy(tmp, "12345");
  reverse(tmp);
  ck_assert_str_eq(tmp, "54321");
}
END_TEST

START_TEST(test_itoa) {
  char str[64];

  itoa(545, str);
  ck_assert_str_eq(str, "545");

  itoa(-127, str);
  ck_assert_str_eq(str, "-127");

  itoa(4895, str);
  ck_assert_str_eq(str, "4895");

  itoa(0, str);
  ck_assert_str_eq(str, "0");

  itoa(-12345, str);
  ck_assert_str_eq(str, "-12345");

  itoa(-143445, str);
  ck_assert_str_eq(str, "-143445");

  itoa(1337, str);
  ck_assert_str_eq(str, "1337");
}

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("strUtils");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_cp_word);
  tcase_add_test(tc_sm, test_reverse);
  tcase_add_test(tc_sm, test_itoa);

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
