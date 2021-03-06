// GROUP 39
// AKANKSHYA MISHRA 2016A7PS0026P
// NARAPAREDDY BHAVANA 2016A7PS0034P
// KARABEE BATTA 2016A7PS0052P
// AASTHA KATARIA 2016A7PS0062P
#include <stdbool.h>
#define NO_OF_STATES 55
#define NO_OF_RULES 50
#define BUF_LENGTH 512
#define MAX_LENGTH 32

// bool global_flag;
// int line_count; //Still a doubt

char *input_buffer;

typedef enum {
	TK_ASSIGNOP, TK_COMMENT, TK_FIELDID, TK_ID, TK_NUM, TK_RNUM, TK_FUNID, TK_RECORDID, TK_WITH, 
	TK_PARAMETERS, TK_END, TK_WHILE, TK_TYPE, TK_MAIN, TK_GLOBAL, TK_PARAMETER, TK_LIST, TK_SQL,
	TK_SQR, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_COMMA, TK_SEM, TK_COLON, TK_DOT, TK_ENDWHILE,
	TK_OP, TK_CL, TK_IF, TK_THEN , TK_ENDIF, TK_READ, TK_WRITE, TK_RETURN, TK_PLUS, TK_MINUS, TK_MUL,
	TK_DIV, TK_CALL, TK_RECORD, TK_ENDRECORD, TK_ELSE, TK_AND, TK_OR, TK_NOT, TK_LT, TK_LE, TK_EQ,
	TK_GT, TK_GE, TK_NE, eps, EOS
} TOKEN;

typedef enum {
	program, mainFunction, otherFunctions, function, input_par, output_par,
	parameter_list, dataType, primitiveDatatype, constructedDatatype, 
	remaining_list, stmts, typeDefinitions, typeDefinition, fieldDefinitions,
	fieldDefinition, moreFields, declarations, declaration, global_or_not, 
	otherStmts, stmt, assignmentStmt, singleOrRecId, new_24, funCallStmt,
	outputParameters, inputParameters, iterativeStmt, conditionalStmt,
	elsePart, ioStmt, allVar, arithmeticExpression, expPrime, term,
	termPrime, factor, highPrecedenceOperators, lowPrecedenceOperators, 
	temp, booleanExpression, var, logicalOp, relationalOp, returnStmt, 
	optionalReturn, idList, more_ids
} NON_TERMINAL;
//IMPORTANT: NO DISTINGUISHING BETWEEN ALLVAR AND ALL

typedef enum  {
	is_lexeme, 
	is_int,
	is_real
} FLAG_TOKEN_TYPE;

typedef struct{
	TOKEN tokenName;
	int line_no;
	FLAG_TOKEN_TYPE flag;
	union{
		char* lexeme;
		int value_of_int;
		float value_of_real;
	}u;
}tokenInfo;

//keyword table implementation

typedef enum {
	is_state,
	is_token_function,
	is_error_function
} TRANSITION_TYPE;

typedef struct{
	TRANSITION_TYPE flag;
	union{
		int state;
		// tokenInfo* (*return_token_function)(char*);
		struct{
			TOKEN tkname;
			int func_flag;
			bool is_retract;
		}func;
		void (*error_function)(char*, int, char, int*, int*);
	}u;
}TRANSITION_TABLE_ELEM;

TRANSITION_TABLE_ELEM **transition_table;