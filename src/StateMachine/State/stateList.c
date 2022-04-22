#include "../state.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Adapted StateNode functions
 */
void StateNode_free(StateNode *sttNode, boolean wipeData) {
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

void StateList_free(StateList *StateNode, boolean wipeData) {
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
boolean nameEqual(void *vStt, void *vName) {
  State *stt = (State *)vStt;
  char *name = (char *)vName;

  return (strcmp(stt->name, name) == 0);
}

//StateNode functions
StateNode *StateList_searchByName(StateList *list, char *name) {
  return StateList_search(list, &nameEqual, name);
}

void StateList_sendSignalByName(StateList *list, char *name) {
  StateNode *stt;
  stt = StateList_searchByName(list, name);
  if (stt) {
    State_sendSignal(stt->dt);
  } else {
    fprintf(stderr, "Error: Inesistent state: %sttList.sttNode", name);
  }
}
