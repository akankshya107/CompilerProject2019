run: compile
	./exe
compile: driver.o lexer.o parser.o lexhead parshead
	gcc driver.o lexer.o parser.o -o exe
driver.o: driver.c 
	gcc -c driver.c
parser.o: parser.c
	gcc -c parser.c 
lexer.o: lexer.c
	gcc -c lexer.c
lexhead:
	gcc lexer.h
	gcc lexerDef.h
parshead:
	gcc parser.h
	gcc parserDef.h