#include "commander.h"

void Command_free(void *vCmd) {
  Command *cmd = (Command *)vCmd;
  if (cmd) {
    free(cmd->name);
    free(cmd);
  }
}

Command *Command_create(char *name, cmdrFunc func, CommandList *list) {
  if (!name) {
    fprintf(stderr, "Error: Cannot create command without a name.\n");
    return NULL;
  }
  // if ((!func && !list) ) {
  if ((!func && !list) || (func && list)) {
    fprintf(stderr,
            "Error: A Command should have whether a function or a list.\n");
    return NULL;
  }

  USint size = strlen(name);
  char *nm = malloc(sizeof(char) * size);

  strcpy(nm, name);

  Command *cmd = malloc(sizeof(Command));

  cmd->name = nm;
  cmd->func = func;
  cmd->list = list;

  return cmd;
}

void *Command_exec(Command *cmd, StateMachineList *list, char *str) {
  return cmd->func(list, str);
}

char *Commander_run(StateMachineList *smcList, char *cmdIn) {
  char cmd[MAXCMD];
  char *nxt;

  ///FIXME
  //Why two? This will make an wasted copy
  cp_word(cmdIn, cmd);

  nxt = cp_word(cmdIn, cmd);

  // Too manny ifs?
  // A better Ideia for a
  // more complex code would
  // be a list.
  // For now it is unecessary.
  if (!strcmp(cmd, "GET")) {
    return Commander_get(smcList, nxt);
  }
  if (!strcmp(cmd, "SET")) {
    return Commander_set(smcList, nxt);
  }

  return NULL;
}

char *Commander_get(StateMachineList *smcList, char *cmdIn) {
  char cmd[MAXCMD];
  char *nxt;

  cp_word(cmdIn, cmd);

  nxt = cp_word(cmdIn, cmd);

  if (!strcmp(cmd, "DEVICES")) {
    return Commander_getDevices(smcList, nxt);
  }
  if (!strcmp(cmd, "STATE")) {
    return Commander_getDevices(smcList, nxt);
  }

  return NULL;
}

char *Commander_getInfo(StateMachineList *smcList, char *cmdIn) {
  StateMachineNode *cur = smcList;
  char tmp[64];
  while (cur) {
    itoa(cur->dt->id, tmp);
    cur = cur->next;
  }

  return NULL;
}
char *Commander_getDevices(StateMachineList *smcList, char *cmdIn) {
  return NULL;
}

char *Commander_set(StateMachineList *smcList, char *cmdIn) { return NULL; }
char *Commander_setState(StateMachineList *smcList, char *cmdIn) {
  return NULL;
}

char *Commander_updateAll() { return NULL; }

boolean Command_nameEqual(void *vCmd, void *vName) {
  Command *cmd = (Command *)vCmd;
  char *n = (char *)vName;
  return (strcmp(cmd->name, n) == 0);
}
