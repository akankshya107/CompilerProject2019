// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#ifndef PARSE_INCLUDED
#include "parserDef.h"
#endif
typedef struct{
	bool is_term;
	union{
		TOKEN terminal;
		NON_TERMINAL nonterminal;
	}elem;
}gram_elem;

typedef struct Ele{
  gram_elem *el;
  struct Ele *next;
}Ele;

typedef struct{
	int size;
	Ele *head;
	Ele *tail;
}Stack;