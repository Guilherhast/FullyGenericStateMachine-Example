#ifndef COMMANDER_H
#define COMMANDER_H

#include <stdio.h>
#include <stdlib.h>

#include "../StateMachine/Body/stateMachine.h"
#include "../StrUtils/strUtils.h"
#include "../consts.h"

#define SIZEBUFFERID 32
#define SIZEBUFFERINFO 64
#define MAXCMD 64
#define MAXMSG 2048

typedef void *(*cmdrFunc)(void *list, char *str);

typedef struct Command Command;
typedef struct CommandNode CommandNode;
typedef struct CommandNode CommandList;

struct Command {
  char *name;
  cmdrFunc func;
  CommandList *list;
};

struct CommandNode {
  Command *dt;
  CommandNode *next;
};

// Commander functions
void Command_free(void *cmd);
Command *Command_create(char *name, cmdrFunc func, CommandList *list);
void *Command_exec(Command *cmd, List *list, char *str);

boolean Command_nameEqual(void *vCmd, void *vName2);

/*
 * Commander Node FUNCTIONS
 */

void CommandNode_free(CommandNode *cmdNode, wipeDataFunc wipeData);

#define CommandNode_freeSafe(s) CommandNode_free(s, NULL)
#define CommandNode_freeWipe(s) CommandNode_free(s, &Command_free)

CommandNode *CommandNode_create(Command *cmd, CommandNode *next);

#define CommandNode_createFull(nm, f, l, nxt)                                  \
  CommandNode_create(Command_create(nm, f, l), nxt)

#define CommandNode_createFullFork(nm, l, nxt)                                 \
  CommandNode_create(Command_create(nm, NULL, l), nxt)

#define CommandNode_createFullFunc(nm, f, nxt)                                 \
  CommandNode_create(Command_create(nm, f, NULL), nxt)

CommandNode *CommandNode_attatch(CommandNode *curcmd, CommandNode *newcmd);

// CommandNode *CommandNode_clone(CommandNode *nd);

/*
#define CommandList_findAndClone(l, t, d)                                      \
CommandNode_clone(CommandList_search(l, t, d))
*/

/*
 * Commander List FUNCTIONS
 */

void CommandList_free(CommandList *cmdList, wipeDataFunc wipeData);
#define CommandList_freeSafe(s) CommandList_free(s, NULL)
#define CommandList_freeWipe(s) CommandList_free(s, &Command_free)

void CommandList_deepFree(CommandList *cmdList, wipeDataFunc wipeData);
#define CommandList_deepFreeSafe(s) CommandList_deepFree(s, NULL)
#define CommandList_deepFreeWipe(s) CommandList_deepFree(s, &Command_free)

CommandList *CommandList_sortedAdd(CommandList *cmdList, CommandNode *cmdNode,
                                   sortFunc sfn, boolean swapData);
#define CommandList_add(t, n) CommandList_sortedAdd(t, n, NULL, false)

// CommandList *CommandList_cat(CommandList *list1, CommandList *list2);

CommandNode *CommandList_search(CommandList *cmdList, testFunc tst, void *data);

#define CommandList_searchByName(t, d)                                         \
  CommandList_search(t, &Command_nameEqual, d)

CommandNode *CommandList_searchNth(CommandList *cmdList, testFunc tst,
                                   void *data, unsigned short int n);

void *CommandList_deepRun(CommandList *cmdList, List *list, char *str);
/*
void *CommandList_deepRun(CommandList *cmdList, testFunc tst, void *data);
#define CommandList_deepRunByName(t, d)                                     \
CommandList_deepRun(t, &Command_nameEqual, d)
*/

/*
 * Search functions
 */
boolean Command_nameEqual(void *vCmd, void *vName);

#endif
