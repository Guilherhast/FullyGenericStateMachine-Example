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
  if (cmd->func) {
    return cmd->func(list, str);
  } else {
    return NULL;
  }
}

boolean Command_nameEqual(void *vCmd, void *vName) {
  Command *cmd = (Command *)vCmd;
  char *n = (char *)vName;
  return (strcmp(cmd->name, n) == 0);
}
