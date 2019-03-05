#include "stackDef.h"

void print_gram(gram_elem* e);
gram_elem* top(Stack *s);
Ele* pop(Stack *s);
void push(Stack *s, Ele *e);
void pushAll(Stack *s, int rule_no);
int size(Stack *s);
bool isEmpty(Stack *s);
Stack* newStack();
Ele* returnEle(bool is_term, int t);