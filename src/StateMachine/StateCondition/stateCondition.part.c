#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../stateCondition.h"
#include "../state.h"

StateCondition *StateCondition_create(checkerFunct check, State *sttPtr,
                                      int priority, StateCondition *next) {

  StateCondition *sttCond = malloc(sizeof(StateCondition));

  if (sttCond == NULL) {
    return NULL;
  }

  char *str = NULL;
  // You may forbid it.
  // But in this case the state machine
  // will go back to the first state
  if (sttPtr != NULL) {
    str = malloc(strlen(sttPtr->name) + 1);
    strcpy(str, sttPtr->name);
  }

  sttCond->stateToName = str;
  sttCond->stateToPtr = sttPtr;

  sttCond->check = check;

  sttCond->priority = priority;
  sttCond->next = next;

  return sttCond;
}

void StateCondition_free(StateCondition *sttCond) {
  free(sttCond->stateToName);
  free(sttCond);
}

void StateCondition_listFree(StateCondition *sttCond) {
  StateCondition *next;
  while (sttCond != NULL) {
    next = sttCond->next;
    StateCondition_free(sttCond);
    sttCond = next;
  }
}

StateCondition *StateCondition_attatch(StateCondition *current,
                                       StateCondition *newStateCondition) {
  if (current == NULL) {
    newStateCondition->next = NULL;
    return newStateCondition;
  }

  newStateCondition->next = current->next;
  current->next = newStateCondition;
  return current;
}

StateCondition *StateCondition_listAdd(StateCondition *list,
                                       StateCondition *newStateCondition) {

  // If the list is empty or
  // The first state has a higher priority
  // Return the added condition
  if (list == NULL || list->priority > newStateCondition->priority) {
    // A way around would be exchange values in pointers
    newStateCondition->next = list;
    return newStateCondition;
  }

  StateCondition *cur = list;

  /**
   * If you create a list manager
   * It should receive  a list test option
   * The function will be used here
   * And also in the check for returning the first element
   * */
  // Loop until the end of the list
  while (cur->next) {
    // If the next has a higher priority attach here
    if (cur->next->priority > newStateCondition->priority) {
      break;
    }
    // Test the next member
    cur = cur->next;
  }

  StateCondition_attatch(cur, newStateCondition);

  return list;
}

// Return the next state if one transition is true
char *StateCondition_listCheckForNextState(StateCondition *list,
                                           unsigned long int dt, va_list args) {
  if (!list) {
    return NULL;
  }

  do {
    if (list->check(dt, args)) {
      break;
    }

    // Stop when the list is null
  } while ((list = list->next));

  return list == NULL ? NULL : list->stateToName;
}

State *StateCondition_listCheckForNextStatePtr(StateCondition *list,
                                               unsigned long int dt,
                                               va_list args) {
  if (!list) {
    return NULL;
  }

  do {
    if (list->check(dt, args)) {
      break;
    }

    // Stop when the list is null
  } while ((list = list->next));

  return list == NULL ? NULL : list->stateToPtr;
}
