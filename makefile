<<<<<<< HEAD
compile: lexhead parshead parser.o driver.o
	gcc parser.o driver.o -o exe
=======
# // GROUP 39
# // AKANKSHYA MISHRA 2016A7PS0026P
# // NARAPAREDDY BHAVANA 2016A7PS0034P
# // KARABEE BATTA 2016A7PS0052P
# // AASTHA KATARIA 2016A7PS0062P
compile: keyhead lexhead parshead stackhead grammarhead key.o DFA.o grammar.o stack.o lexer.o parser.o driver.o
	gcc driver.o DFA.o grammar.o stack.o lexer.o parser.o key.o -o stage1exe
>>>>>>> 822a511e5ac2b3b3685296573d69ef557a776d65
driver.o: driver.c 
	gcc -c -g driver.c
parser.o: parser.c
	gcc -c -g parser.c 
<<<<<<< HEAD
# lexer.o: lexer.c
# 	gcc -c -g lexer.c
# key.o: key.c
# 	gcc -c -g key.c 
# keyhead:
# 	gcc keyDef.h
# 	gcc key.h
=======
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
>>>>>>> 822a511e5ac2b3b3685296573d69ef557a776d65
lexhead:
	gcc lexerDef.h
	gcc lexer.h
parshead:
	gcc parserDef.h
<<<<<<< HEAD
	gcc parser.h
=======
	gcc parser.h
stackhead: 
	gcc stackDef.h
	gcc stack.h
grammarhead: 
	gcc grammarDef.h
	gcc grammar.h
# clearall: key.o lexer.o parser.o driver.o
# 	rm key.o lexer.o parser.o driver.o
>>>>>>> 822a511e5ac2b3b3685296573d69ef557a776d65
