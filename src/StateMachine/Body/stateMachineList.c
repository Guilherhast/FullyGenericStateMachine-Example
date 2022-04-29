#include "../stateMachine.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Adapted StateMachineNode functions
 */
void StateMachineNode_free(StateMachineNode *sttNode, wipeDataFunc wipeData) {
  ListNode_free((ListNode *)sttNode, wipeData);
}

StateMachineNode *StateMachineNode_create(StateMachine *stt,
                                          StateMachineNode *next) {
  return (StateMachineNode *)ListNode_create(stt, (ListNode *)next);
}

StateMachineNode *StateMachineNode_attatch(StateMachineNode *curStt,
                                           StateMachineNode *newStt) {
  return (StateMachineNode *)ListNode_attatch((ListNode *)curStt,
                                              (ListNode *)newStt);
}

/*
 * Adapted StateMachineList functions
 */

void StateMachineList_free(StateMachineList *StateMachineNode,
                           wipeDataFunc wipeData) {
  List_free((List *)StateMachineNode, wipeData);
}

StateMachineList *StateMachineList_sortedAdd(StateMachineList *sttList,
                                             StateMachineNode *sttNode,
                                             sortFunc sfn, boolean swapData) {
  return (StateMachineList *)List_sortedAdd((List *)sttList,
                                            (ListNode *)sttNode, sfn, swapData);
}

StateMachineNode *StateMachineList_search(StateMachineList *sttList,
                                          testFunc tst, void *data) {
  return (StateMachineNode *)List_search((List *)sttList, tst, data);
}
StateMachineNode *StateMachineList_searchNth(StateMachineList *sttList,
                                             testFunc tst, void *data,
                                             unsigned short int n) {
  return (StateMachineNode *)List_searchNth((List *)sttList, tst, data, n);
}

/*
 * Original StateMachineList functions  (find a better name)
 */

// Search functions
boolean idMatch(void *va, void *vb) {
  int *a = (int *)va, *b = (int *)vb;
  return *a == *b;
}
