%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
#include "symtab/symtab.h"
extern char *get_string(char *string, int length);
%}




DIGIT		[0-9]
LETTER		[a-zA-Z]
NUM			{DIGIT}+(\.{DIGIT}+)?
VAR			{LETTER}({LETTER}|{DIGIT})*
STRING		\"([^\t\n\"]|\\\")*\"|\'([^\t\n\']|\\\')*\'




%%




[\t ]		{}
\+			{return ADD;}
\-			{return SUB;}
\*			{return MUL;}
\/			{return DIV;}
\=			{return ASSIGN;}
\n			{return NEWLINE;}
\(			{return ROUND_OPEN;}
\)			{return ROUND_CLOSE;}
math\.pi	{return PI;}
math\.e		{return E;}
write		{return WRITE;}
writeln		{return WRITELN;}
halt		{return HALT;}
{NUM}		{yylval.dbl = atof(yytext); return NUM;}
{VAR}		{yylval.sym = push(strdup(yytext)); return VAR;}
{STRING}	{yylval.str = get_string(yytext, yyleng); return STRING;}
.			{yyerror("Unexpected token!"); exit(0);}




%%




char *get_string(char *string, int length) {
	char *str = malloc(sizeof(length));
	int y = 0;
	for (int i = 1; i < length - 1; i++) {
		if (string[i] != '\\') {
			str[y++] = string[i];
		}
	}
	return str;
}
