#ifndef STATE_H
#define STATE_H

#include <string.h>

#include "consts.h"
#include "stateCondition.h"

// Functions executed in state change (enter, exit)
typedef void (*stateChangeFunc)(unsigned long int, void* data);
typedef void (*stateUpdateFunc)(unsigned long int, void* data);

// Represents a single state
struct State {
  char *name;

  StateCondition *stateConditionList;

  stateChangeFunc enter;
  stateUpdateFunc update;
  stateChangeFunc exit;

  struct State *next;
};

typedef struct State State;

void State_free(State *stt);
void State_listFree(State *stt);

State *State_create(char *name, StateCondition *stateConditionList,
                    stateChangeFunc enter, stateUpdateFunc update,
                    stateChangeFunc exit, State *next);
State *State_attatch(State *current, State *newState);

State *State_listAdd(State *list, State *newState);
#endif
