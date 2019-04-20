#include "Intermediate.h"

quadruple *writeDataDefs(quadruple *code, FILE *fp){
    while(code->operand->flag==0 && code->operand->u.tag==TAG_DECLARE){
        if(code->a1->u.width==2) fprintf(fp, "%s\tdw\tdup(?)", code->L->u.dataDef);
        else fprintf(fp, "%s\tdd\tdup(?)", code->L->u.dataDef);
        code=code->next;
    }
    return code;
}

void writeCode(quadruple *code, FILE *fp){
    while(code!=NULL){
        if(code->operand->flag==0 && code->operand->u.tag==TAG_READ){
            fprintf(fp, "\tMOV\tEDX, %d", (code->a2->u.width==2)? 3:5);
            fprintf(fp, "\tMOV\tECX, %s", code->a1->u.L->u.dataDef);
            fprintf(fp, "\tMOV\tEAX, 3");
            fprintf(fp, "\tMOV\tEBX, EAX");
            fprintf(fp, "\tINT\t80H");
        }
        else if(code->operand->flag==0 && code->operand->u.tag==TAG_WRITE){
            fprintf(fp, "\tMOV\tEDX, %d", (code->a2->u.width==2)? 3:5);
            fprintf(fp, "\tMOV\tECX, %s", code->a1->u.L->u.dataDef);
            fprintf(fp, "\tMOV\tEBX, 1");
            fprintf(fp, "\tMOV\tEAX, 4");
            fprintf(fp, "\tINT\t80H");
        }
        else if(code->operand->flag==1 && (code->operand->u.tkname==TK_PLUS || code->operand->u.tkname==TK_MINUS || code->operand->u.tkname==TK_DIV || code->operand->u.tkname==TK_MUL)){
            if(code->operand->u.tkname==TK_PLUS){
                
            }
            else if(code->operand->u.tkname==TK_MINUS){

            }
            else if(code->operand->u.tkname==TK_DIV){

            }
            else if(code->operand->u.tkname==TK_MUL){

            }
        }
        code = code->next;
    }
    fprintf(fp, "\tMOV\tEAX, 1");
    fprintf(fp, "\tMOV\tEBX, 0");
    fprintf(fp, "\tINT\t80H");
}

void generateCode(ASTNodeIt *ast, char *filename){
	FILE *fp = fopen(filename, "w");
    quadruple *fullcode = generateIntermediateCode(ast);
    fprintf(fp,"SECTION .bss\n");
    fprintf(fp,"\tlpBuffer: resb 18\n\tBuf_Len: equ $-lpBuffer\n");
    fprintf(fp,"lft: RESW 8\nFOR_CTRL: RESW 8\nOUT: RESW 10\ntemp: RESW 1\nrgt: RESW 1\n");
    quadruple *stmts = writeDataDefs(fullcode, fp);
    fprintf(fp,"SECTION .text\nglobal _start\n\n_start:\n");
    writeCode(stmts, fp);
}