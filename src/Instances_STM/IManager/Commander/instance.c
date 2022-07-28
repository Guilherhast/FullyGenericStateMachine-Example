#include "instance.h"



void *get_devices(StateMachineList *smcList, char *NA) { //
  if (!smcList) {
    return NULL;
  }

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

void *get_info(StateMachineList *smcList, char *str) { //
  if (!smcList) {
    return NULL;
  }

  unsigned int *idList = strToIdList(str);
  unsigned int *idListPtr = idList;

  StateMachineNode *tmp;

  char *r = malloc(sizeof(char) * MAXMSG);
  r[0] = '\0';
  char bff[SIZEBUFFERINFO];

  unsigned int id;
  while (*idList != 0) {
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
