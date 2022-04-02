#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "consts.h"
#include "stateCondition.h"

#include "state.h"

// Represents a state machine
struct StateMachine {
  unsigned int id;

  time_t creation;
  time_t lastUpdate;

  void* data;

  State *initialState;
  State *currentState;
  State *stateTo;

  State *possibleStates;

  struct StateMachine* next;
};

typedef struct StateMachine StateMachine;

StateMachine *StateMachine_create(unsigned int id, State *possibleStates,
                                  State *initialState, StateMachine *next,
                                  void* data);

void StateMachine_getArgs(StateMachine *smc, va_list *list);

StateMachine *StateMachine_attatch(StateMachine *current,
                                   StateMachine *newStateMachine);

StateMachine *StateMachine_listAdd(StateMachine *list,
                                   StateMachine *newStateMachine);

#endif
