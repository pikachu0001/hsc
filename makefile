flex -l hsc.lex
yacc -vd hsc.yacc
gcc y.tab.c -ly -ll
./a.out
