#include <stdlib.h>
#include "../state.h"

void State_free(State *stt) {
  free(stt->name);
  free(stt);
}
void State_listFree(State *stt) {
  State *next;
  while (stt != NULL) {
    next = stt->next;
    State_free(stt);
    stt = next;
  }
}

State *State_create(char *name, StateCondition *stateConditionList,
                    stateChangeFunc enter, stateUpdateFunc update,
                    stateChangeFunc exit, State *next) {

  State *stt = malloc(sizeof(State));
  char *str = malloc(strlen(name) + 1);
  strcpy(str, name);

  if (stt == NULL)
    return NULL;

  stt->name = str;

  stt->stateConditionList = stateConditionList;

  stt->enter = enter;
  stt->update = update;
  stt->exit = exit;

  stt->next = next;

  return stt;
}

State *State_attatch(State *current, State *newState) {
  if (current == NULL) {
    newState->next = NULL;
    return newState;
  }

  newState->next = current->next;
  current->next = newState;
  return current;
}

State *State_listAdd(State *list, State *newState) {

  // If the list is empty
  // Return the added state
  if (list == NULL) {
    newState->next = list;
    return newState;
  }

  State *cur = list;

  while (cur->next) {
    cur = cur->next;
  }

  State_attatch(cur, newState);

  return list;
}
