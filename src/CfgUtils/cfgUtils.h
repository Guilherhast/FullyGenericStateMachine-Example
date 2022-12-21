#ifndef CFGUTILS_H
#define CFGUTILS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXCFGLINE 64
#define VALUESIZE 5
#define MAXCFGPROP MAXCFGLINE - VALUESIZE

char *searchProp(char *search, FILE *file);

#endif
