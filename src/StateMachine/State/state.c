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
                    stateChangeFunc enter, stateUpdateFunc update,
                    stateChangeFunc exit, stateSignalFunc sendSignal) {

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

  stt->enter = enter;
  stt->update = update;
  stt->exit = exit;
  stt->sendSignal = sendSignal;

  return stt;
}
void State_enter(State *stt,  void *data) {
  time(&stt->lastTimeEntered);

  if (stt->enter) {
    stt->enter(data);
  }
}
void State_update(State *stt,  void *data) {
  time(&stt->lastUpdated);

  if (stt->enter) {
    stt->update(data);
  }
}
void State_exit(State *stt,  void *data) {
  if (stt->exit) {
    stt->exit(data);
  }
}
void State_sendSignal(State *stt) {
  time(&stt->lastSignalSent);
  if (stt->sendSignal) {
    stt->sendSignal();
  } else {
    fprintf(stderr, "Error: The state '%s' has no signal.\n", stt->name);
  }
  time(&stt->lastSignalSent);
}