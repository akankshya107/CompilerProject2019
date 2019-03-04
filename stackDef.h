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