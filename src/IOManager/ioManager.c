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

char buffer[MAXLINE];

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

// Check for new io trying to connect
void IOManager_checkForNew() {}

// In a more complex ioManager
// This function will be a key
// It will look at the data structure
// And get the next io descriptor to
// feed the readIO functions
int ioManager_nextReady() {
  // Defining 0 wait time
  struct timeval timeout;
  timeout.tv_sec = timeout.tv_usec = 0;

  // File for testing
  int inDescrp = fileno(IFILE ? IFILE : stdin);

  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(inDescrp, &readfds);

  USint nfds = inDescrp + 1;

  if (select(nfds, &readfds, NULL, NULL, &timeout) > 0) {
    return inDescrp;
  }

  return -1;
}

char *ioManager_readIO(int inDesc) {
  char buffer[MAXLINE];
  short int n = read(inDesc, buffer, MAXLINE);

  if (n != -1) {
    if (buffer[n - 1] == '\n') {
      buffer[n - 1] = '\0';
      char *ans = malloc(sizeof(char) * n);
      strcpy(ans, buffer);
      return ans;
    }
    // else
    // in a complex data it should keep data in buffer
  }
  //
  return NULL;
}

// Would be a better pattern to alloc outside
// Also for the state machine buffers
char *IOManager_getNext() {
  IOManager_checkForNew();
  int des = ioManager_nextReady();
  return ioManager_readIO(des);
}

char *IOManager_extractStr(ioData *data) { return data->str; }

void IOManager_update(ioData *data, char *str) {
  if (!(str && str[0])) {
    return;
  }
  char *time = strUtils_getTimeStamp();

  FILE *outFile = OFILE ? OFILE : stdout;
  fprintf(outFile, "[ %s ]\n%s", time, str);
  free(time);
}

void IOManager_updateCur(char *str) { IOManager_update(NULL, str); }

void IOManager_updateAll(char *str) { IOManager_updateCur(str); }
