#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../consts.h"

#define MAXLINE 256

typedef USint IOID;
typedef struct ioData ioData;

struct ioData {
  IOID id;
  USint size;
  char *str;
};

char *IOManager_getNext();

#define IOManager_getNextAlloc()                                               \
  ({                                                                           \
    ioData *lcl_ioData = (ioData *)malloc(sizeof(ioData));                     \
    IOManager_getNext(lcl_ioData);                                             \
    lcl_ioData;                                                                \
  })

#define IOManager_genData() malloc(sizeof(ioData));

void IOManager_answer(ioData *data);
void IOManager_update(ioData *data, char* str);
void IOManager_updateCur(char *str);
void IOManager_updateAll(char *data);

char *IOManager_extractStr(ioData *data);

void IOManager_checkForNew();
int ioManager_nextReady();

char *ioManager_readIO(int inDesc);

void IOManager_setStreams(FILE *in, FILE *out);
FILE *IOManager_getInput();
FILE *IOManager_getOutput();

#endif
