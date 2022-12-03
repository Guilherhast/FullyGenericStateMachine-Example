#include "commander_inst.h"
// Functions
// You may put it in another file
void *get_devices(void *list, char *NA) {
  if (!list || NA) {
    return NULL;
  }

  StateMachineList *smcList = (StateMachineList *)list;

  StateMachineList *cur = smcList;

  char *r = malloc(sizeof(char) * MAXMSG);
  r[0] = '\0';

  char bff[SIZEBUFFERID];
  do {
    itoa(cur->dt->id, bff);
    strcat(r, bff);
    strcat(r, "\n");

    cur = cur->next;
  } while (cur);

  return r;
}

void *get_info(void *list, char *str) {
  if (!list || !str) {
    return NULL;
  }
  StateMachineList *smcList = (StateMachineList *)list;

  unsigned int *idList = strToIdList(str);
  unsigned int *idListPtr = idList;

  StateMachineNode *tmp;

  char *r = malloc(sizeof(char) * MAXMSG);
  r[0] = '\0';
  char bff[SIZEBUFFERINFO];

  unsigned int id;
  while (idList && *idList != 0) {
    id = *idList;

    tmp = StateMachineList_searchById(smcList, &id);
    if (tmp) {
      sprintf(bff, "%d\t%s\n", tmp->dt->id, tmp->dt->currentState->name);
      strcat(r, bff);
    }
    idList++;
  }

  free(idListPtr);
  return r;
}

void *set_state(void *list, char *str) {
  // Secutity tests
  if (!list || !str) {
    return NULL;
  }
  StateMachineList *smcList = (StateMachineList *)list;

  char sttTo[MAXSTR];
  sttTo[0] = '\0';
  char *nxt = cp_word(str, sttTo);

  if (!nxt || !sttTo[0]) {
    fprintf(stderr, "Error: command set_state wrong string format.\n");
    return NULL;
  }

  unsigned int *idList = strToIdList(nxt);

  if (!idList) {
    fprintf(stderr, "Error: command set_state can't retrieve ids.\n");
    return NULL;
  }

  unsigned int id;
  char *r = malloc(sizeof(char) * MAXMSG);
  char bff[SIZEBUFFERINFO];
  char *update_resp;

  r[0] = '\0';
  StateMachineNode *tmp;

  // TODO:
  // Put it in a separated function
  while (*idList != 0) {
    id = *idList;

    tmp = StateMachineList_searchById(smcList, &id);
    if (tmp) {
      update_resp = NULL;

      update_resp = StateMachine_setState(tmp->dt, sttTo);
      sprintf(bff, "%d\n%s\n", tmp->dt->id, update_resp);
      strcat(r, bff);

      free(update_resp);
    }
    idList++;
  }

  return r;
}

// Command lists
CommandList *instCommander_create() {
  // Func
  // Get
  CommandNode *node_func_getInfo =
      CommandNode_createFullFunc("info", get_info, NULL);
  CommandNode *node_func_getDev =
      CommandNode_createFullFunc("devices", get_devices, node_func_getInfo);
  // Set
  CommandNode *node_func_setState =
      CommandNode_createFullFunc("set", set_state, NULL);

  // Forks
  CommandNode *node_fork_get =
      CommandNode_createFullFork("get", node_func_getDev, node_func_setState);

  return node_fork_get;
}

void *Commander_updateAll(StateMachineList *smcs) {
  return StateMachineList_updateAll(smcs, NULL);
}
