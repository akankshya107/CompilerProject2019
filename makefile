run: compile
	./exe
compile: lexhead parshead lexer.o parser.o driver.o
	gcc driver.o lexer.o parser.o -o exe
driver.o: driver.c 
	gcc -c driver.c
parser.o: parser.c
	gcc -c parser.c 
lexer.o: lexer.c
	gcc -c lexer.c
lexhead:
	gcc lexerDef.h
	gcc lexer.h
parshead:
	gcc parserDef.h
	gcc parser.h