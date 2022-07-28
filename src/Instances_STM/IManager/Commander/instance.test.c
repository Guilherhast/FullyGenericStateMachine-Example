#include "instance.h"
#include <check.h>

#define STTNAME1 "TEST"
#define STTNAME2 "TEST2"

void *fk_merger(void *a, void *b) { return NULL; }
#define fkm fk_merger

StateMachineList *fakeStateMachineList() {
  StateNode *sttNd =
      StateNode_createFull(STTNAME2, NULL, NULL, NULL, NULL, NULL, NULL);

  TransitionNode *trnNd =
      TransitionNode_createFullRealFromState(sttNd->dt, NULL, NULL);

  StateList *sttList =
      StateNode_createFull(STTNAME1, NULL, trnNd, NULL, NULL, NULL, sttNd);

  StateMachineList *smcList = NULL;

  for (int i = 1; i <= 5; i++) {
    StateMachineNode *m =
        StateMachineNode_createFull(i, sttList, NULL, fkm, NULL, NULL);
    ck_assert_ptr_nonnull(m);
    smcList = StateMachineList_add(smcList, m);
  }

  ck_assert_ptr_nonnull(smcList);
  return smcList;
}


END_TEST

START_TEST(test_cmdr_getDevices) { //
  StateMachineList *smcList = fakeStateMachineList();
  char *r = (char *)get_devices(smcList, NULL);
  ck_assert_ptr_nonnull(r);
  ck_assert_str_eq(r, "1\n2\n3\n4\n5\n");

  free(r);
  StateMachineList_freeWipe(smcList);
}
END_TEST

START_TEST(test_cmdr_getInfo) { //
  StateMachineList *smcList = fakeStateMachineList();

  unsigned int id = 5;
  StateMachineNode *smcNd = StateMachineList_searchById(smcList, &id);

  StateMachine_setState(smcNd->dt, "TEST2");

  char *r = (char *)get_info(smcList, "3 5");
  ck_assert_ptr_nonnull(r);
  ck_assert_str_eq(r, "3\tTEST\n5\tTEST2\n");

  free(r);
  StateMachineList_freeWipe(smcList);
}
END_TEST

Suite *smc_state_list_suite(void) {
  Suite *s;
  TCase *tc_sm;

  s = suite_create("Commander Instance");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_cmdr_getDevices);
  tcase_add_test(tc_sm, test_cmdr_getInfo);

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
