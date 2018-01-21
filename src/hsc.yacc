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
%token <chr> ADD SUB MUL DIV AND OR NOT NEWLINE ROUND_OPEN ROUND_CLOSE COLON ASSIGNMENT COMMA EQUAL EQUAL_EQUAL GREATER GREATER_EQUAL LESS LESS_EQUAL WRITE WRITELN HALT VAR TRUE FALSE BEGIN_SCOPE END_SCOPE
%token <str> TYPE ID STRING
%token <dbl> PI E NUM
%type <str> declist
%type <sym> expression boolean number
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS EQUAL_EQUAL GREATER GREATER_EQUAL LESS LESS_EQUAL
%left OR
%left AND
%left NOT
%start program




%%




program			:	statement NEWLINE program
				|	statement
				|	NEWLINE program
				|	BEGIN_SCOPE {increase_scope();} program END_SCOPE {pop_variables_at_scope_closed();} program
				|															{/* epsilon */}
				;



statement		:	declaration
				|	assignment
				|	write
				| 	HALT													{/* interrupt execution */ exit(0);}
				;



declaration		:	VAR declist
				|	VAR ID COLON TYPE EQUAL expression						{declare_variable($2, $4); assign_to_variable($2, $6);}
				;



declist			:	ID COMMA declist										{declare_variable($1, $3); $$ = $3;}
				|	ID COLON TYPE											{declare_variable($1, $3); $$ = $3;}
				;



assignment		:	ID ASSIGNMENT expression								{assign_to_variable($1, $3);}
				;



write			:	WRITE writelist
				|	WRITELN writelist 										{printf("\n");}
				|	WRITELN													{printf("\n");}
				;



writelist		:	writelist COMMA expression								{write_expression($3);}
				|   writelist COMMA STRING									{write_string($3);}
				|	expression												{write_expression($1);}
				|	STRING													{write_string($1);}
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
				|	expression EQUAL_EQUAL expression						{$$ = op_equal($1, $3);}
				|	expression GREATER expression							{$$ = op_greater($1, $3);}
				|	expression GREATER_EQUAL expression						{$$ = op_greater_equal($1, $3);}
				|	expression LESS expression								{$$ = op_less($1, $3);}
				|	expression LESS_EQUAL expression						{$$ = op_less_equal($1, $3);}
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
