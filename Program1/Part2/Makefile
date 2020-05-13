CC = gcc
CFLAGS = -g
OBJs = parse.tab.o lex.yy.o

default: rps

rps: ${OBJs}
	${CC} ${CFLAGS} ${OBJs} -o rps

lex.yy.c: scan.l parse.tab.h 
	flex -i scan.l

parse.tab.c: parse.y 
	bison -dv  parse.y

parse.tab.h: parse.tab.c

clean:
	rm -f rps  lex.yy.c *.o parse.tab.[ch] parse.output
depend:
	makedepend  -I. *.c
