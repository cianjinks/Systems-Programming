#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct double_stack {
  double* items;
  int max_size;
  int top;
};

// prototypes of functions that operate on the double stack
// create a new empty stack
struct double_stack* double_stack_new(int max_size);

// push a value onto the stack
void double_stack_push(struct double_stack* this, double value);

// pop a value from the stack
double double_stack_pop(struct double_stack* this);

// Char stack for conversion to reverse polish notation in infix
struct char_stack {
  char* items;
  int max_size;
  int top;
};

struct char_stack* char_stack_new(int max_size);
void char_stack_push(struct char_stack* this, char value);
char char_stack_pop(struct char_stack* this);

#endif
