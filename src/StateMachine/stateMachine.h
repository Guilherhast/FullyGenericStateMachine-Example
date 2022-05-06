#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#define SIGNAL_WAIT_INTERVAL 5

#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "../consts.h"
#include "stateCondition.h"

#include "state.h"

// Some typedefs

typedef struct StateMachine StateMachine;
typedef struct StateMachineNode StateMachineNode;
typedef struct StateMachineNode StateMachineList;

// Represents a state machine
struct StateMachine {
  unsigned int id;

  time_t creation;
  time_t lastUpdate;

  time_t lastStateChange;
  // Last time it has received an info
  // from the controlled device
  time_t lastInfo;

  void *data;

  State *initialState;
  State *currentState;
  Transition *transition;

  StateList *possibleStates;
};

struct StateMachineNode {
  struct StateMachine *dt;
  struct StateMachineNode *next;
};

/*
 * STATEMACHINE FUNCTIONS
 */
void StateMachine_free(void *smc);

StateMachine *StateMachine_create(unsigned int id, StateList *possibleStates,
                                  State *initialState, void *data);

//void *StateMachine_getData(StateMachine *smc);

void StateMachine_update(StateMachine *smc); // Maybe it will check too
void StateMachine_changeState(StateMachine *smc);
void StateMachine_testAndTransit(StateMachine *smc);
void StateMachine_setState(StateMachine *smc, char *sttName);
Transition *StateMachine_check(StateMachine *smc);

boolean idMatch(void* a, void* b);
/*
 * STATEMACHINENODE FUNCTIONS
 */

void StateMachineNode_free(StateMachineNode *smcNode, wipeDataFunc wipeData);
#define StateMachineNode_freeSafe(s) StateMachineNode_free(s, NULL)
#define StateMachineNode_freeWipe(s) StateMachineNode_free(s, StateMachine_free)

StateMachineNode *StateMachineNode_create(StateMachine *smc,
                                          StateMachineNode *next);
#define StateMachineNode_createFull(id, ps, is, dt, nxt)                       \
  StateMachineNode_create(StateMachine_create(id, ps, is, dt), nxt)

StateMachineNode *StateMachineNode_attatch(StateMachineNode *curSmc,
                                           StateMachineNode *newSmc);
/*
 * STATELIST FUNCTIONS
 *
 * You may add a create and add function
 * Macro for the smcNodeCreateFull
 */
void StateMachineList_free(StateMachineList *list, wipeDataFunc wipeData);
#define StateMachineList_freeSafe(s) StateMachineList_free(s, NULL)
#define StateMachineList_freeWipe(s) StateMachineList_free(s, StateMachine_free)

StateMachineList *StateMachineList_sortedAdd(StateMachineList *list, StateMachineNode *node,
                               sortFunc sfn, boolean swapData);
#define StateMachineList_add(s, n) StateMachineList_sortedAdd(s, n, NULL, false)

StateMachineNode *StateMachineList_search(StateMachineList *list, testFunc tst, void *data);
#define StateMachineList_searchById(l,i) StateMachineList_search(l,&idMatch,i)

StateMachine *StateMachineList_update(StateMachineList *list);

/*
 *IMPLEMENTATION FUNCTIONS
 */
#endif
