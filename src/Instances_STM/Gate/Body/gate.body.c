#include "../gate.h"
#include "gate.body.h"

void *strMerger  = StateMachine_strMerger;

data_smc_gate *gateData_allocAndInit(boolean ignoreAutoTriggers,
                                     time_t lock_time, time_t unlock_time,
                                     time_t open_time) {
  data_smc_gate *data = (data_smc_gate *)malloc(sizeof(data_smc_gate));

  time_t now;
  time(&now);

  data->ignoreAutoTriggers = ignoreAutoTriggers;

  /*Initializating  config vars*/
  data->last_open_warnning = now;

  /*Initializating auto timers*/
  data->auto_lock_time = lock_time;
  data->auto_unlock_time = unlock_time;
  data->auto_open_time = open_time;

  return data;
}

// TODO:
// Here you could put functions to set:
//	auto_lock_time
//	auto_unlock_time
//	auto_open_time
StateMachineNode *GateSMC_create(SMCID id, data_smc_gate *data) {
  // After you have made it there is no need to clone
  // States depends on data so one list will work for all
  StateList *sttL = GateStateList_createAll();
  State *iStt = Sl_searchByNameReturnData(sttL, NAME_CLOSED);

  return StateMachineNode_createFull(id, sttL, iStt, strMerger, data, NULL);
}

StateMachineList *GateSMCS_createList(USint n, SMCID *IDS,
                                      data_smc_gate **data) {
  StateMachineList *list = NULL;

  while (n--) {
    list = StateMachineList_add(list, GateSMC_create(*(IDS++), *(data++)));
  }

  return list;
}
