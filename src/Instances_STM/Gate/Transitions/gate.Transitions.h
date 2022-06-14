#ifndef GATE_TRANSITIONS_H
#define GATE_TRANSITIONS_H

#define TransitionList_createRealSoft(s)                                       \
  TransitionNode_createFullRealFromState(s, NULL, NULL)

#define TransitionList_createTriggerSoft(n, f)                                 \
  TransitionNode_createFullTrigger(n, f, NULL, NULL)

#define gt_fastCreate(l, n, f)                                                 \
  {                                                                            \
    TransitionNode *tn = TransitionList_createTriggerSoft(n, f);             \
    l = TransitionList_add(l, tn);                                           \
  }

#endif
