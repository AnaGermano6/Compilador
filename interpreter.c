#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abssyn.h"

int eval(Expr node) {
  int result = 0;
  if (node == 0) {
    yyerror("Null expression!!");
  }
  else if (node->kind == E_INTEGER) {
    result = node->attr.value; 
  } 
  else if (node->kind == E_OPERATION) {
    int vLeft = eval(node->attr.op.left);
    int vRight = eval(node->attr.op.right);
    switch (node->attr.op.operator) {
      case Add: 
        result = vLeft + vRight; 
        printf("%d = %d + %d", result, vLeft, vRight);
        break;
      case Sub: 
        result = vLeft - vRight; 
        printf("%d = %d - %d", result, vLeft, vRight);
        break;
      case Mul: 
        result = vLeft * vRight; 
        printf("%d = %d * %d", result, vLeft, vRight);
        break;
      case Div:
		result = vLeft / vRight;
		printf("%d = %d / %d", result, vLeft, vRight);
		break;
      
      default: yyerror("Unknown operator!");
    }
  }
  return result;
}
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } // yyin = stdin
  if (yyparse() == 0) {
      printf("Result = %d\n", eval(root));
  }
  return 0;


}
