#ifndef GATE_STATES_H
#define GATE_STATES_H

#define NAME_FCDCLOSING NAME_FORCEDCLOSING
#define NAME_FCDOPENING NAME_FORCEDOPENING
#define NAME_INCLOSING NAME_INTERRUPTEDCLOSING
#define NAME_INOPENING NAME_INTERRUPTEDOPENING

#define gt_realFastClone(l, sttName, ...)                                      \
  {                                                                            \
    void *data[] = {__VA_ARGS__};                                              \
    USint n = sizeof(data) / sizeof(data[0]);                                  \
    GateTransitions_addTransitionsFromListReal(l, sttName, n, data);           \
  }

#define gt_triggerFastClone(l, sttName, ...)                                   \
  {                                                                            \
    void *data[] = {__VA_ARGS__};                                              \
    USint n = sizeof(data) / sizeof(data[0]);                                  \
    GateTransitions_addTransitionsFromListTrigger(l, sttName, n, data);        \
  }

#define gs_fastCreate(l, nm, en, up, ex)                                       \
  {                                                                            \
    StateNode *sn = StateNode_createFull(nm, NULL, NULL, en, up, ex, NULL);    \
    l = StateList_add(l, sn);                                                  \
  }

#endif
