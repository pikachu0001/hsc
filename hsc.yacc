%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void yyerror(const char *str) {fprintf(stderr, ">> Ops! %s\nBye!", str);}
extern int yylex();
%}



%union { double dbl; char* str; }
%token <dbl> NUM
%token <str> VAR
%token <str> HALT
%type <dbl> exp
%left '+' '-'
%left '*' '/'
%start program



%%


program	: text
		;

text 	: stmt '\n' text					{}
		| HALT '\n'							{printf("Bye!\n"); exit(0);}
		;

stmt	: exp								{printf(">> %f\n>> ", $1);}
		;

exp		: exp '+' exp						{$$ = $1 + $3;}
		| exp '-' exp						{$$ = $1 - $3;}
		| exp '*' exp						{$$ = $1 * $3;}
		| exp '/' exp						{$$ = $1 / $3;}
		| NUM								{$$ = $1;}
		;



%%



#include "lex.yy.c"
int main() {
	printf("Hi!\n>> ");
	return yyparse();
}
