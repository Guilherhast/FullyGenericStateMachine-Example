#ifndef LIST_H
#define LIST_H

#include "../consts.h"

//-1 if a cames before, 0 if they are equal 1 f b cames before
typedef short int (*sortFunc)(void *a, void *b);
typedef boolean (*testFunc)(void *a, void *data);

typedef struct ListNode List;
typedef struct ListNode ListNode;

struct ListNode {
  void *dt;
  struct ListNode *next;
};

/* NODE FUNCTIONS */
void ListNode_swapData(ListNode *a, ListNode *b);
ListNode *ListNode_create(void *stt, ListNode *next);

void ListNode_free(ListNode *node, boolean wipeData);
#define ListNode_freeSafe(n) ListNode_free(n,false)
#define ListNode_freeWipe(n) ListNode_free(n,true)

ListNode *ListNode_attatch(List *current, List *newState);

/* LIST FUNCTIONS */
// Free all nodes of list
void List_free(List *list, boolean wipeData);
#define List_freeSafe(l) List_free(l,false)
#define List_freeWipe(l) List_free(l,true)

// Add new node to list
List *List_sortedAdd(List *list, ListNode *node, sortFunc sort, boolean swap);
#define List_add(l, n) List_sortedAdd(l, n, NULL, false)
ListNode *List_search(List *list, testFunc test, void *data);
ListNode *List_searchNth(List *list, testFunc test, void *data,
                         unsigned short int n);
#endif
