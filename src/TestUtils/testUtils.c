#include "./testUtils.h"

void ck_assert_list_size(List *list, int size) {
  if (list == NULL) {
    ck_assert_int_eq(size, 0);
    return;
  }

  int count = 1;
  List *cur = list;
  while (cur->next) {
    ++count;
    cur = cur->next;
  }

  ck_assert_int_eq(size, count);
}
