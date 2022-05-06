#ifndef TRANSITION_H
#define TRANSITION_H

#include "../consts.h"

typedef struct StateMachine StateMachine;
typedef struct State State;
typedef struct Transition Transition;

//It may also receive data
typedef void (*transitionFunct)(StateMachine *);

struct Transition {
  transitionFunct tFunc;

  State *stateTo;
  void *data;

  boolean temporary;
};


/*
 *Transiction functions
 */
void Transition_free(Transition *trn);

Transition *Transition_create(State *stateTo, transitionFunct tFunc,
                              void *data, boolean temporary);

#define Transition_createTmp(s,f,b) Transition_create(s,f,b,true)
#define Transition_createPrm(s,f,b) Transition_create(s,f,b,false)

#endif
