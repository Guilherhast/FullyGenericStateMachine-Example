#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "cfgUtils.h"

FILE *tmpIn;

START_TEST(test_searchProp) {
  tmpIn = tmpfile();

  char line[] = "one=hh:mm\nTWO=HH:MM\nThree=05:30";

  fprintf(tmpIn, "%s\n", line);
  rewind(tmpIn);

  char *r1 = searchProp("one", tmpIn);
  char *r2 = searchProp("TWO", tmpIn);
  char *r3 = searchProp("Three", tmpIn);
  char *r4 = searchProp("four", tmpIn);

  ck_assert_str_eq(r1, "hh:mm");
  ck_assert_str_eq(r2, "HH:MM");
  ck_assert_str_eq(r3, "05:30");
  ck_assert_ptr_null(r4);

  free(r1);
  free(r2);
  free(r3);
}
END_TEST

START_TEST(test_searchProp_noSegfault) {
  tmpIn = tmpfile();

  char line[] = "one=hh:mm TWO=HH:MM Three=05:30";

  fprintf(tmpIn, "%s\n", line);
  rewind(tmpIn);

  char *r1 = searchProp("one", tmpIn);
  char *r2 = searchProp("TWO", tmpIn);
  char *r3 = searchProp("Three", tmpIn);
  char *r4 = searchProp("four", tmpIn);

  ck_assert_str_eq(r1, "hh:mm");
  ck_assert_ptr_null(r2);
  ck_assert_ptr_null(r3);
  ck_assert_ptr_null(r4);

  free(r1);
  free(r2);
  free(r3);
}
END_TEST

Suite *module_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("cfgUtils");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_searchProp);
  tcase_add_test(tc_sm, test_searchProp_noSegfault);

  suite_add_tcase(s, tc_sm);

  return s;
}

#ifndef COMPLETE_TEST

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = module_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
#endif
