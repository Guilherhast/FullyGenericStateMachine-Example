#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../state.h"
#include "../stateCondition.h"

/*
 * STATECONDITION FUNCTIONS
 */
void StateCondition_free(void *vSttCond) {
  StateCondition *sttCond = (StateCondition *)vSttCond;
  // Free the name string but not the state.
  free(sttCond->stateToName);
  free(sttCond);
}

StateCondition *StateCondition_create(checkerFunct check, State *sttPtr,
                                      int priority) {

  StateCondition *sttCond = malloc(sizeof(StateCondition));
  char *str = malloc(strlen(sttPtr->name) + 1);

  // Should have a stateTo and run for all data
  if (!sttPtr) {
    fprintf(stderr, "Error: State condition should point to a state.");
    return NULL;
  }
  if (!check) {
    fprintf(stderr,
            "Error: State condition should have a valide chekc function.");
    return NULL;
  }
  if (!(sttCond && str)) {
    fprintf(stderr, "Error: StateCondition: Could not alloc space");
    return NULL;
  }

  // Is it needed?
  // You may use the original data
  strcpy(str, sttPtr->name);

  sttCond->stateToName = str;
  sttCond->stateToPtr = sttPtr;

  sttCond->check = check;

  sttCond->priority = priority;

  return sttCond;
}

boolean StateCondition_check(void *vSttCond, void *data) {
  StateCondition *sttCond = (StateCondition *)vSttCond;
  return sttCond->check(data); // Considerating a valid sttCond
}

short int priorityComparator(void *vSCond1, void *vSCond2) {
  StateCondition *scond1 = (StateCondition *)vSCond1,
                 *scond2 = (StateCondition *)vSCond2;
  return scond1->priority - scond2->priority;
}
