#include "instancesManager.h"

InstancesManager *InstancesManager_create(CommandList *cmdr,
                                          StateMachineList *smcs, USint delay) {
  InstancesManager *inm = malloc(sizeof(InstancesManager));

  inm->stateMachines = smcs;
  inm->commander = cmdr;
  inm->delay = delay;

  InstancesManager_cleanTimer(inm);

  return inm;
}

void InstancesManager_cleanTimer(InstancesManager *inm) {
  gettimeofday(&inm->last_updated, NULL);
}

long int InstancesManager_timeRemaining(InstancesManager *inm) {
  struct timeval now;
  gettimeofday(&now, NULL);

  return (now.tv_sec - inm->last_updated.tv_sec) * MILION +
         (now.tv_usec - inm->last_updated.tv_usec);
}

void InstancesManager_killTime(InstancesManager *inm) {
  usleep(InstancesManager_timeRemaining(inm));
}

boolean InstancesManager_timeUp(InstancesManager *inm) {
  struct timeval now;
  gettimeofday(&now, NULL);

  unsigned int delay = (now.tv_sec - inm->last_updated.tv_sec) * 1000 +
                       (now.tv_usec - inm->last_updated.tv_usec) / 1000;

  return delay >= inm->delay;
}

// IOManager create io
// IOmanager extractString
void InstancesManager_cycle(InstancesManager *inm) {
  char *cmdIn = NULL, *cmdOut = NULL; // Should I free?

  // Consider sleeping until delay
  while ((cmdIn = IOManager_getNext()) ) {
    cmdOut =
        CommandList_deepRun(inm->commander, (List *)inm->stateMachines, cmdIn);

    IOManager_updateCur(cmdOut);

    // Cleaning data
    free(cmdIn);
    free(cmdOut);
  }

  cmdOut = Commander_updateAll(inm->stateMachines);
  InstancesManager_cleanTimer(inm);
  IOManager_updateAll(cmdOut);

  // Cleaning data
  free(cmdOut);
  InstancesManager_killTime(inm);
}
