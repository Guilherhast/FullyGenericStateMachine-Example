#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <stdio.h>
#include <stdlib.h>

#include "../consts.h"

#define MAXLINE 256

typedef USint IOID;
typedef struct ioData ioData;

struct ioData {
  IOID id;
  USint size;
  char *str;
};

void IOManager_getNext(ioData *data);

#define IOManager_getNextAlloc()                                               \
  ({                                                                           \
    ioData *lcl_ioData = (ioData *)malloc(sizeof(ioData));                     \
    IOManager_getNext(lcl_ioData);                                             \
    lcl_ioData;                                                                \
  })

void IOManager_answer(ioData *data);
void IOManager_update(ioData *data);
void IOManager_updateAll(ioData *data);

void IOManager_setStreams(FILE *in, FILE *out);
FILE *IOManager_getInput();
FILE *IOManager_getOutput();

#endif
