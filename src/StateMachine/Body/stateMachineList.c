#include "stateMachine.h"
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

void *StateMachineList_updateAll(StateMachineList *smcs, dataMerger *mgr) {
  if (!smcs) {
    return NULL;
  }
  if (!mgr && !(mgr = &smcs->dt->merger)) {
    return NULL;
  }

  char *r, *tmp;
  r = malloc(sizeof(char) * MAXSTR);

  strcpy(r, "");
  for (; smcs; smcs = smcs->next) {
    tmp = StateMachine_update(smcs->dt);

    if (tmp) {
      strcat(r, tmp);
      free(tmp);
    }
  }
  return r;
}

// Search functions
boolean idMatch(void *vSmc, void *vId) {
  StateMachine *smc = (StateMachine *)vSmc;
  unsigned int *id = (unsigned int *)vId;
  return smc->id == *id;
}
