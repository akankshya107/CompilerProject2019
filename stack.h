// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
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