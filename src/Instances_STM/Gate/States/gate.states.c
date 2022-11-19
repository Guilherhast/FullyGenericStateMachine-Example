#include "../gate.h"
#include "gate.states.h"

// Transition Functions
// ENTER TRANSITIONS

/*
void *stt_str2ptr(char *msg, void *data) {
  int size = strlen(msg);
  char *tmp = malloc(sizeof(char) * ++size);
  strcpy(tmp, msg);
  return tmp;
}
*/

// One liners
void *LockedState_enter(State *stt, void *data) {
  return stt_str2ptr("ACTION: Gate locked.\n", data);
}
void *ClosedState_enter(State *stt, void *data) {
  return stt_str2ptr("ACTION: Gate closed.\n", data);
}
void *ClosingState_enter(State *stt, void *data) {
  return stt_str2ptr("ACTION: Gate started closing.\n", data);
}
void *ForcedClosingState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Forced gate closing.\n", data);
}
void *IntclosingState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Gate closing procces intrrupted!\n", data);
}
void *OpenningState_enter(State *stt, void *data) {
  return stt_str2ptr("ACTION: Openning gate.\n", data);
}
void *ForcedOpenningState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Forced gate Openning.\n", data);
}
void *IntOpenningState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Gate openning procces intrrupted!\n", data);
}
void *OpenState_enter(State *stt, void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  return stt_str2ptr("ACTION: Gate fully open.\n", data);

  // Update last warnning time
  time(&smc_data->last_open_warnning);
}

// EXIT TRANSITIONS
void* IntOpenningState_exit(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Gate unblocked.\n",data);
}

// Update Functions
void* OpenState_update(State *stt, void *data) {
  // Update clock.
  // If takes too long send warnning.
  data_smc_gate *smc_data = (data_smc_gate *)data;

  time_t curr;
  time(&curr);

  // Is open for too long
  if (difftime(stt->lastTimeEntered, curr) > MAX_CLOSED_TIME) {
    // Has not warnned yet
    // Has warnned long ago
    if (difftime(smc_data->last_open_warnning, curr) > OPEN_WARNNING_INTERVAL) {
      // Store last warnning time
      data_smc_gate *smc_data = (data_smc_gate *)data;
      time(&smc_data->last_open_warnning);
      return stt_str2ptr("WARNNING: Time opened exeeded limit\n",data);
    }
  }
  return NULL;
}

// Factories

// Making things one line
#define IONGSE IntOpenningState_exit

StateList *GateStateList_baseFactory() {
  StateList *list = NULL;

  gs_fastCreate(list, NAME_LOCKED, LockedState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_CLOSED, ClosedState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_CLOSING, ClosingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_FCDCLOSING, ForcedClosingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_INCLOSING, IntclosingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_OPEN, OpenState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_FCDOPENNING, OpenState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_INOPENNING, IntOpenningState_enter, NULL, IONGSE);
  gs_fastCreate(list, NAME_OPENNING, OpenningState_enter, OpenState_update,
                NULL);

  // To create acelerating and desacelerating states
  /*
  gs_fastCreate(list, NAME_ACELERATING, &aceleratingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_DESACELERATING, &DeceleratingState_enter, NULL,
  NULL);
  */
  ;

  return list;
}
#undef IONGSE

void GateStateList_addRealTransitions(StateList *list) {

  // Closed states states
  gt_realFastClone(list, NAME_LOCKED, NAME_CLOSED);
  gt_realFastClone(list, NAME_CLOSED, NAME_LOCKED, NAME_FCDOPENNING,
                   NAME_OPENNING);

  // Act of openning
  gt_realFastClone(list, NAME_FCDOPENNING, NAME_OPEN, NAME_OPENNING,
                   NAME_INOPENNING);
  gt_realFastClone(list, NAME_OPENNING, NAME_OPEN, NAME_FCDOPENNING,
                   NAME_INOPENNING);

  // Interrupted actions
  gt_realFastClone(list, NAME_INOPENNING, NAME_INCLOSING, NAME_OPENNING,
                   NAME_FCDOPENNING);
  gt_realFastClone(list, NAME_INCLOSING, NAME_INOPENNING, NAME_CLOSING,
                   NAME_FCDCLOSING);

  // Act of closing
  gt_realFastClone(list, NAME_CLOSING, NAME_CLOSED, NAME_FCDCLOSING,
                   NAME_INCLOSING);
  gt_realFastClone(list, NAME_FCDCLOSING, NAME_CLOSED, NAME_CLOSING,
                   NAME_INCLOSING);

  // Opened state
  gt_realFastClone(list, NAME_OPEN, NAME_CLOSING, NAME_FCDCLOSING);
}

void GateStateList_addTriggerTransitions(StateList *list) {

  // Closed states states
  gt_triggerFastClone(list, NAME_LOCKED, NAME_CLOSED);
  gt_triggerFastClone(list, NAME_CLOSED, NAME_LOCKED, NAME_FCDOPENNING,
                      NAME_OPENNING);

  // Act of openning
  gt_triggerFastClone(list, NAME_FCDOPENNING, NAME_OPENNING, NAME_INOPENNING, NAME_OPEN);
  gt_triggerFastClone(list, NAME_OPENNING, NAME_FCDOPENNING, NAME_INOPENNING, NAME_OPEN);

  // Interrupted actions
  gt_triggerFastClone(list, NAME_INOPENNING, NAME_OPENNING, NAME_FCDOPENNING,
                      NAME_CLOSING, NAME_FCDCLOSING);
  gt_triggerFastClone(list, NAME_INCLOSING, NAME_OPENNING, NAME_FCDOPENNING,
                      NAME_CLOSING, NAME_FCDCLOSING);

  // Act of closing
  gt_triggerFastClone(list, NAME_CLOSING, NAME_FCDCLOSING, NAME_INCLOSING, NAME_CLOSED);
  gt_triggerFastClone(list, NAME_FCDCLOSING, NAME_CLOSING, NAME_INCLOSING, NAME_CLOSED);

  // Opened states
  gt_triggerFastClone(list, NAME_OPEN, NAME_CLOSING, NAME_FCDCLOSING);
}

void GateStateList_addTransitions(StateList *sttList) {
  GateStateList_addRealTransitions(sttList);
  GateStateList_addTriggerTransitions(sttList);
}

void GateStateList_addConditions(StateList *list) {
  GateConditions_addAll(list);
}

// Factory to create states
StateList *GateStateList_createAll() {
  StateList *list = NULL;

  list = GateStateList_baseFactory();
  GateTransitions_initTmp(list);

  GateStateList_addTransitions(list);

  GateStateList_addConditions(list);

  GateTransitions_cleanTmp();
  return list;
}
