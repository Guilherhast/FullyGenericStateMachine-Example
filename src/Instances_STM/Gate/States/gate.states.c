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
void *OpeningState_enter(State *stt, void *data) {
  return stt_str2ptr("ACTION: Opening gate.\n", data);
}
void *ForcedOpeningState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Forced gate Opening.\n", data);
}
void *IntOpeningState_enter(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Gate openning procces intrrupted!\n", data);
}
void *OpenState_enter(State *stt, void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;

  // Update last warnning time
  time(&smc_data->last_open_warnning);

  return stt_str2ptr("ACTION: Gate fully open.\n", data);
}

// EXIT TRANSITIONS
void *IntOpeningState_exit(State *stt, void *data) {
  return stt_str2ptr("WARNNING: Gate unblocked.\n", data);
}

// Update Functions
void *OpenState_update(State *stt, void *data) {
  // Look:
  // The lastTimeEntered should be a field in the data
  // This way stt would not be needed
  // The machine could be just a type
  // The machine would save the data for each instance in a file

  // Update clock.
  // If takes too long send warnning.
  data_smc_gate *smc_data = (data_smc_gate *)data;

  time_t curr;
  time(&curr);

  // Is open for too long
  if (difftime(curr, stt->lastTimeEntered) > MAX_OPEN_TIME) {
    // Has not warnned yet
    // Has warnned long ago
    if (difftime(curr, smc_data->last_open_warnning) > OPEN_WARNNING_INTERVAL) {
      // Store last warnning time
      data_smc_gate *smc_data = (data_smc_gate *)data;
      time(&smc_data->last_open_warnning);
      return stt_str2ptr("WARNNING: Time opened exeeded limit\n", data);
    }
  }
  return NULL;
}

// Factories

// Making things one line
#define IONGSE IntOpeningState_exit

StateList *GateStateList_baseFactory() {
  StateList *list = NULL;

  gs_fastCreate(list, NAME_LOCKED, LockedState_enter, NULL, NULL);

  gs_fastCreate(list, NAME_CLOSED, ClosedState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_CLOSING, ClosingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_FCDCLOSING, ForcedClosingState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_INCLOSING, IntclosingState_enter, NULL, NULL);

  gs_fastCreate(list, NAME_OPEN, OpenState_enter, OpenState_update, NULL);
  gs_fastCreate(list, NAME_FCDOPENING, ForcedOpeningState_enter, NULL, NULL);
  gs_fastCreate(list, NAME_INOPENING, IntOpeningState_enter, NULL, IONGSE);
  gs_fastCreate(list, NAME_OPENING, OpeningState_enter, NULL, NULL);

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
  gt_realFastClone(list, NAME_CLOSED, NAME_LOCKED, NAME_FCDOPENING,
                   NAME_OPENING);

  // Act of openning
  gt_realFastClone(list, NAME_FCDOPENING, NAME_OPEN, NAME_OPENING,
                   NAME_INOPENING);
  gt_realFastClone(list, NAME_OPENING, NAME_OPEN, NAME_FCDOPENING,
                   NAME_INOPENING);

  // Interrupted actions
  gt_realFastClone(list, NAME_INOPENING, NAME_INCLOSING, NAME_OPENING,
                   NAME_FCDOPENING);
  gt_realFastClone(list, NAME_INCLOSING, NAME_INOPENING, NAME_CLOSING,
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
  gt_triggerFastClone(list, NAME_CLOSED, NAME_LOCKED, NAME_FCDOPENING,
                      NAME_OPENING);

  // Act of openning
  gt_triggerFastClone(list, NAME_FCDOPENING, NAME_OPENING, NAME_INOPENING,
                      NAME_OPEN);
  gt_triggerFastClone(list, NAME_OPENING, NAME_FCDOPENING, NAME_INOPENING,
                      NAME_OPEN);

  // Interrupted actions
  gt_triggerFastClone(list, NAME_INOPENING, NAME_OPENING, NAME_FCDOPENING,
                      NAME_CLOSING, NAME_FCDCLOSING);
  gt_triggerFastClone(list, NAME_INCLOSING, NAME_OPENING, NAME_FCDOPENING,
                      NAME_CLOSING, NAME_FCDCLOSING);

  // Act of closing
  gt_triggerFastClone(list, NAME_CLOSING, NAME_FCDCLOSING, NAME_INCLOSING,
                      NAME_CLOSED);
  gt_triggerFastClone(list, NAME_FCDCLOSING, NAME_CLOSING, NAME_INCLOSING,
                      NAME_CLOSED);

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
