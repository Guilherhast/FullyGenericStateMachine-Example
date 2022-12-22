#include "../gate.h"
#include <time.h>

// General functions
boolean timeOutCheck(time_t triggerTime, float tolerance) {
  time_t curr;
  time(&curr);
  time_t d = difftime(curr, triggerTime);
  return d >= 0 && d < tolerance;
}

boolean coolDownCheck(time_t triggerTime, float coolTime) {
  time_t curr;
  time(&curr);
  time_t d = difftime(curr, triggerTime);
  return d > coolTime;
}

boolean timeOutCheckOnlyTime(time_t triggerTime, float tolerance) {
  time_t curr;
  time(&curr);
  int d = (int)difftime(curr % SECS_IN_DAY, triggerTime % SECS_IN_DAY);

  return d >= 0 && d < tolerance;
}

boolean signalCheckCooledDown(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  return coolDownCheck(smc_data->last_signal_sent, SIGNAL_COOLDOWN);
}

// State functions
boolean openState_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return signalCheckCooledDown(data) &&
         timeOutCheckOnlyTime(smc_data->auto_open_time, CHECK_OPEN_TOLERANCE);
}

boolean lockState_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return signalCheckCooledDown(data) &&
         timeOutCheckOnlyTime(smc_data->auto_lock_time, CHECK_LOCK_TOLERANCE);
}

boolean unlockState_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return signalCheckCooledDown(data) &&
         timeOutCheckOnlyTime(smc_data->auto_unlock_time,
                              CHECK_UNLOCK_TOLERANCE);
}

void GateConditions_addConditionFromName(StateList *sttList, char *sttName,
                                         char *trnName, checkerFunct check,
                                         USint priority) {
  StateNode *sttNode = StateList_searchByName(sttList, sttName);
  if (!sttNode) {
    fprintf(stderr, "Error: Could not find state: %s\n", sttName);
    exit(1);
  }

  TransitionNode *trnNode =
      TransitionList_searchTriggerByName(sttNode->dt->transitions, trnName);
  if (!trnNode) {
    fprintf(stderr, "Error: Could not find transition to: %s\n", trnName);
    exit(1);
  }

  StateConditionNode *cndNode =
      StateConditionNode_createFull(check, trnNode->dt, priority, NULL);
  if (!cndNode) {
    fprintf(stderr, "Error: Could not crete condition:\n");
    exit(1);
  }

  sttNode->dt->stateConditionList =
      StateConditionList_add(sttNode->dt->stateConditionList, cndNode);
}

void GateConditions_addAll(StateList *sttList) {
  // Close -> Open
  GateConditions_addConditionFromName(sttList, NAME_CLOSED, NAME_OPENING,
                                      openState_timeOutCheck, 1);
  // Close -> Lock
  GateConditions_addConditionFromName(sttList, NAME_CLOSED, NAME_LOCKED,
                                      lockState_timeOutCheck, 2);
  // Lock -> Close
  GateConditions_addConditionFromName(sttList, NAME_LOCKED, NAME_CLOSED,
                                      unlockState_timeOutCheck, 1);
}
