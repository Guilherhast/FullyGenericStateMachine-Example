#ifndef GATE_BODY_H
#define GATE_BODY_H

#define Sl_searchByNameReturnData(l, n)                                        \
  ({                                                                           \
    StateNode *sttN = StateList_searchByName(l, n);                            \
    sttN->dt;                                                                  \
  })

#endif
