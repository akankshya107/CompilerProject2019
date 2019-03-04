#include "stackDef.h"

gram_elem* top(Stack *s);
gram_elem* pop(Stack *s);
void push(Stack *s, Ele *e);
void pushAll(Stack *s, int rule_no);
int size(Stack *s);
bool isEmpty(Stack *s);
Stack* newStack();
Ele* returnEle(bool is_term, int t);