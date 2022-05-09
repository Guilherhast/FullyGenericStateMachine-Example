#include "../gate.h"

// Transition Functions
// ENTER TRANSITIONS
void State_enterBase(char *msg, void *data) { printf("%s\n", msg); }
// One liners
void ClosedState_enter(State *stt, void *data) {
  State_enterBase("ACTION: Gate closed.", data);
}
void OpenningState_enter(State *stt, void *data) {
  State_enterBase("ACTION: Openning gate.", data);
}
void ClosingState_enter(State *stt, void *data) {
  State_enterBase("ACTION: Gate started closing.", data);
}
void LockedState_enter(State *stt, void *data) {
  State_enterBase("ACTION: Gate locked.", data);
}
void IntrruptedState_enter(State *stt, void *data) {
  State_enterBase("WARNNING: Gate closing procces intrrupted!", data);
}

void OpenState_enter(State *stt, void *data) {
  data_smc_gate *smc_data = (data_smc_gate *)data;
  State_enterBase("ACTION: Gate fully open.", data);

  // Update last warnning time
  time(&smc_data->last_open_warnning);
}

// EXIT TRANSITIONS
void IntrruptedState_exit(State *stt, void *data) {
  printf("WARNNING: Gate unblocked.");
}

// Updates
void OpenState_update(State *stt, void *data) {
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
      printf("WARNNING: Time closed exeeded limit.\n");
      // Store las warnning time
      data_smc_gate *smc_data = (data_smc_gate *)data;
      time(&smc_data->last_open_warnning);
    }
  }
}

// Factory to create states
StateList *GateStateList_createAll() {
  // TODO:
  // Make a test to check initialization order

  StateList *list = NULL;

  // Create the states linked list
  StateNode *stt_closed, *stt_openning, *stt_open, *stt_closing,
      *stt_interrupted, *stt_locked
      // Code for acelerating and decelerationg
      /*
      ,
      *stt_acelerating,
      *stt_decelerating,
      */
      ;

  stt_closed = StateNode_createFull("Closed", NULL, &ClosedState_enter, NULL,
                                    NULL, NULL);
  stt_openning = StateNode_createFull("Openning", NULL, &ClosedState_enter,
                                      NULL, NULL, NULL);
  stt_open = StateNode_createFull("Open", NULL, &OpenningState_enter, NULL,
                                  NULL, NULL);
  stt_closing =
      StateNode_createFull("Closing", NULL, &OpenState_enter, NULL, NULL, NULL);
  stt_interrupted =
      StateNode_createFull("Interrupted", NULL, &IntrruptedState_enter,
                           &IntrruptedState_exit, NULL, NULL);
  stt_locked = StateNode_createFull("Locked", NULL, &LockedState_enter, NULL,
                                    NULL, NULL);
  // Code for acelerating and decelerationg
  /*
  stt_acelerating = State_create("Acelerating", NULL,
  &aceleratingState_enter, NULL, NULL, NULL);
  stt_decelerating = State_create("Desacelerating", NULL,
  &DeceleratingState_enter, NULL, NULL, NULL);
  */
  ;

  list = StateList_add(list, stt_closed);
  list = StateList_add(list, stt_openning);
  list = StateList_add(list, stt_open);
  list = StateList_add(list, stt_closing);
  list = StateList_add(list, stt_interrupted);
  list = StateList_add(list, stt_locked);

  stt_closed->dt->stateConditionList =
      conditions_stt_closed_create(stt_locked, stt_openning);
  stt_locked->dt->stateConditionList =conditions_stt_locked_create( stt_closed);

  // Return the first state of the list
  return list;
}
