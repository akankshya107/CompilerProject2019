# run: compile
# 	./exe
compile: keyhead lexhead parshead key.o lexer.o parser.o driver.o
	gcc driver.o lexer.o parser.o key.o -o exe
driver.o: driver.c 
	gcc -c -g driver.c
parser.o: parser.c
	gcc -c -g parser.c 
lexer.o: lexer.c
	gcc -c -g lexer.c
key.o: key.c
	gcc -c -g key.c 
keyhead:
	gcc keyDef.h
	gcc key.h
lexhead:
	gcc lexerDef.h
	gcc lexer.h
parshead:
	gcc parserDef.h
	gcc parser.h
# clearall: key.o lexer.o parser.o driver.o
# 	rm key.o lexer.o parser.o driver.o