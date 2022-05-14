#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// State Node functions
ListNode *ListNode_create(void *dt, ListNode *next) {
  ListNode *node = malloc(sizeof(ListNode));
  if (!node) {
    fprintf(stderr, "Error: ListNode: Could not alloc space");
    return NULL;
  }

  node->dt = dt;
  node->next = next;

  return node;
}
void ListNode_free(ListNode *node, wipeDataFunc wipeData) {
  if (wipeData) {
    wipeData(node->dt);
  }
  free(node);
}
void ListNode_swapData(ListNode *a, ListNode *b) {
  void *tmp = a->dt;
  a->dt = b->dt;
  b->dt = tmp;
}

ListNode *ListNode_attatch(ListNode *cur, ListNode *new) {
  // Is it the best way.
  // You could throw an error
  if (cur == NULL) {
    new->next = NULL;
    return new;
  }

  // Who is behind you?
  // Now he is behind me
  new->next = cur->next;
  // And I am behind you
  cur->next = new;
  return cur;
}

ListNode *ListNode_clone(ListNode *node) {
  if (!node) {
    return NULL;
  }
  ListNode *newNode = malloc(sizeof(ListNode));
  newNode->dt = node->dt;
  newNode->next = NULL;
  return newNode;
}

// List functions
void List_free(List *list, wipeDataFunc wipeData) {
  List *next;
  while (list != NULL) {
    next = list->next;
    ListNode_free(list, wipeData);
    list = next;
  }
}

List *List_sortedAdd(List *list, ListNode *node, sortFunc sort,
                     boolean swapData) {
  // If the list is empty
  // Return the added state
  if (!node) {
    return list;
  }
  if (list == NULL) {
    node->next = NULL;
    return node;
  } else {
    if (sort && sort(list->dt, node->dt) > 0) {
      // The new node comes before the first
      if (swapData) {
        // Swap data and add the node with old data in the end
        ListNode_swapData(list, node);
        return ListNode_attatch(list, node);
      } else {
        // Add the list after the node
        return ListNode_attatch(node, list);
      }
    }
  }

  ListNode *cur = list;
  while (cur->next) {
    if (sort && sort(cur->next->dt, node->dt) > 0) {
      break;
    }
    cur = cur->next;
  }

  ListNode_attatch(cur, node);

  // Return the original value
  return list;
}

List *List_cat(List *list1, List *list2) {
  if (!list1) {
    return list2;
  }
  List *cur = list1;
  while (cur->next) {
    cur = cur->next;
  }
  cur->next = list2;
  return list1;
}

List *List_merge(List *list1, List *list2, sortFunc sort) {
  if (!list2) {
    return list1;
  }
  if (!list1) {
    return list2;
  }

  List *first, *att;

  if (sort && sort(list1->dt, list2->dt) > 0) {
    first = list2;
    att = list1;
  } else {
    first = list1;
    att = list2;
  }

  List *cur = first, *tmp = NULL;
  while (cur->next && att) {
    if (sort && sort(cur->next->dt, att->dt) > 0) {
      tmp = att->next;
      ListNode_attatch(cur, att);
      att = tmp;
    }
    cur = cur->next;
  }
  cur->next = att;

  return first;
}

ListNode *List_search(List *list, testFunc test, void *data) {
  ListNode *cur = list;
  while (cur) {
    if (test(cur->dt, data)) {
      break;
    }
    cur = cur->next;
  }
  // If cur is NULL or the loop does not find
  return cur;
}
// After a long time I realized that the above function is a macro for this
ListNode *List_searchNth(List *list, testFunc test, void *data,
                         unsigned short int n) {
  ListNode *result = list;
  // Stop when:
  // Result not found
  // searched n times
  // Result has no next
  do {
    result = List_search(result, test, data);
  } while (result && --n && (result = result->next));
  return result;
}

// I'm not afraid of Segmentation fault
List *List_findAndCloneMany(List *list, testFunc test, sortFunc sort, USint n,
                            void **data) {
  if (!(list && test && n && data)) {
    fprintf(stderr,
            "Error: List_findAndCloneMany: Can't receive NULL parameters.");
    return NULL;
  }

  List *cl = NULL;
  ListNode *tmp = NULL;
  while (n--) {
    tmp = List_findAndClone(list, test, *(data++));
    cl = List_sortedAdd(cl, tmp, sort, false);
  }

  return cl;
}
