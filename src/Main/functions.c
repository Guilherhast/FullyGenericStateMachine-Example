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
void setup(int argc, char *argv[]) {

  if (argc < MINNARGS) {
    fprintf(stderr, "Error: Missing args.\n");
    fprintf(stderr, "Received %d, expected at least %d\n", argc, MINNARGS);
    exit(1);
  }

  FILE *cfg = fopen(argv[1], "r");

  if (!cfg) {
    fprintf(stderr, "Error: Could'nt open file %s\n", argv[1]);
  }

  StateMachineList *stateMachines = GateStateMachine_createAll(cfg);
  fclose(cfg);

  CommandList *commander = instCommander_create();

  iManager = InstancesManager_create(commander, stateMachines, DELAY);

  if (!iManager) {
    proccesExit(1);
  }

  char str[MAXLINE];
  sprintf(str, "Updating each %dms\n", DELAY);

  IOManager_updateAll("The state machines were initalizated.\n");
  IOManager_updateAll(str);
}

void update() { //<- Domesticating my linter
  InstancesManager_cycle(iManager);
}
