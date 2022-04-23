#ifndef STATE_CONDITION_H
#define STATE_CONDITION_H

#include "../Lists/list.h"
#include "../consts.h"
#include <stdarg.h>

typedef boolean (*checkerFunct)(void *);

// Some typedefs
typedef struct State State;
typedef struct StateCondition StateCondition;
typedef struct StateConditionNode StateConditionNode;
typedef struct StateConditionNode StateConditionList;

// Used to test to which state the machine should transit
struct StateCondition {
  checkerFunct check;
  State *stateToPtr;
  char *stateToName;
  // The lower the priority higher level of precedence
  // Think like a number in a queue
  USint priority;
};

struct StateConditionNode {
  struct StateCondition *dt;
  struct StateConditionNode *next;
};

/*
 * STATECONDITION FUNCTIONS
 */
short int priorityComparator(void* vSCond1,void* vSCond2);

void StateCondition_free(void *sttCond);

StateCondition *StateCondition_create(checkerFunct check, State *sttPtr,
                                      int priority);

boolean StateCondition_check(void *vSttCond, void* data);

/*
 * STATECONDITIONNODE FUNCTIONS
 */

void StateConditionNode_free(StateConditionNode *sttNode, wipeDataFunc wipeData);
#define StateConditionNode_freeSafe(s) StateConditionNode_free(s, NULL)
#define StateConditionNode_freeWipe(s) StateConditionNode_free(s, &StateCondition_free)

StateConditionNode *StateConditionNode_create(StateCondition *scond,
                                              StateConditionNode *next);
#define StateConditionNode_createFull(f, s, p, n)                              \
  StateConditionNode_create(StateCondition_create(f, s, p), n)

StateConditionNode *StateConditionNode_attatch(StateConditionNode *cur,
                                           StateConditionNode *newScnd);
/*
 * STATECONDITIONLIST FUNCTIONS
 */
void StateConditionList_free(StateConditionList *sttCond, wipeDataFunc wipeData);
#define StateConditionList_freeSafe(s) StateConditionList_free(s, NULL)
#define StateConditionList_freeWipe(s) StateConditionList_free(s, &StateCondition_free)

StateConditionList *StateConditionList_sortedAdd(StateConditionList *list,
                                                 StateConditionNode *newScnd,
                                                 sortFunc sort,
                                                 boolean swapData);

#define StateConditionList_add(s, n)                                           \
  StateConditionList_sortedAdd(s, n, priorityComparator, false)

StateConditionNode *StateConditionList_search(StateConditionList *sttList,
                                              testFunc tst, void *data);
/*
 * Implementation only functions
 */
State *StateConditionList_checkForNextState(StateConditionList *list,
                                            void *data);
char *StateConditionList_checkForNextStateName(StateConditionList *list,
                                               void *data);

#endif
