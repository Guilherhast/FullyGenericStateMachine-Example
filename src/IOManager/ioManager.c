/*
 * This file will manage all IO from the software
 * A state machine needs to receive data from
 * interfaces and devices.
 *
 * One interface will register itself in the ioManager.
 * It will receive data from updates ( maybe
 * applying filters).
 *
 * One device will also register itself here with
 * different filters. This way the IOManager may
 * decide how to send data. The corresponding
 * ioData object may be added to the State Machine
 * so it can send data propperly when an action is
 * triggered.
 *
 * The registration proccess should take care of
 * reassosiating disconnected devices from it's
 * StateMachines.
 *
 *
 */

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

void IOManager_checkForNew() {}

char *IOManager_getNext() {
  IOManager_checkForNew();

  char *line = NULL;
  USint size = 0;
  size_t n = 0;

  FILE *inputF = IFILE ? IFILE : stdin;

  // It won't work for a raw terminal
  size = getline(&line, &n, inputF);

  if (line && size) {
    cleanNewLine(line, &size);
  }

  USint newSize = strlen(line);

  if (newSize == size) {
    return line;
  } else {
    return NULL;
  }
}

char *IOManager_extractStr(ioData *data) { return data->str; }

/*
void IOManager_answer(ioData *data) {
FILE *outF = OFILE ? OFILE : stdin;
fprintf(outF, "%s\n", data->str);
}
*/

void IOManager_update(ioData *data, char *str) {
  if (!str) {
    return;
  }

  FILE *outFile = OFILE ? OFILE : stdout;
  fprintf(outFile, "%s\n", str);
}

void IOManager_updateCur(char *str) { IOManager_update(NULL, str); }

void IOManager_updateAll(char *str) { IOManager_updateCur(str); }
