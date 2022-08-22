#include <stdlib.h>
#include <time.h>

#include "../../IOManager/ioManager.h"
#include "../../StateMachine/stateMachine.h"

#include "Commander/commander.h"

typedef struct InstancesManager InstancesManager;

// Using only functions from commander and ioManager
struct InstancesManager {
  StateMachineList *stateMachines;
  USint delay;
  time_t last_updated;
};

InstancesManager *InstancesManager_create(StateMachineList *smcs, USint delay);
void InstancesManager_cleanTimer(InstancesManager *inm);
boolean InstancesManager_timeUp(InstancesManager *inm);
void InstancesManager_cycle(InstancesManager *inm);
