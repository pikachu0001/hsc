%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/symtab.h"
#include "../src/yaccutil.h"
extern int yylex();
#define YYDEBUG 0
%}




%union {
	int chr;
	double dbl;
	char *str;
	Node *sym;
}
%token <chr> ADD SUB MUL DIV AND OR NOT NEWLINE ROUND_OPEN ROUND_CLOSE COLON ASSIGNMENT WRITE WRITELN HALT VAR TRUE FALSE
%token <str> TYPE ID STRING
%token <dbl> PI E NUM
%type <sym> expression boolean number
%left ADD SUB
%left MUL DIV
%left OR
%left AND
%left NOT
%nonassoc UMINUS
%start program




%%




program			:	statement NEWLINE program
				|	statement
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
				|	WRITELN expression 										{write_expression($2); printf("\n");}
				|	WRITELN	STRING 											{write_string($2); printf("\n");}
				|	WRITELN													{printf("\n");}
				;



expression		:	ROUND_OPEN expression ROUND_CLOSE						{$$ = $2;}
				|	expression ADD expression								{$$ = op_add($1, $3);}
				|	expression SUB expression								{$$ = op_sub($1, $3);}
				|	expression MUL expression								{$$ = op_mul($1, $3);}
				|	expression DIV expression								{$$ = op_div($1, $3);}
				|	SUB expression %prec UMINUS								{$$ = op_uminus($2);}
				|	expression AND expression								{$$ = op_and($1, $3);}
				|	expression OR expression								{$$ = op_or($1, $3);}
				|	NOT expression											{$$ = op_not($2);}
				|	number													{$$ = $1;}
				|	boolean													{$$ = $1;}
				|	ID														{$$ = get_variable_for_exprattr_transmission($1);}
				;



boolean			:	TRUE													{$$ = createUnnamedSymbolForExprAttr(BOOLEAN, 1);}
				|	FALSE													{$$ = createUnnamedSymbolForExprAttr(BOOLEAN, 0);}
				;



number			:	NUM														{$$ = createUnnamedSymbolForExprAttr(REAL, $1);}
				|	PI														{$$ = createUnnamedSymbolForExprAttr(REAL, 3.14159265359);}
				|	E														{$$ = createUnnamedSymbolForExprAttr(REAL, 2.71828182846);}
				;




/* INFO: const REAL/BOOLEAN from yaccutil.h */




%%




#include "lex.yy.c"

int main() {
	#if YYDEBUG
        yydebug = 1;
    #endif
    return yyparse();
}
