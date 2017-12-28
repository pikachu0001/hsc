%option noyywrap
%option yylineno
%{
#include <stdlib.h>
#include <string.h>
#include "../src/symtab.h"
extern char *remove_quotes(char *string, int length);
// REFERENCES:	http://www.cs.man.ac.uk/~pjj/cs212/ex2_str_comm.html
//				http://epaperpress.com/lexandyacc/str.html
char buf[150];
char *s;
%}
%x STR




DIGIT					[0-9]
LETTER					[a-zA-Z]
NUM						{DIGIT}+(\.{DIGIT}+)?
TYPE					real|boolean
ID						{LETTER}({LETTER}|{DIGIT})*
COMMENT					\(\*([^*]|\n|\*[^\)])*\*\)




%%




\'						{BEGIN STR; s = buf;}
<STR>\\n				{*s++ = '\n';}
<STR>\\t				{*s++ = '\t';}
<STR>\'\'				{*s++ = '\'';}
<STR>\'					{*s = 0; BEGIN 0; yylval.str = strdup(buf); return STRING;}
<STR>\n					{yyerror("Cannot write strings on multiple lines!");}
<STR>\t					{yyerror("Cannot use direct tabs inside the string! Use \\t instead");}
<STR>.					{*s++ = *yytext;}
[\t ]					{}
\+						{return ADD;}
\-						{return SUB;}
\*						{return MUL;}
\/						{return DIV;}
&&						{return AND;}
\|\|					{return OR;}
!						{return NOT;}
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
true					{return TRUE;}
false					{return FALSE;}
begin					{return BEGIN_SCOPE;}
end						{return END_SCOPE;}
{COMMENT}				{}
{TYPE}					{yylval.str = strdup(yytext); return TYPE;}
{NUM}					{yylval.dbl = atof(yytext); return NUM;}
{ID}					{yylval.str = strdup(yytext); return ID;}
.						{yyerror("Unexpected token!");}





%%
