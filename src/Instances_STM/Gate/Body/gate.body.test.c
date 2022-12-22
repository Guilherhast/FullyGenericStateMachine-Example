#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../gate.h"
#include "../gate.test.h"

boolean openState_timeOutCheck(void *data);
boolean lockState_timeOutCheck(void *data);
boolean unlockState_timeOutCheck(void *data);

data_smc_gate *gateData_allocTest() {
  time_t now;
  time(&now);

  time_t lock = now - 20 * MIL;
  time_t unlock = now + 20 * MIL;
  time_t open = now + 25 * MIL;

  return gateData_allocAndInitNOIG(lock, unlock, open);
}

char triggerTest[20];

void cleanUp() { triggerTest[0] = '\0'; }

void local_transitionFunc(StateMachine *smc) {
  //
  strcpy(triggerTest, TESTSTR);
}

START_TEST(test_GateBody_create) {
  data_smc_gate *dt = gateData_allocTest();
  StateMachineNode *g = GateSMC_create(1, dt);

  ck_assert_str_eq(g->dt->currentState->name, NAME_CLOSED);
  ck_assert_ptr_nonnull(g);
  ck_assert_ptr_null(g->next);

  free(dt);
  StateMachineNode_freeSafe(g);
}
END_TEST

START_TEST(test_GateBody_createList) {
  USint nGates = 4;

  data_smc_gate *dt = gateData_allocTest();
  data_smc_gate *gataDatas[] = {dt, dt, dt, dt};

  SMCID id1 = 1, id2 = 2, id3 = 3, id4 = 4;
  SMCID gateIDs[] = {id1, id2, id3, id4};

  StateMachineList *l = GateSMCS_createList(nGates, gateIDs, gataDatas);

  StateMachineNode *r1, *r2, *r3, *r4;

  r1 = StateMachineList_searchById(l,&id1);
  r2 = StateMachineList_searchById(l,&id2);
  r3 = StateMachineList_searchById(l,&id3);
  r4 = StateMachineList_searchById(l,&id4);


  ck_assert_ptr_nonnull(r1);
  ck_assert_ptr_nonnull(r2);
  ck_assert_ptr_nonnull(r3);
  ck_assert_ptr_nonnull(r4);

  ck_assert_list_size((List *)l, nGates);

  free(dt);
  StateMachineList_freeSafe(l);
}
END_TEST

START_TEST(test_GateBody_setState) {
  data_smc_gate *dt = gateData_allocTest();
  StateMachineNode *g = GateSMC_create(1, dt);

  StateMachine *smc = g->dt;

  StateMachine_setState(smc, NAME_OPENING);

  ck_assert_str_eq(smc->currentState->name, NAME_OPENING);

  free(dt);
  StateMachineNode_freeSafe(g);
}
END_TEST

START_TEST(test_GateBody_set_testAndTransit) {
  data_smc_gate *dt = gateData_allocTest();
  StateMachineNode *g = GateSMC_create(1, dt);

  StateMachine *smc = g->dt;

  StateMachine_setState(smc, NAME_OPENING);
  StateMachine_testAndTransit(smc);

  ck_assert_ptr_null(smc->transition);
  ck_assert_str_eq(smc->currentState->name, NAME_OPENING);

  free(dt);
  StateMachineNode_freeSafe(g);
}
END_TEST

START_TEST(test_GateBody_trigger) {
  void *ltf = local_transitionFunc;

  ck_assert_str_eq(triggerTest, "\0");

  data_smc_gate *dt = gateData_allocTest();
  StateMachineNode *g = GateSMC_create(1, dt);

  StateMachine *smc = g->dt;

  // Adding a mock transition to the current state
  TransitionNode *test_trn =
      TransitionNode_createFullTrigger(NAME_TEST, ltf, NULL, NULL);
  TransitionList_add(smc->currentState->transitions, test_trn);

  // Triggering the fake transiton
  StateMachine_triggerState(smc, NAME_TEST);

  ck_assert_str_eq(triggerTest, TESTSTR);

  cleanUp();

  free(dt);
  StateMachineNode_freeSafe(g);
}
END_TEST

Suite *default_suite(void) {
  cleanUp();

  Suite *s;
  TCase *tc_sm;

  s = suite_create("Gate Body");
  tc_sm = tcase_create("Smoke");

  tcase_add_test(tc_sm, test_GateBody_create);
  tcase_add_test(tc_sm, test_GateBody_createList);
  tcase_add_test(tc_sm, test_GateBody_setState);
  tcase_add_test(tc_sm, test_GateBody_set_testAndTransit);
  tcase_add_test(tc_sm, test_GateBody_trigger);

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
