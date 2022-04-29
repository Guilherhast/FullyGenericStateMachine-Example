#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../stateMachine.h"

int IDCOUNTER = 0;

void StateMachine_free(void *smc) { free(smc); }

StateMachine *StateMachine_create(unsigned int id, StateList *possibleStates,
                                  State *initialState, void *data) {

  if (possibleStates == NULL) {
    fprintf(stderr, "Can't create a stateMachine without a state\n");
    return NULL;
  }

  StateMachine *smc = malloc(sizeof(StateMachine));

  smc->id = id == 0 ? IDCOUNTER++ : id;

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

  smc->stateTo = NULL;

  smc->data = data;

  return smc;
}

void StateMachine_update(StateMachine *smc) {
  StateMachine_testAndTransit(smc);
  // If stateTo is already defined the
  // State machine will only transit in the next
  // update
  smc->stateTo = StateMachine_check(smc);
  State_update(smc->currentState, smc->data);
}

void StateMachine_testAndTransit(StateMachine *smc) {
  if (smc->stateTo) {
    State_exit(smc->currentState, smc->data);
    State_enter(smc->stateTo, smc->data);
    smc->currentState = smc->stateTo;
    smc->stateTo = NULL;
  }
}

void StateMachine_setState(StateMachine *smc, char *sttName) {
  StateNode *sttN = StateList_searchByName(smc->possibleStates, sttName);
  smc->stateTo = sttN->dt;
}

State *StateMachine_check(StateMachine *smc) {
  return StateConditionList_checkForNextState(
      smc->currentState->stateConditionList, smc->data);
}
