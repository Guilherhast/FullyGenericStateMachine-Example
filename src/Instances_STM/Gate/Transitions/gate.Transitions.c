#include "../gate.h"
#include "./gate.Transitions.h"

// Send signal may be in the StateMachine
// Signal may be an struct
// Send signal may receive it
static TransitionList *tmpRealList = NULL;
static TransitionList *tmpTriggerList = NULL;

typedef char Signal;
void SendSignal(Signal *name) {
  //
  printf("Sending signal: %s\n", name);
}

// Transition Functions
void LockedState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void ClosedState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void ClosingState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void ForcedClosingState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void IntClosingState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void OpenningState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void ForcedOpenningState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void IntOpenningState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}
void OpenState_sendSignal(StateMachine *smc) {
  SendSignal(smc->transition->stateToName);
}

boolean GateTransitions_initializationCheck() {
  if (!tmpRealList || !tmpTriggerList) {
    fprintf(stderr, "Error: First initialize the temporary lists.\n");
    fprintf(stderr, "Run: GateTransitions_initTmp()\n");
    return false;
  }
  return true;
}

// You may put some functions and variables as static
// In the gcc for testing you may
// Use sed to remove the words static
// Test the variable and leave it as static in production
TransitionList *GateTransitions_createRealTmp(StateList *sttList) {
  if (!sttList) {
    return NULL;
  }

  StateList *cur = sttList;
  TransitionList *trnList = NULL;

  do {
    trnList =
        TransitionList_add(trnList, TransitionList_createRealSoft(cur->dt));
  } while ((cur = cur->next));

  return trnList;
}

void GateTransitions_addTransitionsFromList(StateList *sttList, char *sttName,
                                            USint n, void **names,
                                            boolean isTrigger) {
  if (!GateTransitions_initializationCheck()) {
    return;
  }

  StateNode *sttN = StateList_searchByName(sttList, sttName);

  if (!sttN) {
    fprintf(stderr, "Error: GateTransitions_addTransitionsFromList:\n");
    fprintf(stderr, "Could not find state '%s' in states list.\n", sttName);
    return;
  }

  // You could put all in one list
  if (isTrigger) {
    sttN->dt->transitions = TransitionList_cat(
        sttN->dt->transitions, TransitionList_triggerFindAndCloneManyByName(
                                   tmpTriggerList, n, (void **)names));
  } else {
    sttN->dt->transitions = TransitionList_cat(
        sttN->dt->transitions, TransitionList_realFindAndCloneManyByName(
                                   tmpRealList, n, (void **)names));
  }

}

TransitionList *GateTransitions_createTriggerTmp() {
  // TODO:
  // Make a function to create the list so you can test
  TransitionList *list = NULL;
  gt_fastCreate(list, NAME_LOCKED, LockedState_sendSignal);
  gt_fastCreate(list, NAME_CLOSED, ClosedState_sendSignal);
  gt_fastCreate(list, NAME_CLOSING, ClosingState_sendSignal);
  gt_fastCreate(list, NAME_INTERRUPTEDCLOSING, IntClosingState_sendSignal);
  gt_fastCreate(list, NAME_FORCEDCLOSING, ForcedClosingState_sendSignal);
  gt_fastCreate(list, NAME_OPENNING, OpenningState_sendSignal);
  gt_fastCreate(list, NAME_INTERRUPTEDOPENNING, IntOpenningState_sendSignal);
  gt_fastCreate(list, NAME_FORCEDOPENNING, ForcedOpenningState_sendSignal);
  gt_fastCreate(list, NAME_OPEN, OpenState_sendSignal);

  return list;
}

void GateTransitions_initTmp(StateList *sttList) {
  tmpRealList = GateTransitions_createRealTmp(sttList);
  tmpTriggerList = GateTransitions_createTriggerTmp();
}

void GateTransitions_cleanTmp() {
  // Free the temporary list
  TransitionList_freeSafe(tmpRealList);
  TransitionList_freeSafe(tmpTriggerList);
}
