#include "instancesManager.h"

InstancesManager *InstancesManager_create(StateMachineList *smcs, USint delay) {
  InstancesManager *inm = malloc(sizeof(InstancesManager));

  inm->stateMachines = smcs;
  inm->delay = delay;

  inm->last_updated = 0;

  return inm;
}

void InstancesManager_cleanTimer(InstancesManager *inm) {
  time(&inm->last_updated);
}

boolean InstancesManager_timeUp(InstancesManager *inm) {
  time_t now;
  time(&now);

  return (now - inm->last_updated) < inm->delay;
}

// IOManager create io
// IOmanager extractString
void InstancesManager_cycle(InstancesManager *inm) {
  char *cmdIn, *cmdOut; // Should I free?

  while ((cmdIn = IOManager_getNext()) || !InstancesManager_timeUp(inm)) {
    cmdOut = Commander_run(inm->stateMachines, cmdIn);

    // Cleaning data
    free(cmdIn);
    free(cmdOut);
  }

  cmdOut = Commander_updateAll();
  InstancesManager_cleanTimer(inm);
  IOManager_updateAll(cmdOut);

  // Cleaning data
  free(cmdOut);
}
