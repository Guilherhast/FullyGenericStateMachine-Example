#include <stdlib.h>
#include <time.h>

#include "../../Commander/commander.h"
#include "../Commander_inst/commander_inst.h"

#include "../../IOManager/ioManager.h"
#include "../../StateMachine/Body/stateMachine.h"


typedef struct InstancesManager InstancesManager;

// Using only functions from commander and ioManager
struct InstancesManager {
  StateMachineList *stateMachines;
  CommandList *commander;
  USint delay;
  time_t last_updated;
};

InstancesManager *InstancesManager_create(CommandList *cmdr,
                                          StateMachineList *smcs, USint delay);

void InstancesManager_cleanTimer(InstancesManager *inm);
boolean InstancesManager_timeUp(InstancesManager *inm);
void InstancesManager_cycle(InstancesManager *inm);
