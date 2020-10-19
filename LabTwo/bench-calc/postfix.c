#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {

  struct double_stack* stack = double_stack_new(nargs);

  for(int i = 0; i < nargs; i++)
  {
    // Check if it is a signed number
    if((args[i][0] == '+' || args[i][0] == '-') && args[i][1] != '\0')
    {
      if(args[i][1] >= '0' && args[i][1] <= '9')
      {
        double_stack_push(stack, atof(args[i]));
      }
    }
    else if(args[i][0] >= '0' && args[i][0] <= '9')
    {
      double_stack_push(stack, atof(args[i]));
    }
    // Check which symbol it is otherwise
    else
    {
      switch(args[i][0])
      {
        case '+':
        {
          double firstElement = double_stack_pop(stack);
          double secondElement = double_stack_pop(stack);
          double result = firstElement + secondElement;
          double_stack_push(stack, result);
          break;
        }
        case '-':
        {
          double firstElement = double_stack_pop(stack);
          double secondElement = double_stack_pop(stack);
          double result = firstElement - secondElement;
          double_stack_push(stack, result);
          break;
        }
        case 'X':
        {
          double firstElement = double_stack_pop(stack);
          double secondElement = double_stack_pop(stack);
          double result = firstElement * secondElement;
          double_stack_push(stack, result);
          break;
        }
        case '/':
        {
          double firstElement = double_stack_pop(stack);
          double secondElement = double_stack_pop(stack);
          double result = firstElement / secondElement;
          double_stack_push(stack, result);
          break;
        }
        case '^':
        {
          double firstElement = double_stack_pop(stack);
          double secondElement = double_stack_pop(stack);
          // May be wrong due to order pushed
          double result = pow(firstElement, secondElement);
          double_stack_push(stack, result);
          break;
        }
        default: { printf("Invalid input entered"); break; }
      }
    }
  }
  return double_stack_pop(stack);
}
