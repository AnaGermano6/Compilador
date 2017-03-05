#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threeAdress.h"

Adrs mkInt(int v){
  Adrs newp=malloc(sizeof(*newp));
  newp->kind = Int;
  newp->content.val = v;
  return newp;
}

Inst mkVar(char *s){
  Inst newp=mallloc(sizeof(*newp));
  newp->kind = Var;
  strcpy(newp->content.id , s);
  return newp;
}

Inst mkInstr(OpKind op, Adrs ad1, Adrs ad2, Adrs ad3){
  Inst newp= malloc(sizeof(*newp));
  newp->op = op;
  newp->add1 = ad1;
  newp->add2 = ad2;
  newp->add3 = ad3;
  return newp;
}

InstList mkInstList(Inst elem, InstList l1){
	InstList newp = malloc(sizeof(*newp));
	newp->elem = elem;
	newp->tail = l1;
	return newp;
}

InstList newVar(){
	InstList newp= malloc(sizeof(*newp));
	newp -> var=var;
	newp -> next=NULL;
	return newp;
}

InstList append(InstList l1, InstList l2){
	InstList p;
	if(l1==NULL) return l2;
	for(p=l1; p->next!=NULL; p=p->next);
	p->next=l2;
	return l1;
}

Pairs mkPair(char var, InstList code){
	Pairs p=malloc(sizeof(*p));
	p -> var=var;
	p -> code=code;
	return p;
}

Pairs compileExpr(Expr e){
  if(e->kind == E_INTEGER){
    return (mkInt(e->attr.value), NULL);
  }
  else if(e->kind == OpExp){
	switch(e.op.kind){
		case Add:
			Pair p1 = compileExpr(e.attr.op.left);
			Pair p2 = compileExpr(e.attr.op.right);
			InstList l = append(p1->list, p2->list);
			char v = newVar();
			Inst i = mkInstr(Add, v, p1->var, p2->var);
			InstList l1 = append(l, newElem(i));
			return mkPair(v,l1);
		case Sub:
			Pair p1 = compileExpr(e.attr.op.left);
			Pair p2 = compileExpr(e.attr.op.right);
			InstList l = append(p1->list, p2->list);
			char v = newVar();
			Inst i = mkInstr(Sub, v, p1->var, p2->var);
			InstList l1 = append(l, newElem(i));
			return mkPair(v,l1);
		case Mul:
			Pair p1 = compileExpr(e.attr.op.left);
			Pair p2 = compileExpr(e.attr.op.right);
			InstList l = append(p1->list, p2->list);
			char v = newVar();
			Inst i = mkInstr(Mul, v, p1->var, p2->var);
			InstList l1 = append(l, newElem(i));
			return mkPair(v,l1);
		case Div:
			Pair p1 = compileExpr(e.attr.op.left);
			Pair p2 = compileExpr(e.attr.op.right);
			InstList l = append(p1->list, p2->list);
			char v = newVar();
			Inst i = mkInstr(Div, v, p1->var, p2->var);
			InstList l1 = append(l, newElem(i));
			return mkPair(v,l1);
	}
  }
}
