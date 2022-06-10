#ifndef TESTUTILS
#define TESTUTILS

#include "../Lists/list.h"
#include <check.h>

typedef boolean (*uTestFunc)(void *data);

void ck_assert_list_sizeWithFunc(List *list, int size, uTestFunc test);

#define ck_assert_list_size(l, s) ck_assert_list_sizeWithFunc(l, s, NULL)

#endif
