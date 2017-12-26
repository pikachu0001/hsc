%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab/symtab.h"
extern int yylex();
extern void yyerror(const char *string);
extern void write_string(char *string);
extern void writeln_string(char *string);
extern void write_expression(double expression);
extern void writeln_expression(double expression);
%}




%union {
	int chr;
	double dbl;
	char *str;
	Node *sym;
}
%token <chr> ADD SUB MUL DIV ASSIGN NEWLINE ROUND_OPEN ROUND_CLOSE WRITE WRITELN HALT
%token <dbl> PI E NUM
%token <str> STRING
%token <sym> VAR
%type <dbl> expression constant
%left ADD SUB
%left MUL DIV
%start program




%%




program			:	statement program
				|	NEWLINE program
				|															{/* epsilon */}
				;



statement		:	write
				| 	HALT													{/* interrupt execution */ exit(0);}
				;



write			:	WRITE expression										{write_expression($2);}
				|	WRITE STRING 											{write_string($2);}
				|	WRITELN expression 										{writeln_expression($2);}
				|	WRITELN	STRING 											{writeln_string($2);}
				|	WRITELN													{printf("\n");}
				;



expression		:	expression ADD expression								{$$ = $1 + $3;}
				|	expression SUB expression								{$$ = $1 - $3;}
				|	expression MUL expression								{$$ = $1 * $3;}
				|	expression DIV expression								{$$ = $1 / $3;}
				|	ROUND_OPEN expression ROUND_CLOSE						{$$ = $2;}
				|	constant												{$$ = $1;}
				|	NUM														{$$ = $1;}
				;


constant		:	PI														{$$ = 3.14159265359;}
				|	E														{$$ = 2.71828182846;}
				;




%%



#include "lex.yy.c"

/*

			:	declaration	NEWLINE
			|	assignment	NEWLINE
			|	

*/

int main() {
	return yyparse();
}

void yyerror(const char *str) {
	fprintf(stderr, "Ops! %s\n", str);
	exit(0);
}

void write_string(char *string) {
	printf("%s", string);
}

void writeln_string(char *string) {
	printf("%s\n", string);
}

void write_expression(double expression) {
	printf("%f", expression);
}

void writeln_expression(double expression) {
	printf("%f\n", expression);
}





















/*







program	: stmt program
		| NEWLINE program
		| HALT								{printf("Bye!\n"); exit(0);}
		;

stmt	: NEWLINE 							{printf("\n>> ");}
		| exp								{printf(">> %f\n>> ", $1);}
		| VAR ASSIGN exp					{set_value($1, $3);	printf(">> ");}
		;

exp		: exp ADD exp						{$$ = $1 + $3;}
		| exp SUB exp						{$$ = $1 - $3;}
		| exp MUL exp						{$$ = $1 * $3;}
		| exp DIV exp						{$$ = $1 / $3;}
		| NUM								{$$ = $1;}
		| VAR								{printf("hi\n");
											$$ = $1->value;}
		;



*/