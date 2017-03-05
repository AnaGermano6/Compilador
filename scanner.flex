%option noyywrap

%{

#include <stdio.h>
#include <stdlib.h>
#include "parser.h" /* tokens */
#include "abssyn.h"

%}

true		"1"
false		"0"

add 				"+"
sub 				"-"
div 	  	        "/"
mul 				"*"
menor				"<"
menor_igual         "<="
maior				">"
maior_igual         ">="
igual_igual     	"=="
igual				"="
not_igual 	        "~="
o_parent 	    	"("
c_parent 	    	")"

c_and 		"&&"
and 		"&"
c_or 		"||"
or 			"|"

if			"if"
elseif 		"elseif"
else		"else"
for			"for"
while		"while"
end			"end"
input		"input"
disp		"disp"

comma       ","
semicolon   ";"

digits 	[0-9]+
var 		[a-z][a-zA-Z0-9]*

%%

{add}          	{return ADD;}
{sub}			{return SUB;}
{mul}			{return MUL;}
{div}						{return DIV;}
{o_parent}			{return OPEN_P;}
{c_parent}			{return CLOSE_P;}
{not_igual}			{return NOT_IGUAL;}
{igual}					{return IGUAL;}
{igual_igual}		{return IGUAL_IGUAL;}
{menor}         {return MENOR;}
{menor_igual}		{return MENOR_IGUAL;}
{maior}					{return MAIOR;}
{maior_igual}		{return MAIOR_IGUAL;}
{c_and}				{return C_AND;}
{and}					{return AND;}
{c_or}				{return C_OR;}
{or}					{return OR;}

{if}					{return IF;}
{elseif} 			{return THEN;}
{else}				{return ELSE;}
{for}					{return FOR;}
{while}				{return WHILE;}
{end}					{return END;}
{input}				{return INPUT;}
{disp}				{return DISP;}

{true}				{return TRUE;}
{false}				{return FALSE;}


{semicolon}			{return SEMICOLON;}

{digits} 		{yylval.ival=atoi(yytext); return NUM;}
{var}       {yylval.sval=String(yytext); return ID;}
. 					{yyerror("unexpected character");}

%%
int main(int argc, char **argv){
++ argv, --argc;
if(argc > 0)
yyin =fopen(argv[0], "r");
else
yyin=stdin;
yylex();}
