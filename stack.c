#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "stackDef.h"

void print_gram(gram_elem* e){
	if(e->is_term){
		printf("%s\n", TerminalString(e->elem.terminal));
	}else{
		printf("%s\n", nonTerminalStringTable[e->elem.nonterminal]->nonterminal);
	}
}

gram_elem* top(Stack *s){
	Ele *ptr=s->tail;
	return ptr->el;
}

bool isEmpty(Stack *s){
	if (s->size==0) return true;
	return false;
}

Ele* pop(Stack *s){
	if(isEmpty(s)) return NULL;
	if(s->size==1) {Ele *ptr= s->head; s->head=NULL; s->tail=NULL; s->size--; return ptr;}
	Ele *ptr = s->head;
	while(ptr->next!=s->tail){ ptr=ptr->next; }
	Ele *ret = s->tail;
	s->tail=ptr;
	s->size--;
	return ret;
}

Ele* returnEle(bool is_term, int t){
  Ele *e = (Ele*)malloc(sizeof(Ele));
  e->el = (gram_elem*)malloc(sizeof(gram_elem));
  e->el->is_term=is_term;
  if(is_term){
	  e->el->elem.terminal=t;
  }else{
	  e->el->elem.nonterminal=t;
  }
  e->next=NULL;
  return e;
}

void push(Stack *s, Ele *e){
	if(s->size==0){
		s->head=e;
		s->tail=e;
	}else{
		s->tail->next=e;
		s->tail=e;
	}
	s->size++;
}

void pushAll(Stack *s, int rule_no){
	// if(rule_no==-1) return;
	g_node *g = grammar[rule_no]->next;
	while(g->next!=NULL){
		g=g->next;
	}
	while(g!=NULL){
		if(g->is_term){
			push(s, returnEle(1, g->elem.terminal));
		}
		else{
			push(s, returnEle(0, g->elem.nonterminal));
		}
		g=g->prev;
	}
}

int size(Stack *s){
	return s->size;
}

Stack* newStack(){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->size=0;
	s->head=NULL;
	s->tail=NULL;
	return s;
}
