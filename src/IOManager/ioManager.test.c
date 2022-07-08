#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "ioManager.h"

static FILE *tmpIn;
static FILE *tmpOut;

#define LINEIN "getinfo 1990"
#define LINEOUT "Machine online"

void cleanNewLine(char *str, USint *size);

void before(char *line) {
  tmpIn = tmpfile();
  tmpOut = tmpfile();

  fprintf(tmpIn, "%s\n", line);

  rewind(tmpIn);

  IOManager_setStreams(tmpIn, tmpOut);
}

void after() {
  fclose(tmpIn);
  fclose(tmpOut);
}

START_TEST(test_ioManager_streams_beforeSetting) {
  FILE *inPtr, *ouPtr;
  inPtr = IOManager_getInput();
  ouPtr = IOManager_getOutput();

  // Before seting should be NULL
  ck_assert_ptr_null(inPtr);
  ck_assert_ptr_null(ouPtr);
}
END_TEST

START_TEST(test_ioManager_streams_afterSetting) {
  before(LINEIN);

  FILE *inPtr, *ouPtr;

  inPtr = IOManager_getInput();
  ouPtr = IOManager_getOutput();

  // After setting should be the given value
  ck_assert_ptr_eq(inPtr, tmpIn);
  ck_assert_ptr_eq(ouPtr, tmpOut);

  after();
}
END_TEST

START_TEST(test_ioManager_getNext) {
  before(LINEIN);

  char *data;

  data = IOManager_getNext();

  ck_assert_str_eq(data, LINEIN);

  after();
}
END_TEST

/*
START_TEST(test_ioManager_answer) {
  before(LINEIN);

  // Preparing to call the function
  ioData *data = malloc(sizeof(ioData));

  data->size = strlen(LINEOUT);
  data->str = malloc(sizeof(char) * data->size);

  strcpy(data->str, LINEOUT);

  // Calling the function
  IOManager_answer(data);

  // Preparing to read the data
  FILE *out = IOManager_getOutput();
  rewind(out);

  char *line = NULL;
  size_t size = 0;
  USint len = getline(&line, &size, out);

  cleanNewLine(line, &len);

  ck_assert_str_eq(line, data->str);


  free(data->str);
  free(data);
  after();
}
END_TEST
*/


START_TEST(test_ioManager_update) {
  before(LINEIN);

  // Preparing to call the function
  ioData *data = malloc(sizeof(ioData));

  data->size = strlen(LINEOUT);
  data->str = malloc(sizeof(char) * data->size);

  strcpy(data->str, LINEOUT);

  // Calling the function
  IOManager_update(data,data->str);

  // Preparing to read the data
  FILE *out = IOManager_getOutput();
  rewind(out);

  char *line = NULL;
  size_t size = 0;
  USint len = getline(&line, &size, out);

  cleanNewLine(line, &len);

  ck_assert_str_eq(line, data->str);

  /*
   */

  free(data->str);
  free(data);
  after();
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("IOManager");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_ioManager_streams_beforeSetting);
  tcase_add_test(tc_sm, test_ioManager_streams_afterSetting);
  tcase_add_test(tc_sm, test_ioManager_getNext);
  //tcase_add_test(tc_sm, test_ioManager_answer);
  tcase_add_test(tc_sm, test_ioManager_update);

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
