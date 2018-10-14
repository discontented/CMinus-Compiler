CCC = g++
CCFLAGS= -O2 -Wall -Wno-unused -Wno-deprecated -Wno-write-strings
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

imp: y.tab.o lex.yy.o cMinus.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o cMinus.o -o imp 

imp.o: cMinus.cpp cMinus.h
	${CCC} -c imp.cpp
y.tab.o: syntax.y
	${YACC} ${YFLAGS} syntax.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: lexer.l
	${LEX} $(LFLAGS) lexer.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o imp