%option noyywrap
%{
// http://www.cs.man.ac.uk/~pjj/cs212/ex2_str_comm.html
#include <stdlib.h>
#include <string.h>
#include "symtab/symtab.h"
extern char *parse_string(char *string, int length);
extern double parse_boolean(char *boolean);
%}




DIGIT					[0-9]
LETTER					[a-zA-Z]
NUM						{DIGIT}+(\.{DIGIT}+)?
BOOLEAN					true|false
TYPE					real|string|boolean
ID						{LETTER}({LETTER}|{DIGIT})*
STRING					\"([^\t\n\"]|\\\")*\"|\'([^\t\n\']|\\\')*\'
COMMENT					\(\*([^*]|\n|\*[^\)])*\*\)




%%




[\t ]					{}
\+						{return ADD;}
\-						{return SUB;}
\*						{return MUL;}
\/						{return DIV;}
\n						{return NEWLINE;}
\(						{return ROUND_OPEN;}
\)						{return ROUND_CLOSE;}
\:						{return COLON;}
\:=						{return ASSIGNMENT;}
math\.pi				{return PI;}
math\.e					{return E;}
write					{return WRITE;}
writeln					{return WRITELN;}
halt					{return HALT;}
var						{return VAR;}
{COMMENT}				{}
{TYPE}					{yylval.str = strdup(yytext); return TYPE;}
{NUM}					{yylval.dbl = atof(yytext); return NUM;}
{BOOLEAN}				{yylval.dbl = parse_boolean(yytext); return BOOLEAN;}
{ID}					{yylval.str = strdup(yytext); return ID;}
{STRING}				{yylval.str = parse_string(yytext, yyleng); return STRING;}
.						{yyerror("Unexpected token!"); exit(0);}





%%




char *parse_string(char *string, int length) {
	char *str = malloc(sizeof(length));
	int y = 0;
	for (int i = 1; i < length - 1; i++) {
		if (string[i] != '\\') {
			str[y++] = string[i];
		}
	}
	return str;
}


double parse_boolean(char *boolean) {
	if (strcmp(boolean, "true") == 0) {
		return 1;
	}
	if (strcmp(boolean, "false") == 0) {
		return 0;
	}
	yyerror("Cannot assign a non boolean value");
}
