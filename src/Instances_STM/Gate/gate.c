#include "gate.h"

time_t createDaylyTimer(USint hour, USint min) {
  struct tm timer;

  timer.tm_hour = hour;
  timer.tm_min = min;

  return mktime(&timer);
}

StateMachineList *GateStateMachine_createAll() {
  const int nGates = 2;

  time_t open1 = createDaylyTimer(6, 30);
  time_t open2 = createDaylyTimer(7, 0);

  time_t lock = createDaylyTimer(22, 0);
  time_t unlock = createDaylyTimer(6, 0);

  SMCID ids[] = {1, 2};

  // Creating gates with the different openning time,
  // but with the same lock and unlock time
  data_smc_gate *data[] = {gateData_allocAndInitNOIG(open1, lock, unlock),
                           gateData_allocAndInitNOIG(open2, lock, unlock)};

  return GateSMCS_createList(nGates, ids, data);
}
