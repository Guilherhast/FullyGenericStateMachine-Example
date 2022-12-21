#include "gate.h"

void printTime(struct tm time) {
  char buffer[128];
  char fmt[] = "%d-%m-%Y %H:%M:%S";
  // char fmt[] = "\t[%H:%M]";
  strftime(buffer, sizeof(buffer), fmt, &time);
  printf("%s\n", buffer);
}

void printTime_t(time_t time) {
  //
  printTime(*localtime(&time));
}

time_t createDaylyTimer(USint hour, USint min) {
  time_t tt;
  time(&tt);
  struct tm timer = *localtime(&tt);

  // Setting relevant
  timer.tm_hour = hour;
  timer.tm_min = min;

  timer.tm_isdst = -1;
  timer.tm_sec = 0;

  //printTime(timer);
  return mktime(&timer);
}

time_t createDaylyTimerFromStr(char *str) {
  unsigned short int hour, minuts;
  char *def = DEFAULTTIMESTR;
  if (!str) {
    str = def;
  }
  sscanf(str, "%hd:%hd", &hour, &minuts);
  return createDaylyTimer(hour, minuts);
}

StateMachineList *GateStateMachine_createAll(FILE *cfgFile) {
  char *str;


  // Get entries from cfgFile
  str = searchProp("Lock", cfgFile);
  time_t lock = createDaylyTimerFromStr(str);
  free(str);

  str = searchProp("Unlock", cfgFile);
  time_t unlock = createDaylyTimerFromStr(str);
  free(str);

  str = searchProp("Open1", cfgFile);
  time_t open1 = createDaylyTimerFromStr(str);
  free(str);

  str = searchProp("Open2", cfgFile);
  time_t open2 = createDaylyTimerFromStr(str);
  free(str);

  SMCID ids[] = {1, 2};

  // Creating gates with the different openning time,
  // but with the same lock and unlock time
  const unsigned short int nGates = 2;
  data_smc_gate *data[] = {gateData_allocAndInitNOIG(lock, unlock, open1),
                           gateData_allocAndInitNOIG(lock, unlock, open2)};

  return GateSMCS_createList(nGates, ids, data);
}
