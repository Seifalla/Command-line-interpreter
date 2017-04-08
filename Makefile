GCC = gcc -g -Wall -pedantic
OBJECTS = lex.yy.o nshParser.o error.o main.o

asu : $(OBJECTS)
	$(GCC) $(OBJECTS) -o nsh
lex.yy.o : global.h lex.yy.c
	$(GCC) -c lex.yy.c -lfl
parser.o : global.h nshParser.c
	$(GCC) -c nshParser.c
error.o : global.h error.c
	$(GCC) -c error.c
main.o : global.h main.c
	$(GCC) -c main.c
lex.yy.c : global.h nsh.lex
	flex nsh.lex

clean:
	-rm -f $(OBJECTS) lex.yy.c nsh
