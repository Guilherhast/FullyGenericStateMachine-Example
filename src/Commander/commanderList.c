#include "../Lists/list.h"
#include "commander.h"

#include <stdio.h>

void CommandNode_free(CommandNode *trnNode, wipeDataFunc wipeData) {
  ListNode_free((ListNode *)trnNode, wipeData);
}

CommandNode *CommandNode_create(Command *cmd, CommandNode *next) {
  return (CommandNode *)ListNode_create(cmd, (ListNode *)next);
}

CommandNode *CommandNode_attatch(CommandNode *curCmd, CommandNode *newCmd) {
  return (CommandNode *)ListNode_attatch((ListNode *)curCmd,
                                         (ListNode *)newCmd);
}

CommandNode *CommandNode_clone(CommandNode *nd) {
  return (CommandNode *)ListNode_clone((ListNode *)nd);
}

// Command List functions

void CommandList_free(CommandList *cmdList, wipeDataFunc wipeData) {
  List_free((List *)cmdList, wipeData);
}

CommandList *CommandList_sortedAdd(CommandList *scondList, CommandNode *cmdNode,
                                   sortFunc sfn, boolean swapData) {
  return (CommandList *)List_sortedAdd((List *)scondList, (ListNode *)cmdNode,
                                       sfn, swapData);
}

/*
CommandList *CommandList_cat(CommandList *list1, CommandList *list2) {
return (CommandList *)List_cat((List *)list1, (List *)list2);
}
*/

CommandNode *CommandList_search(CommandList *cmdList, testFunc tst,
                                void *data) {
  return (CommandNode *)List_search((List *)cmdList, tst, data);
}
CommandNode *CommandList_searchNth(CommandList *cmdList, testFunc tst,
                                   void *data, unsigned short int n) {
  return (CommandNode *)List_searchNth((List *)cmdList, tst, data, n);
}

void CommandList_deepFree(CommandList *cmdList, wipeDataFunc wipeData) {

  if (cmdList->next) {
    CommandList_deepFree(cmdList->next, wipeData);
  }

  if (cmdList->dt->list) {
    CommandList_deepFree(cmdList->dt->list, wipeData);
    cmdList->dt->list = NULL;
  }

  // The printf below stays because it is beautiful.
  // printf("Freeing command of name:\t%s\n", cmdList->dt->name);
  if (wipeData) {
    wipeData(cmdList->dt);
  }

  free(cmdList);
}

void *CommandList_deepRun(CommandList *cmdList, StateMachineList *smcList,
                          char *str) {
  if (!str) {
    return NULL;
  }

  char cmdStr[MAXCMD];
  char *nxt;
  nxt = cp_word(str, cmdStr);

  CommandList *l = CommandList_searchByName(cmdList, cmdStr);

  // If it is not a command list
  // Perform a deep search in list
  if (l) {
    if (l->dt->list) {
      l = CommandList_deepRun(l->dt->list, smcList, nxt);
    } else {
      return Command_exec(l->dt, smcList, nxt);
    }
  }
  return l;
}

/*
CommandList *CommandList_findAndCloneMany(CommandList *list, testFunc test,
sortFunc sort, USint n, void **data) {

return (CommandList *)List_findAndCloneMany((List *)list, test, sort, n,
data);
}
*/
