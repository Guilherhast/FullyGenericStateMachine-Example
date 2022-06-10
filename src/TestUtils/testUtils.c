#include "./testUtils.h"
#include <stdio.h>

void ck_assert_list_sizeWithFunc(List *list, int size, uTestFunc test) {
  if (list == NULL) {
    ck_assert_int_eq(size, 0);
    return;
  }

  int count = 0;
  List *cur = list;
  do {
    if (test) {
      if (test(cur->dt)) {
        ++count;
      }
    } else {
      ++count;
    }
  } while ((cur = cur->next));

  ck_assert_int_eq(size, count);
}
