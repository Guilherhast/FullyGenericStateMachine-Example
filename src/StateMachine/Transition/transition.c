
#include "../transition.h"
#include "../state.h"

void Transition_free(void *VTrn) {
  Transition *trn = (Transition *)VTrn;
  free(trn->stateToName);
  free(trn);
}

Transition *Transition_create(State *stateTo, char *stateToName,
                              transitionFunct tFunc, boolean isTrigger,
                              void *data) {

  Transition *t = malloc(sizeof(Transition));

  char *name = malloc(strlen(stateToName));
  strcpy(name, stateToName);

  t->tFunc = tFunc;
  t->stateTo = stateTo;
  t->stateToName = name;

  t->isTrigger = isTrigger;

  t->data = data;

  if (t->isTrigger && t->stateTo) {
    fprintf(stderr, "Error: Trigger transitions should have no stateTo.\n");
    return NULL;
  }
  if (!(t->stateTo || t->tFunc)) {
    fprintf(
        stderr,
        "Error: Transition should have at least a function or a stateTo.\n");
    return NULL;
  }
  // There is a state
  // And the names are different
  if (stateTo && strcmp(stateTo->name, name)) {
    fprintf(stderr,
            "Error: Transition stateToName \"%s\" conflicting with "
            "stateTo->name \"%s\"\n",
            stateTo->name, name);
    return NULL;
  }

  return t;
}
