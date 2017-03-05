// AST definitions
#ifndef __ast_h__
#define __ast_h__
#define T_FALSE 0
#define T_TRUE 1

typedef struct _Expr *Expr;
typedef struct _command *command;
typedef struct _handler *handler;
typedef struct _CmdList *CmdList;
typedef enum{Add, Sub, Mul, Div} Op;
typedef enum{If, Elseif, Else, For, While} Cmds;
typedef enum {T_FALSE, T_TRUE} bools;


// AST for expressions
struct _Expr {
  enum {
    E_INTEGER,
    E_OPERATION,
    E_BOOL,
    E_LOGICAL,
    E_VAR,
    E_END
  } kind;
  union {
    int value; // for integer values
    struct { Expr left;  int operator; Expr right;} op; 
    struct { int val;} bool;
    struct { Expr val;} var;
    struct { Expr pos;} ende;
    struct { Expr left; Op opr; Expr right;} log;
  } attr;
};

struct _command {
	enum {
	    C_IFF,
	    C_IFFE,
	    C_IFFEF,
    	C_WHILEE,
    	C_FOR,
    	C_DISP,
    	C_INPUT
	} kind;
	union {
		struct { Expr test;} dispp;
	    struct { Expr in;} inp;
	    struct { Expr test; command success;} iff;
	    struct { Expr test; command success; command fail;} iffe;
	    struct { Expr test; handler elseif; command elsee;} iffef;
	    struct { Expr test; command body;} whilee;
	    struct { Expr var; Expr first; Expr second; Expr body;} forr;
	} attr;

};

struct _handler {
	enum {
		H_ELSEIF1,
		H_ELSEIF2
	} kind;

	union{
		struct { Expr test; command success; handler another; } elseif1;
		struct { Expr test; command success; } elseif2;
	} attr;
};

struct _CmdList{
	enum{
		C_CMD
	}kind;
	union{
		command cmd;
	}head;
	 CmdList next;
};


// Constructor functions (see implementation in ast.c)
Expr ast_integer(int );
Expr ast_operation(int, Expr, Expr);
Expr mkbool(int);
Expr mkvar(Expr);
Expr ast_logical(Expr, Op, Expr);
command mkif(Expr, command);
command mkifelse(Expr, command, command);
command mkifelseifelse(Expr, handler, command);
handler mkelseif1(Expr, command, handler);
handler mkelseif2(Expr, command);
command mkwhile(Expr, command);
command mkfor(Expr, Expr, Expr, command);
Expr mkend (Expr);
command dispfunc(Expr);
command mkinput();
CmdList ast_command(command, CmdList);

#endif
