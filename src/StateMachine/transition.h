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
typedef void* (*transitionFunct)(StateMachine *);

struct Transition {
  transitionFunct tFunc;

  State *stateTo;
  char *stateToName;

  void *data;

  boolean isTrigger;
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
                              transitionFunct tFunc, boolean isTrigger,
                              void *data);

#define Transition_createRealFromState(s, d)                                   \
  Transition_create(s, s->name, NULL, false, d)
#define Transition_createRealFromFunc(n, f, d)                                 \
  Transition_create(NULL, n, f, false, d)
#define Transition_createRealShort(s, f, d)                                    \
  Transition_create(s, s->name, f, false, d)

#define Transition_createTriggerFromState(s, d)                                \
  Transition_create(s, s->name, NULL, true, d)

#define Transition_createTriggerFromFunc(n, f, d)                              \
  Transition_create(NULL, n, f, true, d)

#define Transition_createTriggerShort(n, f, d)                                 \
  Transition_create(NULL, n, f, true, d)
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

// Real transition macros
#define TransitionNode_createFullReal(s, nm, f, d, nxt)                        \
  TransitionNode_create(Transition_create(s, nm, f, false, d), nxt)

#define TransitionNode_createFullRealFromState(s, d, n)                        \
  TransitionNode_createFullReal(s, s->name, NULL, d, n)

#define TransitionNode_createFullRealFromFunc(nm, f, d, nxt)                   \
  TransitionNode_createFullReal(NULL, n, f, d, nxt)

#define TransitionNode_createFullRealShort(s, f, d, n)                         \
  TransitionNode_createFullReal(s, s->name, f, d, n)

// Trigger transition macros
#define TransitionNode_createFullTrigger(nm, f, d, nxt)                        \
  TransitionNode_create(Transition_create(NULL, nm, f, true, d), nxt)

TransitionNode *TransitionNode_attatch(TransitionNode *curStt,
                                       TransitionNode *newStt);

TransitionNode *TransitionNode_clone(TransitionNode *nd);

#define TransitionList_findAndClone(l, t, d)                                   \
  TransitionNode_clone(TransitionList_search(l, t, d))
/*
 * TRANSITIONLIST FUNCTIONS
 */

void TransitionList_free(TransitionList *trnList, wipeDataFunc wipeData);
#define TransitionList_freeSafe(s) TransitionList_free(s, NULL)
#define TransitionList_freeWipe(s) TransitionList_free(s, &Transition_free)

TransitionList *TransitionList_sortedAdd(TransitionList *trnList,
                                         TransitionNode *trnNode, sortFunc sfn,
                                         boolean swapData);
#define TransitionList_add(t, n) TransitionList_sortedAdd(t, n, NULL, false)

TransitionList *TransitionList_cat(TransitionList *list1,
                                   TransitionList *list2);

TransitionNode *TransitionList_search(TransitionList *trnList, testFunc tst,
                                      void *data);

#define TransitionList_searchTriggerByName(t, d)                               \
  TransitionList_search(t, &Transition_triggerNameEqual, d)

#define TransitionList_searchRealByName(t, d)                                  \
  TransitionList_search(t, &Transition_realNameEqual, d)

TransitionNode *TransitionList_searchNth(TransitionList *trnList, testFunc tst,
                                         void *data, unsigned short int n);

TransitionList *TransitionList_findAndCloneMany(TransitionList *list,
                                                testFunc test, sortFunc sort,
                                                USint n, void **data);

#define TransitionList_realFindAndCloneManyByName(l, n, d)                     \
  TransitionList_findAndCloneMany(l, Transition_realNameEqual, NULL, n, d)

#define TransitionList_triggerFindAndCloneManyByName(l, n, d)                  \
  TransitionList_findAndCloneMany(l, Transition_triggerNameEqual, NULL, n, d)

/*
 * Search functions
 */
boolean Transition_nameEqual(void *vStt, void *vName, boolean searchTrigger);
boolean Transition_realNameEqual(void *vStt, void *vName);
boolean Transition_triggerNameEqual(void *vStt, void *vName);

#endif
