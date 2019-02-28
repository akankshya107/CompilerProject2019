#define NO_OF_STATES 55
#define BUF_LENGTH 512
char *input_buffer;
char *input_buffer_twin;

typedef enum {
	TK_ASSIGNOP, TK_COMMENT, TK_FIELDID, TK_ID, TK_NUM, TK_RNUM, TK_FUNID, TK_RECORDID, TK_WITH, 
	TK_PARAMETERS, TK_END, TK_WHILE, TK_TYPE, TK_MAIN, TK_GLOBAL, TK_PARAMETER, TK_LIST, TK_SQL,
	TK_SQR, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_COMMA, TK_SEM, TK_COLON, TK_DOT, TK_ENDWHILE,
	TK_OP, TK_CL, TK_IF, TK_THEN , TK_ENDIF, TK_READ, TK_WRITE, TK_RETURN, TK_PLUS, TK_MINUS, TK_MUL,
	TK_DIV, TK_CALL, TK_RECORD, TK_ENDRECORD, TK_ELSE, TK_AND, TK_OR, TK_NOT, TK_LT, TK_LE, TK_EQ,
	TK_GT, TK_GE, TK_NE, eps
} TOKEN;
typedef enum {
	program, mainFunction, otherFunctions, function, input_par, output_par,
	parameter_list, dataType, primitiveDatatype, constructedDatatype, 
	remaining_list, stmts, typeDefinitions, typeDefinition, fieldDefinitions,
	fieldDefinition, moreFields, declarations, declaration, global_or_not, 
	otherStmts, stmt, assignmentStmt, singleOrRecId, new_24, funCallStmt,
	outputParameters, inputParameters, iterativeStmt, conditionalStmt,
	elsePart, ioStmt, allVar, arithmeticExpression, expPrime, term,
	termPrime, factor, highPrecedenceOperator, lowPrecedenceOperator, 
	all, temp, booleanExpression, var, logicalOp, relationalOp, returnStmt, 
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

//symbol table implementation

typedef enum {
	is_state,
	is_token_function,
	is_error_function
} TRANSITION_TYPE;

typedef struct{
	TRANSITION_TYPE flag;
	union{
		int state;
		tokenInfo* (*return_token_function)(void);
		void (*error_function)(void);
	}u;
}TRANSITION_TABLE_ELEM;


