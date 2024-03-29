#include "state.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Adapted StateNode functions
 */
void StateNode_free(StateNode *sttNode, wipeDataFunc wipeData) {
  ListNode_free((ListNode *)sttNode, wipeData);
}

StateNode *StateNode_create(State *stt, StateNode *next) {
  return (StateNode *)ListNode_create(stt, (ListNode *)next);
}

StateNode *StateNode_attatch(StateNode *curStt, StateNode *newStt) {
  return (StateNode *)ListNode_attatch((ListNode *)curStt, (ListNode *)newStt);
}

/*
 * Adapted StateList functions
 */

void StateList_free(StateList *StateNode, wipeDataFunc wipeData) {
  List_free((List *)StateNode, wipeData);
}

StateList *StateList_sortedAdd(StateList *sttList, StateNode *sttNode,
                               sortFunc sfn, boolean swapData) {
  return (StateList *)List_sortedAdd((List *)sttList, (ListNode *)sttNode, sfn,
                                     swapData);
}

StateNode *StateList_search(StateList *sttList, testFunc tst, void *data) {
  return (StateNode *)List_search((List *)sttList, tst, data);
}
StateNode *StateList_searchNth(StateList *sttList, testFunc tst, void *data,
                               unsigned short int n) {
  return (StateNode *)List_searchNth((List *)sttList, tst, data, n);
}

/*
 * Original StateList functions  (find a better name)
 */

// Search functions
boolean State_nameEqual(void *vStt, void *vName) {
  State *stt = (State *)vStt;
  char *name = (char *)vName;

  return (strcmp(stt->name, name) == 0);
}
