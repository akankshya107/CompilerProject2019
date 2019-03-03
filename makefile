# run: compile
# 	./exe
compile: keyhead lexhead parshead key.o lexer.o parser.o driver.o
	gcc driver.o lexer.o parser.o key.o -o exe
driver.o: driver.c 
	gcc -c driver.c
parser.o: parser.c
	gcc -c parser.c 
lexer.o: lexer.c
	gcc -c lexer.c
key.o: key.c
	gcc -c key.c 
keyhead:
	gcc keyDef.h
	gcc key.h
lexhead:
	gcc lexerDef.h
	gcc lexer.h
parshead:
	gcc parserDef.h
	gcc parser.h