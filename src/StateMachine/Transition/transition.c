#include <stdio.h>
#include <stdlib.h>

#include "../transition.h"

void Transition_free(Transition *trn){
	free(trn);
}

Transition *Transition_create(State *stateTo, transitionFunct tFunc,
                              void *data, boolean temporary) {
  Transition *t = malloc(sizeof(Transition));

  t->tFunc = tFunc;
  t->stateTo = stateTo;

  t->data = data;
  t->temporary = temporary;

  if (!(t->stateTo || t->tFunc)) {
    fprintf(stderr, "Error: Transition should have at least a function or a stateTo.");
  }

  return t;
}
