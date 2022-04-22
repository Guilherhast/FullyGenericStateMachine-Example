#include "../state.h"
#include <stdio.h>
#include <stdlib.h>

// State functions
void State_free(State *stt) {
  free(stt->name);
  free(stt);
}
State *State_create(char *name, StateCondition *stateConditionList,
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

  stt->stateConditionList = stateConditionList;

  stt->enter = enter;
  stt->update = update;
  stt->exit = exit;
  stt->sendSignal = sendSignal;

  return stt;
}
void State_enter(State *stt, time_t dt, void *data) {
  time(&stt->lastTimeEntered);

  if (stt->enter) {
    stt->enter(dt, data);
  }
}
void State_update(State *stt, time_t dt, void *data) {
  time(&stt->lastUpdated);

  if (stt->enter) {
    stt->update(dt, data);
  }
}
void State_exit(State *stt,  time_t dt, void *data) {
  if (stt->exit) {
    stt->exit(dt, data);
  }
}
void State_sendSignal(State *stt) {
  time(&stt->lastSignalSent);
  if (stt->sendSignal) {
    stt->sendSignal();
  } else {
    fprintf(stderr, "Error: State has no signal. State: %s.\n", stt->name);
  }
  time(&stt->lastSignalSent);
}
