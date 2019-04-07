# // GROUP 39
# // AKANKSHYA MISHRA 2016A7PS0026P
# // NARAPAREDDY BHAVANA 2016A7PS0034P
# // KARABEE BATTA 2016A7PS0052P
# // AASTHA KATARIA 2016A7PS0062P
compile: keyhead lexhead parshead stackhead grammarhead ASThead key.o DFA.o AST.o grammar.o stack.o lexer.o parser.o driver.o
	gcc driver.o AST.o DFA.o grammar.o stack.o lexer.o parser.o key.o -o stage1exe
driver.o: driver.c 
	gcc -c -g driver.c
AST.o: AST.c
	gcc -c -g AST.c
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
ASThead:
	gcc ASTDef.h
	gcc AST.h