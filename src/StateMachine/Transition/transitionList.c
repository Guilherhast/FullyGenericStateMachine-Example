#include "../../Lists/list.h"
#include "transition.h"
#include <stdio.h>


/*
 * Adapted StateConditionNode functions
 */

void TransitionNode_free(TransitionNode *trnNode, wipeDataFunc wipeData) {
  ListNode_free((ListNode *)trnNode, wipeData);
}

TransitionNode *TransitionNode_create(Transition *trn, TransitionNode *next) {
  return (TransitionNode *)ListNode_create(trn, (ListNode *)next);
}

TransitionNode *TransitionNode_attatch(TransitionNode *curTrn,
                                       TransitionNode *newTrn) {
  return (TransitionNode *)ListNode_attatch((ListNode *)curTrn,
                                            (ListNode *)newTrn);
}

TransitionNode *TransitionNode_clone(TransitionNode *nd) {
  return (TransitionNode *)ListNode_clone((ListNode *)nd);
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

TransitionList *TransitionList_cat(TransitionList *list1,
                                   TransitionList *list2) {
  return (TransitionList *)List_cat((List *)list1, (List *)list2);
}

TransitionNode *TransitionList_search(TransitionList *scondList, testFunc tst,
                                      void *data) {
  return (TransitionNode *)List_search((List *)scondList, tst, data);
}
TransitionNode *TransitionList_searchNth(TransitionList *trnList, testFunc tst,
                                         void *data, unsigned short int n) {
  return (TransitionNode *)List_searchNth((List *)trnList, tst, data, n);
}

TransitionList *TransitionList_findAndCloneMany(TransitionList *list,
                                                testFunc test, sortFunc sort,
                                                USint n, void **data) {

  return (TransitionList *)List_findAndCloneMany((List *)list, test, sort, n,
                                                 data);
}
/*
 * Original StateConditionList functions  (find a better name)
 */

// Search functions
// StateConditionNode functions
boolean Transition_triggerNameEqual(void *vTrn, void *vName) {
  return Transition_nameEqual(vTrn, vName, true);
}
boolean Transition_realNameEqual(void *vTrn, void *vName) {
  return Transition_nameEqual(vTrn, vName, false);
}
boolean Transition_nameEqual(void *vTrn, void *vName, boolean searchTrigger) {
  if (!(vTrn && vName)) {
    return false;
  }
  Transition *trn = (Transition *)vTrn;
  char *name = (char *)vName;

  if (searchTrigger != trn->isTrigger) {
    return false;
  }
  return (strcmp(trn->stateToName, name) == 0);
}
