#include "cfgUtils.h"

// Search `search` int the file pointer file
// from the current position to the end of the file
// Use rewind to search from start
char *searchProp(char *search, FILE *file) {
  size_t size = MAXCFGLINE;
  char prop[MAXCFGPROP];

  char *bff = malloc(sizeof(char) * MAXCFGLINE);

  char *value = malloc(sizeof(char) * VALUESIZE);

  short int chars_read;

  while ((chars_read = getline(&bff, &size, file))) {
    if (chars_read <= 0) {
      free(bff);
      return NULL;
    }
    sscanf(bff, "%[^=]=%s", prop, value);
    if (!strcmp(search, prop)) {
      free(bff);
      return value;
    }
  }
  free(bff);
  return NULL;
}
