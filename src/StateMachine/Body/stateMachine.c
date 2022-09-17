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
  if (!merger) {
    fprintf(stderr, "Can't create a stateMachine without a merger\n");
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
      void *holder;

      holder = base;
      tmpData = State_exit(smc->currentState, smc->data);
      base = smc->merger(base, tmpData);
      free(holder);

      holder = base;
      tmpData = State_enter(smc->transition->stateTo, smc->data);
      base = smc->merger(base, tmpData);
      free(holder);

      smc->currentState = smc->transition->stateTo;
    }
    smc->transition = NULL;
  }
  return base;
}

void *StateMachine_update(StateMachine *smc) {
  void *trnData = NULL, *upData = NULL, *resp = NULL;

  smc->transition = StateMachine_check(smc);
  trnData = StateMachine_testAndTransit(smc);
  upData = State_update(smc->currentState, smc->data);

  resp = smc->merger(trnData, upData);

  free(trnData);
  free(upData);

  return resp;
}

void *StateMachine_setState(StateMachine *smc, char *sttName) {
  TransitionNode *tn =
      TransitionList_searchRealByName(smc->currentState->transitions, sttName);
  if (tn) {
    smc->transition = tn->dt;
  } else {
    fprintf(stderr, "Error: Can't find transition for state '%s'\n", sttName);
  }
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

// Help functions
void *StateMachine_strMerger(void *str1, void *str2) {
  char *tmp = "";
  if (!str1) {
    str1 = tmp;
  }
  if (!str2) {
    str2 = tmp;
  }

  int s1 = strlen((char *)str1);
  int s2 = strlen((char *)str2);

  char *str = malloc(sizeof(char) * (1 + s1 + s2));

  str[0] = '\0';
  strcat(str, str1);
  strcat(str, str2);

  return str;
}
