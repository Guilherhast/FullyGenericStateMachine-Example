// Includes

#include "main.h"

#include "../Instances_STM/Commander_inst/commander_inst.h"
#include "../Instances_STM/Gate/gate.h"
#include "../Instances_STM/IManager/instancesManager.h"

// Constants

#define DELAY 100

// Variables

static struct InstancesManager *iManager = NULL;

// Functions

void setup() {
  StateMachineList *stateMachines = GateStateMachine_createAll();
  CommandList *commander = instCommander_create();

  iManager = InstancesManager_create(commander, stateMachines, DELAY);

  if (!iManager) {
    proccesExit(1);
  }

  printf("The state machines were initalizated.\n");
  printf("Updating each %dms\n", DELAY);
}

void update() { //<- Domesticating my linter
  printf("DEBUG: Inside Update\n");
  InstancesManager_cycle(iManager);
  printf("DEUBG: After cycle\n");
}
