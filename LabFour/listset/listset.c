#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset* result = malloc(sizeof(struct listset));
  result->head = NULL;
  return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  struct listnode* copy = this->head;
  while(copy != NULL)
  {
    if(strcmp(copy->str, item) == 0)
    {
      return 1;
    }
    copy = copy->next;
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
  if(listset_lookup(this, item) == 0)
  {
    struct listnode* newnode = malloc(sizeof(struct listnode));
    newnode->next = this->head;
    newnode->str = item;
    this->head = newnode;
  }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  struct listnode* copy = this->head;
  struct listnode* prev = this->head;
  // Make sure list is not empty
  if(this->head == NULL)
  {
    return;
  }
  // If list is only one node check it
  if(this->head->next == NULL)
  {
    if(strcmp(this->head->str, item) == 0)
    {
      free(this->head);
      this->head = NULL;
    }
    return;
  }
  // If list is > 1 node long
  while(copy != NULL)
  {
    if(strcmp(copy->str, item) == 0)
    {
      // If this is not the last node
      if(copy->next != NULL)
      {
        struct listnode* freecopy = copy->next;
        copy->str = copy->next->str;
        copy->next = copy->next->next;
        free(freecopy);
      }
      else
      {
        free(prev->next);
        prev->next = NULL;
      }
    }
    prev = copy;
    copy = copy->next;
  }
}
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
  struct listnode* output = dest->head;
  struct listnode* copysrc1 = src1->head;
  struct listnode* copysrc2 = src2->head;
  while(copysrc1 != NULL)
  {
    output = copysrc1;
    output = output->next;
    copysrc1 = copysrc1->next;
  }
  while(copysrc2 != NULL)
  {
    output = copysrc2;
    output = output->next;
    copysrc2 = copysrc2->next;
  }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
  struct listnode* output = dest->head;
  struct listnode* copysrc1 = src1->head;
  while(copysrc1 != NULL)
  {
    if(listset_lookup(src2, copysrc1->str))
    {
      output = copysrc1;
      output = output->next;
    }
    copysrc1 = copysrc1->next;
  }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
  int count = 0;
  struct listnode* copy = this->head;
  while(copy != NULL)
  {
    copy = copy->next;
    count++;
  }
  return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s ", p->str);
  }
  printf("\n");
}
