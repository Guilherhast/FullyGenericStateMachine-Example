#include "../gate.h"
#include <time.h>

// Send signals
void Closed_sendSignal() { printf("Sending close signal\n"); }
void Open_sendSignal() { printf("Sending open signal\n"); }
void Lock_sendSignal() { printf("Sending lock signal\n"); }
void Interrupted_sendSignal() { printf("Sending interrupt signal\n"); }

// General functions
boolean timeOutCheck(time_t triggerTime, float tolerance) {
  time_t curr;
  time(&curr);
  time_t d = difftime(curr, triggerTime);
  return d >= 0 && d < tolerance;
}
boolean timeOutCheckOnlyTime(time_t triggerTime, float tolerance) {
  time_t curr;
  time(&curr);
  int d = (int)difftime(curr % MILIS_IN_DAY, triggerTime % MILIS_IN_DAY);
  return d >= 0 && d < tolerance;
}

// State functions
boolean State_open_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return timeOutCheckOnlyTime(smc_data->auto_open_time, CHECK_LOCK_TOLERANCE);
}
boolean State_lock_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return timeOutCheckOnlyTime(smc_data->auto_lock_time, CHECK_LOCK_TOLERANCE);
}
boolean State_unlock_timeOutCheck(void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  if (smc_data->ignoreAutoTriggers) {
    return false;
  }
  return timeOutCheckOnlyTime(smc_data->auto_unlock_time,
                              CHECK_UNLOCK_TOLERANCE);
}

// State Conditions
StateConditionList *conditions_stt_closed_create(State *sttLock,
                                                 State *sttOpening) {

  // Closed to locked
  // Closed to open
  StateConditionNode *lockCond = StateConditionNode_createFull(
                         &State_lock_timeOutCheck, sttLock, 1, NULL),
                     *openCond = StateConditionNode_createFull(
                         &State_open_timeOutCheck, sttOpening, 1, NULL);

  StateConditionList *list = NULL;

  list = StateConditionList_add(list, lockCond);
  list = StateConditionList_add(list, openCond);

  return list;
}

StateConditionList *conditions_stt_locked_create(State *sttClosed) {
  // Locked to
  return StateConditionNode_createFull(&State_unlock_timeOutCheck, sttClosed, 1,
                                       NULL);
}

// Factory to create state checks for the closed state
StateConditionList *conditions_stt_locked_create(State *sttLock,
                                                 State *sttUnlock) {

  StateConditionNode *unlockCond = StateCondition_create(
                         &State_unlock_timeOutCheck, sttUnlock, 1, NULL),
                     * = StateCondition_create(&State_unlock_timeOutCheck,
                                               sttUnlock, 1, temp);

  return list;
}
