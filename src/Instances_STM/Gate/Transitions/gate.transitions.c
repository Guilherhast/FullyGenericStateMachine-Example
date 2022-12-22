#include "../gate.h"
#include "./gate.transitions.h"

// Send signal may be in the StateMachine
// Signal may be an struct
// Send signal may receive it
static TransitionList *tmpRealList = NULL;
static TransitionList *tmpTriggerList = NULL;

// Transition Functions

void *GateTransitions_sendSignalByName(StateMachine *smc) {
  data_smc_gate *smc_data = (data_smc_gate *)smc->data;
  char str[64];
  sprintf(str, "%d - Sending signal", smc->id);
  time(&smc_data->last_signal_sent);
  return strUtils_wrap(str, smc->transition->stateToName);
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
  TransitionList *list = NULL;
  gt_fastCreate(list, NAME_LOCKED);
  gt_fastCreate(list, NAME_CLOSED);
  gt_fastCreate(list, NAME_CLOSING);
  gt_fastCreate(list, NAME_INTERRUPTEDCLOSING);
  gt_fastCreate(list, NAME_FORCEDCLOSING);
  gt_fastCreate(list, NAME_OPENNING);
  gt_fastCreate(list, NAME_INTERRUPTEDOPENNING);
  gt_fastCreate(list, NAME_FORCEDOPENNING);
  gt_fastCreate(list, NAME_OPEN);

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
