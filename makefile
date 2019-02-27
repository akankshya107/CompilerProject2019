run: compile
	./exe
compile: driver.o lexer.o lexhead parshead
	gcc driver.o lexer.o -o exe
driver.o: driver.c 
	gcc -c driver.c
lexer.o: lexer.c
	gcc -c lexer.c
lexhead:
	gcc lexer.h
	gcc lexerDef.h
parshead:
	gcc parser.h
	gcc parserDef.h