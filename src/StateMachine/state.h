#ifndef STATE_H
#define STATE_H

/*
 *Considere putting it in the
 * States folder. You will use
 * It diff in the folder
 */

#include <string.h>
#include <time.h>

#include "../Lists/list.h"
#include "../consts.h"

#include "stateCondition.h"

// Some typedefs
typedef struct State State;
typedef struct StateNode StateNode;
typedef struct StateNode StateList;

// Functions executed in state change (enter, exit)
typedef void (*stateChangeFunc)(State *stt, void *data);
typedef void (*stateUpdateFunc)(State *stt, void *data);

// Represents a single state
struct State {
  char *name;

  StateConditionList *stateConditionList;
  TransitionList *transitions;

  time_t lastTimeEntered;
  time_t lastUpdated;
  time_t lastSignalSent;

  stateChangeFunc enter;
  stateUpdateFunc update;
  stateChangeFunc exit;

};

struct StateNode {
  struct State *dt;
  struct StateNode *next;
};

/*
 * STATE FUNCTIONS
 */
void State_free(void *stt);

State *State_create(char *name, StateConditionList *sCondList,
                    TransitionList *transitions, stateChangeFunc enter,
                    stateUpdateFunc update, stateChangeFunc exit);

void State_enter(State *stt, void *data);
void State_exit(State *stt, void *data);
void State_update(State *stt, void *data);
void State_sendSignal(State *stt);

void StateList_sendSignalByName(StateList *list, char *name);

/*
 * STATENODE FUNCTIONS
 *
 * I could do all as macros but it will
 * not allow me to check types.
 * So I am using functions
 */
void StateNode_free(StateNode *sttNode, wipeDataFunc wipeData);
#define StateNode_freeSafe(s) StateNode_free(s, NULL)
#define StateNode_freeWipe(s) StateNode_free(s, State_free)

StateNode *StateNode_create(State *stt, StateNode *next);
#define StateNode_createFull(nm, cl, tr, en, up, ex, nxt)                      \
  StateNode_create(State_create(nm, cl, tr, en, up, ex), nxt)

StateNode *StateNode_attatch(StateNode *curStt, StateNode *newStt);

/*
 * STATELIST FUNCTIONS
 */
void StateList_free(StateList *sttNode, wipeDataFunc wipeData);
#define StateList_freeSafe(s) StateList_free(s, NULL)
#define StateList_freeWipe(s) StateList_free(s, State_free)

StateList *StateList_sortedAdd(StateList *sttList, StateNode *sttNode,
                               sortFunc sfn, boolean swapData);
#define StateList_add(s, n) StateList_sortedAdd(s, n, NULL, false)

StateNode *StateList_search(StateList *sttList, testFunc tst, void *data);
#define StateList_searchByName(l, n) StateList_search(l, &State_nameEqual, n)
// StateNode *StateList_searchNth(StateList *sttList,testFunc tst,void
// *data,USint n);

/*
 * IMPLEMENTATION FUNCTIONS
 */
boolean State_nameEqual(void *vStt, void *vName);
// StateNode *StateList_searchByName(StateList *list, char *name);
#endif
