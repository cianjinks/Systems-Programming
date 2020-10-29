#include "stack.h"

struct double_stack* double_stack_new(int max_size) 
{
    struct double_stack* result = malloc(sizeof(struct double_stack));
    result->items = malloc(max_size * sizeof(double));
    result->max_size = max_size;
    result->top = 0;
    return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack* this, double value) 
{
    assert(this->top < this->max_size);
    this->items[this->top] = value;
    this->top++;
}

// pop a value from the stack
double double_stack_pop(struct double_stack* this) 
{
    assert(this->top > 0);
    this->top--;
    return this->items[this->top];
}

struct char_stack* char_stack_new(int max_size)
{
    struct char_stack* result = malloc(sizeof(struct char_stack));
    result->items = malloc(max_size * sizeof(char));
    result->max_size = max_size;
    result->top = 0;
    return result;
}

void char_stack_push(struct char_stack* this, char value)
{
    assert(this->top < this->max_size);
    this->items[this->top] = value;
    this->top++;
}

char char_stack_pop(struct char_stack* this)
{
    assert(this->top > 0);
    this->top--;
    return this->items[this->top];
}
