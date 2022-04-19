#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// State Node functions
ListNode *ListNode_create(void *dt, ListNode *next) {
  ListNode *node = malloc(sizeof(ListNode));

  node->dt = dt;
  node->next = next;

  return node;
}
void ListNode_free(ListNode *node, boolean wipeData) {
  if (wipeData) {
    free(node->dt);
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

// List functions
void List_free(List *list, boolean wipeData) {
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
  if (list == NULL) {
    node->next = NULL;
    return node;
  } else {
    if (sort && sort(list, node) > 0) {
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
    if (sort && sort(cur->next, node) > 0) {
      break;
    }
    cur = cur->next;
  }

  ListNode_attatch(cur, node);

  // Return the original value
  return list;
}

ListNode *List_search(List *list, testFunc test, void *data) {
  ListNode *cur = list;
  while (cur) {
    if (test(cur->dt, data)) {
      return cur;
    }
    cur = cur->next;
  }
  // If cur is NULL or the loop does not find
  return cur;
}
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
