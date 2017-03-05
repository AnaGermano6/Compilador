// Tokens
%token
  PLUS
  MINUS
  MUL
  DIV
  OPEN_P
  CLOSE_P
  NOT_IGUAL
  IGUAL
  IGUAL_IGUAL
  MENOR
  MENOR_IGUAL
  C_AND
  AND
  C_OR
  OR
  IF
  ELSEIF
  THEN
  ELSE
  FOR
  WHILE
  END
  DISP
  TRUE
  FALSE
  NUM INT
  ID  VAR
  NUM_REAL REAL


// Operator associativity & precedence
%right IGUAL
%left MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL IGUAL_IGUAL NOT_IGUAL
%left ADD SUB
%left MUL DIV

%token C_OR
%token C_AND
%token OR
%token AND
%token OPEN_P CLOSE_P

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  Cmd T_cmd;
  char* T_id;
}

%type <intValue> NUM
%type <exprValue> expr
%type <T_cmd> handler
%type <T_cmd> command
%type <T_id> ID

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "abssyn.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
}

%%
program: expr { root = $1; }

expr:
  expr PLUS expr          {$$ = ast_operation(PLUS, $1, $3);}
  | expr MINUS expr       {$$ = ast_operation(MINUS, $1, $3);}
  | expr MUL expr         {$$ = ast_operation(TIMES, $1, $3);}
  | expr DIV expr         {$$ = ast_operation(DIV, $1, $3);}
  | expr MENOR_IGUAL expr {$$ = ast_operation(MENOR_IGUAL, $1, $3);}
  | expr MENOR expr       {$$ = ast_operation(MENOR, $1, $3);}
  | expr MAIOR_IGUAL expr {$$ = ast_operation(MAIOR_IGUAL, $1, $3);}
  | expr MAIOR expr       {$$ = ast_operation(MAIOR, $1, $3);}
  | expr IGUAL_IGUAL expr {$$ = ast_operation(IGUAL_IGUAL, $1, $3);}
  | expr NOT_IGUAL expr   {$$ = ast_operation(NOT_IGUAL, $1, $3);}
  | ID                    {$$ = mkvar($1);}
  | NUM                   {$$ = ast_integer($1);}
  ;

command:
  IF expr command END                 {$$ = mkif($2, $3);} //if1
  | IF expr command ELSE command END  {$$ = mkifelse($2, $3, $5);} //if2
  | IF expr handler ELSE command END  {$$ = mkifelseifelse($2, $3, $5);}    //if3
  | WHILE expr command                {$$ = mkwhile($2, $3);}
  | FOR expr':'expr command           {$$ = mkfor($2, $4, $5);}
  | INPUT'('')'                       {$$ = mkinput();}
  | DISP'('expr')'                    {$$ = dispfunc($3);}
  | ID IGUAL expr                     {$1 = $3;}
  ;

handler:
  ELSEIF expr command handler     {mkelseif1($2, $3, $4);}
  | ELSEIF expr command           {mkelseif2($2, $3);}
  ;

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
