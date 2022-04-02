#ifndef STATE_CONDITION_H
#define STATE_CONDITION_H

#include "consts.h"
#include <stdarg.h>

typedef boolean (*checkerFunct)(unsigned long int, void *);

typedef struct State State;

// Used to test to which state the machine should transit
struct StateCondition {
  checkerFunct check;
  char *stateToName;
  // The lower the priority higher level of precedence
  // Think like a number in a queue
  unsigned short int priority;

  // TODO: Optimized version
  State *stateToPtr;

  struct StateCondition *next;
};

typedef struct StateCondition StateCondition;

extern void StateCondition_free(StateCondition *sttCond);
extern void StateCondition_listFree(StateCondition *sttCond);

extern StateCondition *StateCondition_create(checkerFunct check, State *sttPtr,
                                             int priority,
                                             StateCondition *next);
extern StateCondition *
StateCondition_attatch(StateCondition *current,
                       StateCondition *newStateCondition);

extern StateCondition *
StateCondition_listAdd(StateCondition *list, StateCondition *newStateCondition);

extern char *StateCondition_listCheckForNextState(StateCondition *list,
                                                  unsigned long int dt,
                                                  va_list args);

extern State *StateCondition_listCheckForNextStatePtr(StateCondition *list,
                                                      unsigned long int dt,
                                                      va_list args);
#endif
