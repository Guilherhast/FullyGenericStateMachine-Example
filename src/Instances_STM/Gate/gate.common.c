#include <stdlib.h>
#include <string.h>

void *str2ptr(char *msg) {
  int size = strlen(msg);
  char *tmp = malloc(sizeof(char) * ++size);
  strcpy(tmp, msg);
  return tmp;
}

void *trn_str2ptr(char *msg) {
  //
  return str2ptr(msg);
}

void *stt_str2ptr(char *msg, void *data) {
  //
  return str2ptr(msg);
}
