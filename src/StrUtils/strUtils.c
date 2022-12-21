#include "strUtils.h"

unsigned int *strToIdList(char *str) {
  if (!str) {
    return NULL;
  }

  unsigned int n = 0;
  unsigned int values[MAXDEVICES];

  char bff[MAXSTR];
  char *nxt = str;

  do {
    nxt = cp_word(nxt, bff);
    values[n] = atoi(bff);
    if (values[n] == 0) {
      // fprintf(stderr, "Error: StateMachine id can't be NULL\n");
      n--;
    }
    n++;
  } while (nxt != NULL && n < MAXDEVICES);

  if (n == 0) {
    return NULL;
  }

  unsigned int *r = malloc(sizeof(USint) + 1);

  r[n] = values[n] = 0;

  while (n--) {
    r[n] = values[n];
  }

  return r;
}

void reverse(char *s) {
  int l = strlen(s) - 1;
  int i = 0;
  char c;

  // I agree with the book.
  //[l - i] takes more processing
  while (i < l) {
    c = s[i];
    s[i] = s[l];
    s[l] = c;

    i++;
    l--;
  }
}

// Taken from TheCProgrammingLanguage
void itoa(int n, char s[]) {
  int i, sign;
  if ((sign = n) < 0)
    n = -n;
  i = 0;
  do {
    s[i++] = n % 10 + '0'; // Add the first digit
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

char *str_toUpper(char *str) {
  while (*str != '\0') {
    *str = toupper(*str);
  }
  return str;
}

// Copy a word from in to out
// Returns a pointer to the next word in in
// Or NULL if there is none
boolean isDivisor(char c) {
  return c == '\n' || c == '\0' || c == '\t' || c == ' ';
}
char *cp_word(char *in, char *out) {
  int n = 0;

  while (!isDivisor(in[++n]))
    ;

  strncpy(out, in, n);
  out[n] = '\0';

  /*
  str_toUpper(out);
  for (int i = 0; i < n; i++) {
  out[i] = toupper(out[i]);
  }
  */

  if (in[n] != '\0') {
    return &in[++n];
  }

  return NULL;
}

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

void *strUtils_wrap(char *desc, char *wrapped) {
  int l = strlen(desc) + strlen(wrapped) + 4;
  char *str = malloc(sizeof(char) * l);
  sprintf(str, "%s:\t%s\n", desc, wrapped);
  return str;
}
