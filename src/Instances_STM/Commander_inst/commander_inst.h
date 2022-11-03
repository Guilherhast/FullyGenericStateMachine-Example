#ifndef COMMANDER_INSTANCE_H
#define COMMANDER_INSTANCE_H

#include "stdlib.h"
#include "../../Commander/commander.h"

void *get_devices(void *smcList, char *NA);
void *get_info(void *smcList, char *str);
void *set_state(void *smcList, char *str);

void *Commander_updateAll();

CommandList *instCommander_create();

#endif
