#ifndef STATE_H
#define STATE_H

#include <string.h>
#include <time.h>

#include "../Lists/list.h"
#include "../consts.h"

#include "stateCondition.h"

// Functions executed in state change (enter, exit)
typedef void (*stateChangeFunc)(time_t dt, void *data);
typedef void (*stateUpdateFunc)(time_t dt, void *data);
typedef void (*stateSignalFunc)();

// Some typedefs
typedef struct State State;
typedef struct StateNode StateNode;
typedef struct StateNode StateList;

// Represents a single state
struct State {
  char *name;

  StateCondition *stateConditionList;

  time_t lastTimeEntered;
  time_t lastUpdated;
  time_t lastSignalSent;

  stateChangeFunc enter;
  stateUpdateFunc update;
  stateChangeFunc exit;

  stateSignalFunc sendSignal;
};

struct StateNode {
  struct State *dt;
  struct StateNode *next;
};

/*
 * STATE FUNCTIONS
 */
void State_free(void *stt);

State *State_create(char *name, StateCondition *stateConditionList,
                    stateChangeFunc enter, stateUpdateFunc update,
                    stateChangeFunc exit, stateSignalFunc sendSignal);

void State_enter(State *stt, time_t dt, void *data);
void State_exit(State *stt, time_t dt, void *data);
void State_update(State *stt, time_t dt, void *data);
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
#define StateNode_createFull(nm, cl, en, up, ex, ss, nxt)                      \
  StateNode_create(State_create(nm, cl, en, up, ex, ss), nxt)

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
// StateNode *StateList_searchNth(StateList *sttList,testFunc tst,void
// *data,USint n);

/*
 * IMPLEMENTATION FUNCTIONS
 */
StateNode *StateList_searchByName(StateList *list, char *name);

#endif
