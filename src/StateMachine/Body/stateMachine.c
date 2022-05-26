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
  smc->data = data;

  return smc;
}

void StateMachine_update(StateMachine *smc) {
  StateMachine_testAndTransit(smc);
  // If stateTo is already defined the
  // State machine will only transit in the next
  // update
  smc->transition = StateMachine_check(smc);
  State_update(smc->currentState, smc->data);
}

void StateMachine_testAndTransit(StateMachine *smc) {
  if (smc->transition) {
    if (smc->transition->tFunc) {
      smc->transition->tFunc(smc);
    }
    if (smc->transition->stateTo) {
      State_exit(smc->currentState, smc->data);
      State_enter(smc->transition->stateTo, smc->data);
      smc->currentState = smc->transition->stateTo;
    }
    // To optimize for cpu you could:
    // Put a transition object in the state machine
    // Use it to store temporary transitions
    /*
    if (smc->transition->temporary) {
    Transition_free(smc->transition);
    }
    */
    smc->transition = NULL;
  }
}

void StateMachine_setState(StateMachine *smc, char *sttName) {
  TransitionNode *tn =
      TransitionList_searchRealByName(smc->currentState->transitions, sttName);
  smc->transition = tn->dt;
}
void StateMachine_triggerState(StateMachine *smc, char *sttName) {
  TransitionNode *tn = TransitionList_searchTriggerByName(
      smc->currentState->transitions, sttName);
  if (tn && tn->dt->tFunc) {
    tn->dt->tFunc(smc);
  }
}

Transition *StateMachine_check(StateMachine *smc) {
  return StateConditionList_checkForTransition(
      smc->currentState->stateConditionList, smc->data);
}
