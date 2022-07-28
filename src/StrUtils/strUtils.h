#ifndef STRUTILS_H
#define STRUTILS_H


#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../consts.h"

#define MAXSTR 256
#define MAXDEVICES 64

void reverse(char *s);
void itoa(int n, char s[]);
void *str2ptr(char *msg);
void *trn_str2ptr(char *msg);
void *stt_str2ptr(char *msg, void *data);

boolean isDivisor(char c);

unsigned int *strToIdList(char *str);

char *str_toUpper(char *str);
char *cp_word(char *in, char *out);
#define cp_wordUpper(i,o) str_toUpper(cp_word(i,o))

#endif
