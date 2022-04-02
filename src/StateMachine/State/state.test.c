#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../consts.h"
#include "../state.h"

void en(unsigned long int dt, void* data) {}
void ex(unsigned long int dt, void* data) {}
void up(unsigned long int dt, void* data) {}

START_TEST(test_state_create) {
  State *stt;

  stt = State_create("Frist", NULL, &en, &up, &ex, NULL);

  ck_assert_str_eq(stt->name, "Frist");

  ck_assert_ptr_eq(stt->enter, &en);
  ck_assert_ptr_eq(stt->update, &up);
  ck_assert_ptr_eq(stt->exit, &ex);
}
END_TEST

START_TEST(test_State_attatch) {
  State *stt1, *stt2, *ptr;

  stt1 = State_create("Frist", NULL, &en, &up, &ex, NULL);
  stt2 = State_create("Second", NULL, &en, &up, &ex, NULL);

  ptr = State_attatch(stt1, stt2);

  ck_assert_ptr_eq(ptr, stt1);
  ck_assert_ptr_eq(stt1->next, stt2);
}
END_TEST

START_TEST(test_State_listAdd) {
  State *stt1, *stt2, *stt3, *stt4, *list;

  list = NULL;

  stt1 = State_create("Frist", NULL, &en, &up, &ex, NULL);
  stt2 = State_create("Second", NULL, &en, &up, &ex, NULL);
  stt3 = State_create("Third", NULL, &en, &up, &ex, NULL);
  stt4 = State_create("Forth", NULL, &en, &up, &ex, NULL);

  list = State_listAdd(list, stt1);
  list = State_listAdd(list, stt2);
  list = State_listAdd(list, stt3);
  list = State_listAdd(list, stt4);

  ck_assert_ptr_eq(stt3->next, stt4);
  ck_assert_ptr_eq(list, stt1);
  ck_assert_ptr_eq(stt1->next, stt2);
  ck_assert_ptr_eq(stt2->next, stt3);

  /*
  */

}
END_TEST

Suite *stateCondition_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("State Machine State");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_state_create);
  tcase_add_test(tc_sm, test_State_attatch);
  tcase_add_test(tc_sm, test_State_listAdd);

  suite_add_tcase(s, tc_sm);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = stateCondition_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
