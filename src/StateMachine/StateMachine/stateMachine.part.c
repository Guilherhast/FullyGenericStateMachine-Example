#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../stateMachine.h"

int IDCOUNTER = 0;

StateMachine *StateMachine_create(unsigned int id, State *possibleStates,
                                  State *initialState, StateMachine *next,
                                  void *data) {

  if (possibleStates == NULL) {
    fprintf(stderr, "Can't create a stateMachine without an state\n");
    exit(1);
  }

  StateMachine *smc = malloc(sizeof(StateMachine));

  smc->id= id==0? IDCOUNTER++:id;

  time(&smc->creation);
  smc->lastUpdate = smc->creation;

  smc->possibleStates = possibleStates;

  if (initialState == NULL) {
    smc->currentState = smc->initialState = possibleStates;
  } else {
    smc->initialState = initialState;
  }
  smc->stateTo = NULL;

  smc->next = next;

  smc->data = data;

  return smc;
}

void StateMachine_free(StateMachine *smc) { free(smc); }

void StateMachine_listFree(StateMachine *smc) {
  StateMachine *next;
  while (smc != NULL) {
    next = smc->next;
    StateMachine_free(smc);
    smc = next;
  }
}

StateMachine *StateMachine_attatch(StateMachine *current,
                                   StateMachine *newStateMachine) {
  if (current == NULL) {
    newStateMachine->next = NULL;
    return newStateMachine;
  }

  newStateMachine->next = current->next;
  current->next = newStateMachine;
  return current;
}

StateMachine *StateMachine_listAdd(StateMachine *list,
                                   StateMachine *newStateMachine) {
  // If the list is empty
  // Return the added state
  if (list == NULL) {
    newStateMachine->next = list;
    return newStateMachine;
  }

  StateMachine *cur = list;

  while (cur->next) {
    cur = cur->next;
  }

  StateMachine_attatch(cur, newStateMachine);

  return list;
}
