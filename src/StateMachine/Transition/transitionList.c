#include "../transition.h"
#include "../../Lists/list.h"

/*
 * Adapted StateConditionNode functions
 */

void TransitionNode_free(TransitionNode *trnNode, wipeDataFunc wipeData) {
  ListNode_free((ListNode *)trnNode, wipeData);
}

TransitionNode *TransitionNode_create(Transition *trn,
                                          TransitionNode *next) {
  return (TransitionNode *)ListNode_create(trn, (ListNode *)next);
}

TransitionNode *TransitionNode_attatch(TransitionNode *curStt,
                                       TransitionNode *newStt) {
  return (TransitionNode *)ListNode_attatch((ListNode *)curStt,
                                            (ListNode *)newStt);
}

/*
 * Adapted StateConditionList functions
 */

void TransitionList_free(TransitionList *trnList, wipeDataFunc wipeData) {
  List_free((List *)trnList, wipeData);
}

TransitionList *TransitionList_sortedAdd(TransitionList *scondList,
                                         TransitionNode *trnNode, sortFunc sfn,
                                         boolean swapData) {
  return (TransitionList *)List_sortedAdd((List *)scondList,
                                          (ListNode *)trnNode, sfn, swapData);
}

TransitionNode *TransitionList_search(TransitionList *scondList, testFunc tst,
                                      void *data) {
  return (TransitionNode *)List_search((List *)scondList, tst, data);
}
TransitionNode *TransitionList_searchNth(TransitionList *trnList, testFunc tst,
                                         void *data, unsigned short int n) {
  return (TransitionNode *)List_searchNth((List *)trnList, tst, data, n);
}

/*
 * Original StateConditionList functions  (find a better name)
 */

// Search functions
// StateConditionNode functions
boolean Transition_nameEqual(void *vStt, void *vName) {
  Transition *trn = (Transition *)vStt;
  char *name = (char *)vName;

  return (strcmp(trn->stateToName, name) == 0);
}
