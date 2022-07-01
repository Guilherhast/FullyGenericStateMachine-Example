#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../stateMachine.h"

int IDCOUNTER = 0;

void StateMachine_free(void *smc) { free(smc); }

StateMachine *StateMachine_create(unsigned int id, StateList *possibleStates,
                                  State *initialState, dataMerger merger,
                                  void *data) {

  if (possibleStates == NULL) {
    fprintf(stderr, "Can't create a stateMachine without a state\n");
    return NULL;
  }
  if (data && !merger) {
    fprintf(stderr, "Can't create a stateMachine with data without a merger\n");
    return NULL;
  }

  StateMachine *smc = malloc(sizeof(StateMachine));

  smc->id = id == 0 ? IDCOUNTER++ : id;

  smc->online = true;

  time(&smc->creation);
  smc->lastUpdate = smc->creation;
  smc->lastStateChange = smc->creation;
  smc->lastInfo = smc->creation;

  smc->possibleStates = possibleStates;

  // Tenary is too obscurated?
  if (initialState == NULL) {
    smc->currentState = smc->initialState = possibleStates->dt;
  } else {
    smc->currentState = smc->initialState = initialState;
  }

  smc->transition = NULL;

  smc->merger = merger;
  smc->data = data;

  return smc;
}

void *StateMachine_testAndTransit(StateMachine *smc) {
  void *base = NULL;
  if (smc->transition) {
    if (smc->transition->tFunc) {
      base = smc->transition->tFunc(smc);
    }
    if (smc->transition->stateTo) {
      void *tmpData = NULL;

      tmpData = State_exit(smc->currentState, smc->data);
      base = smc->merger(base, tmpData);

      tmpData = State_enter(smc->transition->stateTo, smc->data);
      base = smc->merger(base, tmpData);

      smc->currentState = smc->transition->stateTo;
    }
    smc->transition = NULL;
  }
  return base;
}

void *StateMachine_update(StateMachine *smc) {
  void *trnData = NULL, *upData = NULL;

  smc->transition = StateMachine_check(smc);
  trnData = StateMachine_testAndTransit(smc);
  upData = State_update(smc->currentState, smc->data);

  return smc->merger(trnData, upData);
}

void *StateMachine_setState(StateMachine *smc, char *sttName) {
  TransitionNode *tn =
      TransitionList_searchRealByName(smc->currentState->transitions, sttName);
  smc->transition = tn->dt;
  return StateMachine_testAndTransit(smc);
}

void *StateMachine_triggerState(StateMachine *smc, char *sttName) {
  TransitionNode *tn = TransitionList_searchTriggerByName(
      smc->currentState->transitions, sttName);
  if (tn && tn->dt->tFunc) { // We expect tn->dt is defined
    return tn->dt->tFunc(smc);
  }
  return NULL;
}

Transition *StateMachine_check(StateMachine *smc) {
  return StateConditionList_checkForTransition(
      smc->currentState->stateConditionList, smc->data);
}
