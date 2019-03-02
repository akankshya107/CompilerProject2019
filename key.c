#include "key.h"
#include <stdlib.h>
#include <string.h>
int hash(char *str){
	long unsigned int sum = 0;
	long unsigned int a = 32;
	for (int i=0; i<strlen(str); i++){
		sum=(sum*a+str[i])%43;
	}
	return sum;
}

hash_elem *create_hash_elem(){
    hash_elem *h = (hash_elem*)malloc(sizeof(hash_elem));
    h->str = (char*)malloc(sizeof(char)*11);
    h->tkname = -1;
}

hashTable populateKeyWordTable(){
    KeyWordTable = (hashTable)malloc(sizeof(hash_elem*)*NO_OF_KEYWORDS);

    int index;
    int count=0;
    int *array = (int*)malloc(24*sizeof(int));
    //populate this 
    //with
    index = hash("with");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_WITH;
    KeyWordTable[index]->str = "with";

    //parameters
    index = hash("parameters");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_PARAMETERS;
    KeyWordTable[index]->str = "parameters";

    //end
    index = hash("end");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_END;
    KeyWordTable[index]->str = "end";

    //while
    index = hash("while");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_WHILE;
    KeyWordTable[index]->str = "while";

    //type
    index = hash("type");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_TYPE;
    KeyWordTable[index]->str = "type";

    //main
    index = hash("_main");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_MAIN;
    KeyWordTable[index]->str = "main";

    //global
    index = hash("global");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_GLOBAL;
    KeyWordTable[index]->str = "global";

    //parameter
    index = hash("parameter");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_PARAMETER;
    KeyWordTable[index]->str = "parameter";

    //list
    index = hash("list");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_LIST;
    KeyWordTable[index]->str = "list";

    //input
    index = hash("input");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_INPUT;
    KeyWordTable[index]->str = "input";

    //output
    index = hash("output");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_OUTPUT;
    KeyWordTable[index]->str = "output";

    //int 
    index = hash("int");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_INT;
    KeyWordTable[index]->str = "int";

    //real
    index = hash("real");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_REAL;
    KeyWordTable[index]->str = "real";

    //endwhile
    index = hash("endwhile");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_ENDWHILE;
    KeyWordTable[index]->str = "endwhile";

    //if
    index = hash("if");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_IF;
    KeyWordTable[index]->str = "if";

    //then
    index = hash("then");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_THEN;
    KeyWordTable[index]->str = "then";

    //endif
    index = hash("endif");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_ENDIF;
    KeyWordTable[index]->str = "endif";

    //read
    index = hash("read");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_READ;
    KeyWordTable[index]->str = "read";

    //write 
    index = hash("write");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_WRITE;
    KeyWordTable[index]->str = "write";

    //return
    index = hash("return");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_RETURN;
    KeyWordTable[index]->str = "return";

    //call
    index = hash("call");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_CALL;
    KeyWordTable[index]->str = "call";

    //record
    index = hash("record");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_RECORD;
    KeyWordTable[index]->str = "record";

    //endrecord
    index = hash("endrecord");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_ENDRECORD;
    KeyWordTable[index]->str = "endrecord";

    //else
    index = hash("else");
    array[count] = index;
    count++;
    KeyWordTable[index]=create_hash_elem();
    KeyWordTable[index]->tkname = TK_ELSE;
    KeyWordTable[index]->str = "else";

    //see if any collisions
    int collisions=0;
    for(int i=0; i<count; i++){
        for(int j=0; j<i; j++){
            if(array[i]==array[j]){
                collisions++;
                break;
            }
        }
    }
    printf("%d",collisions);

    return KeyWordTable;
}

hash_elem* lookup(char *str){
    if(strcmp(str, KeyWordTable[hash(str)]->str)){
        return KeyWordTable[hash(str)];
    }
    else {
        hash_elem *ret = create_hash_elem();
        return ret;
    }
}