CCC = g++
CCFLAGS= -O2 -Wall -Wno-unused -Wno-deprecated -Wno-write-strings
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y
F_BISON = syntax
F_LEX = lexer
F_CPP = cMinus

RM = /bin/rm -f

${F_CPP}: y.tab.o lex.yy.o ${F_CPP}.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o ${F_CPP}.o -o ${F_BISON}

${F_CPP}.o: ${F_CPP}.cpp ${F_CPP}.h
	${CCC} -c ${F_CPP}.cpp
y.tab.o: ${F_BISON}.y
	${YACC} ${YFLAGS} ${F_BISON}.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: ${F_LEX}.l
	${LEX} $(LFLAGS) ${F_LEX}.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o ${F_BISON}
