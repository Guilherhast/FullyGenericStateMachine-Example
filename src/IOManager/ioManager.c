#include "ioManager.h"

static FILE *IFILE = NULL;
static FILE *OFILE = NULL;

void cleanNewLine(char *str, USint *size) {
  if (str[*size - 1] == '\n') {
    str[*size - 1] = '\0';
    (*size)--;
  }
}

void IOManager_setStreams(FILE *in, FILE *out) {
  IFILE = in;
  OFILE = out;
}

FILE *IOManager_getInput() {
  // Bad linter
  return IFILE;
}
FILE *IOManager_getOutput() {
  // Bad linter
  return OFILE;
}

void IOManager_getNext(ioData *data) {
  char *line = NULL;
  size_t n = 0;

  FILE *inputF = IFILE ? IFILE : stdin;

  data->size = getline(&line, &n, inputF);
  data->str = line;

  cleanNewLine(data->str, &data->size);

  return;
}

void IOManager_answer(ioData *data) {
  FILE *outF = OFILE ? OFILE : stdin;
  fprintf(outF, "%s\n", data->str);
}

void IOManager_update(ioData *data) {
  FILE *outF = OFILE ? OFILE : stdin;
  fprintf(outF, "%s\n", data->str);
}

void IOManager_updateAll(ioData *data) { IOManager_update(data); }
