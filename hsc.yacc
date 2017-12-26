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
extern void declare_variable(char *name, char* type);
extern void assign_to_variable(char *name, double value);
extern double get_variable_value(char *name);
#define YYDEBUG 0
%}




%union {
	int chr;
	double dbl;
	char *str;
	Node *sym;
}
%token <chr> ADD SUB MUL DIV NEWLINE ROUND_OPEN ROUND_CLOSE COLON ASSIGNMENT WRITE WRITELN HALT VAR
%token <dbl> PI E NUM BOOLEAN
%token <str> TYPE ID STRING
%type <dbl> expression constant
%left ADD SUB
%left MUL DIV
%start program




%%




program			:	statement program
				|	NEWLINE program
				|															{/* epsilon */}
				;



statement		:	declaration
				|	assignment
				|	write
				| 	HALT													{/* interrupt execution */ exit(0);}
				;



declaration		:	VAR ID COLON TYPE										{declare_variable($2, $4);}
				;



assignment		:	ID ASSIGNMENT expression								{assign_to_variable($1, $3);}
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
				|	BOOLEAN													{$$ = $1;}
				|	NUM														{$$ = $1;}
				|	ID														{$$ = get_variable_value($1);}
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
	#if YYDEBUG
        yydebug = 1;
    #endif
    return yyparse();
}

void yyerror(const char *str) {
	fprintf(stderr, "\x1B[31mERROR!\x1B[33m %s\x1B[0m\n", str);
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

void declare_variable(char *name, char* type) {
	Node *node = lookup(name);
	if (node != NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "The variable \"%s\" has been already declared.", name);
		yyerror(error);
	}
	push(name);
}

void assign_to_variable(char *name, double value) {
	Node *node = lookup(name);
	if (node == NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot assign the value. The variable \"%s\" has not been declared.", name);
		yyerror(error);
	}
	set_value(node, value);
}

double get_variable_value(char *name) {
	Node *node = lookup(name);
	if (node == NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot assign the value. The variable \"%s\" has not been declared.", name);
		yyerror(error);
	}
	return node->value;
}
