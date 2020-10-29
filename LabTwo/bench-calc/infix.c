#include "infix.h"

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs) {

  struct char_stack* stack = char_stack_new(nargs);
  char** result = malloc(nargs * sizeof(char*));
  int resultindex = 0;

  for(int i = 0; i < nargs; i++)
  {
    if(is_number(args[i]))
    {
      result[resultindex++] = args[i];
    }
    else if(args[i][0] == '(')
    {
      char_stack_push(stack, args[i][0]);
    }
    else if(is_operator(args[i]))
    {
      while(is_higher_precendence(stack->items[stack->top-1], args[i][0]))
      {
        result[resultindex] = malloc(sizeof(char));
        result[resultindex++][0] = char_stack_pop(stack);
      }
      char_stack_push(stack, args[i][0]);
    }
    else if(args[i][0] == ')')
    {
      while(stack->items[stack->top-1] != '(')
      {
        result[resultindex] = malloc(sizeof(char));
        result[resultindex++][0] = char_stack_pop(stack);
      }
      // Pop the left bracket
      char_stack_pop(stack);
    }
  }
  while(stack->top > 0)
  {
    result[resultindex] = malloc(sizeof(char));
    result[resultindex++][0] = char_stack_pop(stack);
  }

  for(int i = 0; i < resultindex; i++)
  {
    printf("%s ", result[i]);
  }
  printf("\n");
  return evaluate_postfix_expression(result, resultindex);
}

int is_number(const char* string)
{
  if(strlen(string) == 1)
  {
    if(string[0] >= '0' && string[0] <= '9')
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

int is_operator(const char* string)
{
  if(string[0] == '^' || string[0] == 'X' || string[0] == '/' || string[0] == '+' || string[0] == '-')
  {
    return 1;
  } 
  return 0;
}

int is_higher_precendence(char firstValue, char secondValue)
{
  if(firstValue == '^' && secondValue == '^')
  {
    return 1;
  }
  if((firstValue == 'X' || firstValue == '/') && (secondValue == 'X' || secondValue == '/'))
  {
    return 1;
  }
  if((firstValue == '+' || firstValue == '-') && (secondValue == '+' || secondValue == '-'))
  {
    return 1;
  }

  // Turns out the order of precendence is the exact same as their ascii ordering
  if(firstValue > secondValue)
  {
    return 1;
  }
  return 0;
}
