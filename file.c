#include<stdio.h>
// int main()
// {
//     FILE* fp =fopen("nt_string.txt","r");
// 	char c;
// 	int i=0;
// 	int j=0;
//     while(c=fgetc(fp)!=EOF)
// 	{
// 		printf("%c 1",c);
// 		// if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_')
// 		// {
// 		// 	nonTerminalStringTable[i]->nonterminal[j++]=c;
// 		// }
// 		// else
// 		// {
// 		// 	nonTerminalStringTable[i]->nonterminal[j++]='\0';
// 		// 	i++;

// 		// }
		
// 	}
// 	fclose(fp);
// }

int main() {

    FILE *f;
    char c;
    f=fopen("nt_string.txt","r");

    while((c=fgetc(f))!=EOF){
        
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'||(c>='0'&&c<='9'))
		{
			// nonTerminalStringTable[i]->nonterminal[j++]=c;
            printf("%c",c);
		}
		else
		{
			// nonTerminalStringTable[i]->nonterminal[j++]='\0';
			// i++;
            printf(" ");
            continue;
		}
    }

    fclose(f);
    return 0;
}