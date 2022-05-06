#include <stdio.h>
#include <stdlib.h>

#include "../stateCondition.h"

/*
 * Adapted StateConditionNode functions
 */
void StateConditionNode_free(StateConditionNode *sttNode,
                             wipeDataFunc wipeData) {
  ListNode_free((ListNode *)sttNode, wipeData);
}

StateConditionNode *StateConditionNode_create(StateCondition *stt,
                                              StateConditionNode *next) {
  return (StateConditionNode *)ListNode_create(stt, (ListNode *)next);
}

StateConditionNode *StateConditionNode_attatch(StateConditionNode *curStt,
                                               StateConditionNode *newStt) {
  return (StateConditionNode *)ListNode_attatch((ListNode *)curStt,
                                                (ListNode *)newStt);
}

/*
 * Adapted StateConditionList functions
 */

void StateConditionList_free(StateConditionList *sttCond,
                             wipeDataFunc wipeData) {
  List_free((List *)sttCond, wipeData);
}

StateConditionList *StateConditionList_sortedAdd(StateConditionList *scondList,
                                                 StateConditionNode *sttNode,
                                                 sortFunc sfn,
                                                 boolean swapData) {
  return (StateConditionList *)List_sortedAdd(
      (List *)scondList, (ListNode *)sttNode, sfn, swapData);
}

StateConditionNode *StateConditionList_search(StateConditionList *scondList,
                                              testFunc tst, void *data) {
  return (StateConditionNode *)List_search((List *)scondList, tst, data);
}
StateConditionNode *StateConditionList_searchNth(StateConditionList *sttList,
                                                 testFunc tst, void *data,
                                                 unsigned short int n) {
  return (StateConditionNode *)List_searchNth((List *)sttList, tst, data, n);
}

/*
 * Original StateConditionList functions  (find a better name)
 */

// Search functions
// StateConditionNode functions
StateConditionNode *StateConditionList_searchFulfilled(StateConditionList *list,
                                                       void *data) {
  return StateConditionList_search(list, &StateCondition_check, data);
}

Transition *StateConditionList_checkForTransition(StateConditionList *list,
                                            void *data) {
  StateConditionNode *nd = StateConditionList_searchFulfilled(list, data);
  return nd->dt->transition;
}
