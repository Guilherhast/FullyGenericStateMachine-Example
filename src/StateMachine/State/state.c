#include "../state.h"
#include <stdio.h>
#include <stdlib.h>

// State functions
void State_free(void *vStt) {
  State *stt = (State *)vStt;
  free(stt->name);
  free(stt);
}
State *State_create(char *name, StateConditionList *sCondList,
                    TransitionList *transitions, stateChangeFunc enter,
                    stateUpdateFunc update, stateChangeFunc exit) {

  State *stt = malloc(sizeof(State));
  char *str = malloc(strlen(name) + 1);
  strcpy(str, name);

  if (stt == NULL) {
    return NULL;
  }

  stt->lastSignalSent = 0;
  stt->lastTimeEntered = 0;
  stt->lastUpdated = 0;

  stt->name = str;

  stt->stateConditionList = sCondList;
  stt->transitions = transitions;

  stt->enter = enter;
  stt->update = update;
  stt->exit = exit;

  return stt;
}
void* State_enter(State *stt, void *data) {
  time(&stt->lastTimeEntered);

  if (stt->enter) {
    return stt->enter(stt, data);
  }
  return NULL;
}
void* State_update(State *stt, void *data) {
  time(&stt->lastUpdated);

  if (stt->enter) {
    return stt->update(stt, data);
  }
  return NULL;
}
void* State_exit(State *stt, void *data) {
  if (stt->exit) {
    return stt->exit(stt, data);
  }
  return NULL;
}
