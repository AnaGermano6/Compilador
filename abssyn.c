#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abssyn.h"

/* inteiros */
Expr ast_integer (int v) {
  Expr node =malloc(sizeof(*node));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}


/* operadores */
Expr ast_operation(int operator, Expr left, Expr right) {
  Expr node= malloc(sizeof(*node));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

/* booleanos */
Expr mkbool (int val){
	Expr node= malloc(sizeof(*node));
	node -> kind=  E_BOOL;
	node -> attr.bool.val=val;
	return node;
}

Expr ast_logical(Expr left, Op operator, Expr right){
    Expr node = malloc(sizeof(*node));
    node->kind = E_LOGICAL;
    node->attr.log.left = left;
    node->attr.log.opr = operator;
    node->attr.log.right = right;
    return node;
}

/*variveis*/
Expr mkvar (Expr val){
	Expr node= malloc(sizeof(*node));
	node -> kind=E_VAR;
	node -> attr.var.val=val;
	return node;
}

CmdList ast_command(command cmd, CmdList tail){
	CmdList node = malloc(sizeof(*node));
	node->kind = C_CMD;
	node->head.cmd = cmd;
	node->next = tail;
	return node;
}

/*if1*/
command mkif(Expr test, command success){
	command node =malloc(sizeof(*node));
	node -> kind = C_IFF;
	node -> attr.iff.test=test;
	node -> attr.iff.success=success;
	return node;
}


/* if2  */
command mkifelse(Expr test, command success, command fail){
	command node =malloc(sizeof(*node));
	node -> kind = C_IFFE;
	node -> attr.iffe.test=test;
	node -> attr.iffe.success=success;
	node -> attr.iffe.fail=fail;
	return node;
}

/* if elseif else   if3*/
command mkifelseifelse(Expr test, handler elseif, command elsee){
	command node = malloc(sizeof(*node));
	node -> kind = C_IFFEF;
	node -> attr.iffef.test=test;
	node -> attr.iffef.elseif=elseif;
	node -> attr.iffef.elsee=elsee;
	return node;
}

handler mkelseif1(Expr test, command success, handler another){
  handler node = malloc(sizeof(*node));
  node -> kind = H_ELSEIF1;
  node -> attr.elseif1.test=test;
  node -> attr.elseif1.success=success;
  node -> attr.elseif1.another=another;
  return node;
}

handler mkelseif2(Expr test, command success){
  handler node = malloc(sizeof(*node));
  node -> kind = H_ELSEIF2;
  node -> attr.elseif2.test=test;
  node -> attr.elseif2.success=success;
  return node;
}

/* while */
command mkwhile(Expr test, command body){
	command node = malloc(sizeof(*node));
	node -> kind = C_WHILEE;
	node -> attr.whilee.test=test;
	node -> attr.whilee.body=body;
	return node;
}

/* for */
command mkfor(Expr var,Expr first, Expr second, command body) {
	command node = malloc(sizeof(*node));
	node -> kind = C_FOR;
	node -> attr.forr.var=var;
	node -> attr.forr.first=first;
	node -> attr.forr.second=second;
	node -> attr.forr.body=body;
	return node;
}

/* end? */
Expr mkend (Expr pos){
	Expr node = malloc(sizeof(*node));
	node -> kind = E_END;
	node -> attr.ende.pos=pos;
	return node;
}

/* disp */
command dispfunc(Expr test){
	command node = malloc(sizeof(*node));
	node -> kind=C_DISP;
	node-> attr.dispp.test=test;
	return node;
}

/* input */
command mkinput(){
	command node = malloc(sizeof(*node));
	node-> kind=C_INPUT;
	return node;
}
