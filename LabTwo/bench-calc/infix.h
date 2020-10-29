#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "postfix.h"

double evaluate_infix_expression(char ** expr, int nterms);

int is_number(const char* string);

int is_operator(const char* string);

int is_higher_precendence(char firstValue, char secondValue);

#endif
