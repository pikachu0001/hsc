
# Formal languages and compiler PROJECT 2017/2018 - HSC
# Bash script to build exec file for compilation
# Musciagna Giorgio

# drop or clean if exists "out" folder
out=out
if [ ! -d $out ]
then
	mkdir out
else
	ls=`ls $out`
	if [ ! -z "$ls" ]
	then
   		rm -r $out/*
   	fi
fi

# exec flex and yacc
src=src
flex -o $out/lex.yy.c -l $src/*.lex
yacc -o $out/y.tab.c -vd $src/*.yacc

# exec gcc on y.tab.c
gcc $out/y.tab.c -ly -ll

# run
./a.out < testcode
