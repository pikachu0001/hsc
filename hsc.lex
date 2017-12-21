%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
%}



NUM		[0-9]+(\.[0-9]+)?
VAR		[a-zA-Z]([a-zA-Z]|[0-9])*



%%



[\t ]		{}
\+			{return '+';}
\-			{return '-';}
\*			{return '*';}
\/			{return '/';}
\n			{return '\n';}
halt\.		{return HALT;}
{NUM}		{yylval.dbl = atof(yytext);
			return NUM;}
{VAR}		{yylval.str = strdup(yytext);
			return VAR;}


%%
