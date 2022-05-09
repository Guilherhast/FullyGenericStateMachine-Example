#ifndef TRANSITION_H
#define TRANSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Lists/list.h"
#include "../consts.h"

typedef struct StateMachine StateMachine;
typedef struct State State;

typedef struct Transition Transition;
typedef struct TransitionNode TransitionNode;
typedef struct TransitionNode TransitionList;

// It may also receive data
typedef void (*transitionFunct)(StateMachine *);

struct Transition {
  transitionFunct tFunc;

  State *stateTo;
  char *stateToName;

  void *data;

  // boolean temporary;
};

struct TransitionNode {
  struct Transition *dt;
  struct TransitionNode *next;
};

/*
 *Transiction functions
 */
void Transition_free(void *trn);

Transition *Transition_create(State *stateTo, char *stateToName,
                              transitionFunct tFunc, void *data);

#define Transition_createFromState(s, d) Transition_create(s, s->name, NULL, d)
#define Transition_createFromFunc(n, f, d) Transition_create(NULL, n, f, d)
#define Transition_createShort(s, f, d) Transition_create(s, s->name, f, d)

/*
Transition *Transition_create(State *stateTo, transitionFunct tFunc,
void *data, boolean temporary);

#define Transition_createTmp(s,f,b) Transition_create(s,f,b,true)
#define Transition_createPrm(s,f,b) Transition_create(s,f,b,false)
*/

/*
 * TRANSITIONNODE FUNCTIONS
 */

void TransitionNode_free(TransitionNode *trnNode, wipeDataFunc wipeData);

#define TransitionNode_freeSafe(s) TransitionNode_free(s, NULL)
#define TransitionNode_freeWipe(s) TransitionNode_free(s, &Transition_free)

TransitionNode *TransitionNode_create(Transition *trn, TransitionNode *next);

#define TransitionNode_createFull(s, nm, f, d, nxt)                            \
  TransitionNode_create(Transition_create(s, nm, f, d), nxt)

#define TransitionNode_createFullFromState(s, d, n)                            \
  TransitionNode_createFull(s, s->name, NULL, d)
#define TransitionNode_createFullFromFunc(nm, f, d, nxt)                          \
  TransitionNode_createFull(NULL, n, f, d)
#define TransitionNode_createFullShort(s, f, d, n)                             \
  TransitionNode_createFull(s, s->name, f, d)

TransitionNode *TransitionNode_attatch(TransitionNode *curStt,
                                       TransitionNode *newStt);

/*
 * TRANSITIONLIST FUNCTIONS
 */

void TransitionList_free(TransitionList *trnList, wipeDataFunc wipeData);
#define TransitionList_freeSafe(s) TransitionList_free(s, NULL)
#define TransitionList_freeWipe(s) TransitionList_free(s, &Transition_free)


TransitionList *TransitionList_sortedAdd(TransitionList *trnList,
                                         TransitionNode *trnNode, sortFunc sfn,
                                         boolean swapData);
#define TransitionList_add(t,n) TransitionList_sortedAdd(t,n,NULL,false)

TransitionNode *TransitionList_search(TransitionList *trnList, testFunc tst,
                                      void *data);

#define TransitionList_searchByName(t, d)                                      \
  TransitionList_search(t, &Transition_nameEqual, d)

TransitionNode *TransitionList_searchNth(TransitionList *trnList, testFunc tst,
                                         void *data, unsigned short int n);

/*
 * Search functions
 */
boolean Transition_nameEqual(void *vStt, void *vName);

#endif
