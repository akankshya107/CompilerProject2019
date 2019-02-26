char *input_buffer;
char *input_buffer_twin;

typedef enum {TK_ASSIGNOP, TK_COMMENT, TK_FIELDID, TK_ID, TK_NUM, TK_RNUM, TK_FUNID, TK_RECORDID, TK_WITH, TK_PARAMETERS, TK_END, TK_WHILE, TK_TYPE, TK_MAIN, TK_GLOBAL, TK_PARAMETER, TK_LIST, TK_SQL, TK_SQR, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_COMMA, TK_SEM, TK_COLON, TK_DOT, TK_ENDWHILE, TK_OP, TK_CL, TK_IF, TK_THEN , TK_ENDIF, TK_READ, TK_WRITE, TK_RETURN, TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_CALL, TK_RECORD, TK_ENDRECORD, TK_ELSE, TK_AND, TK_OR, TK_NOT, TK_LT, TK_LE, TK_EQ, TK_GT, TK_GE, TK_NE, eps} TOKEN;

typedef struct{
	TOKEN tokenName;
	int line_no;
	union{
		int lexeme;
		int value_of_int;
		int value_of_real;
	};
}tokenInfo;

//storing lexemes in array -how??


typedef union{
	int state;
	tokenInfo* (*fun_ptr)(void);
}TRANSITION_TABLE_ELEM;


