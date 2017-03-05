#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "abssyn.h"

typedef enum {atrib, add, sub, mul, div} OpKind;
typedef struct _Address *Adrs;
typedef struct Instr *Inst;
typedef struct InstrList *InstList;
typedef struct Pair *Pairs;

struct _Address{
  enum{Empty, Int, Var} AddrKind;
  union{
    int val; // mkInt
    char *id;//mkVar
  }content;
};

struct Instr{
  OpKind op; //mkInstr
  Adrs add1, add2, add3;
};

struct InstrList{
  Inst elem;
  InstList tail;
};

struct Pair{
	Adrs *var;
	InstList code;
};

// Constructor functions 
Adrs mkInt(int);
Inst mkVar(char);
Inst mkInstr(OpKind, Adrs, Adrs, Adrs);
InstList newElem(Inst);
InstList append(InstList, InstList);
Pairs mkPair(char, InstList);
Pairs compileExpr(Expr);
InstList mkInstList(Inst, InstList);

#endif
