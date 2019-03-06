# run: compile
# 	./exe
compile: keyhead lexhead parshead stackhead grammarhead key.o DFA.o grammar.o stack.o lexer.o parser.o driver.o
	gcc driver.o DFA.o grammar.o stack.o lexer.o parser.o key.o -o exe
driver.o: driver.c 
	gcc -c -g driver.c
parser.o: parser.c
	gcc -c -g parser.c 
lexer.o: lexer.c
	gcc -c -g lexer.c
key.o: key.c
	gcc -c -g key.c 
DFA.o: DFA.c
	gcc -c -g DFA.c
grammar.o: grammar.c 
	gcc -c -g grammar.c 
stack.o: stack.c
	gcc -c -g stack.c 
keyhead:
	gcc keyDef.h
	gcc key.h
lexhead:
	gcc lexerDef.h
	gcc lexer.h
parshead:
	gcc parserDef.h
	gcc parser.h
stackhead: 
	gcc stackDef.h
	gcc stack.h
grammarhead: 
	gcc grammarDef.h
	gcc grammar.h
# clearall: key.o lexer.o parser.o driver.o
# 	rm key.o lexer.o parser.o driver.o