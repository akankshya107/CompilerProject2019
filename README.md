# CompilerProject2019

# To Do
AST, ICG, NASM: http://www.nasm.us/

# MODULES
Abstract Syntax Tree: This module takes as input the parse tree produced by the parser and generates a memory efficient abstract syntax tree (AST). The abstract syntax tree is generated by traversing the parse tree (one pass) eliminating unnecessary details such as semicolon, colon, comma, parenthesis, square brackets, assignment operator etc. The AST preserves the syntactic structure of a construct for code generation. The AST retains only those children which are essential for semantic analysis. The long chains of unnecessary nodes are collapsed. The leaf nodes of the AST still continue to contain the tokens and other relevant information extracted.  

Prepare semantic rules to obtain AST for each construct and implement. For implementation, you may have to modify the structure of the parse tree nodes as was discussed during regular lectures.  

Symbol Table (ST): This module takes as input the abstract syntax tree generated as above. Symbol table is a special data structure that maintains information about the identifiers (variables that participate in computation as the source code is executed). The information gathered during semantic analysis phase is extremely valuable for generating the assembly language code for the input source code. Variables declared in different static scopes are maintained in separate symbol tables. Implement Symbol Table to incorporate following information for all identifiers.

    Type
    width
    Scope
    offset etc.

The variable identifiers are defined within the static scope of a function definition.

Type Extractor and Checker: Type of an identifier is extracted from the declaration statement that declares the identifier. The data types supported in the language you are implementing are: integer, real and record. The type checker verifies the type of an expression appearing at the right hand side of the assignment statement and checks if it matches with that of the identifier on the left hand side. An arithmetic operator can have two operands of the similar type, where types can be integer and real data types.

The general type checking rules are:

    The type of an identifier is the type appearing while declaring the variable.
    The type of TK_NUM is integer.
    The type of TK_RNUM is real.
    The type of an identifier of a record type expanded with a dot followed by the field name is same as that of the field.
    The type of a record type is a tuple (type of field1, type of field 2, type of field3,.......and so on). Example : Consider the following type definition 

record #circle

                type real : centre_x;

                type real: centre_y;

                type real: radius;

                type real: area;

endrecord;

The type of the above record is (real, real, real, real) (say T).
The type of a simple expression (say E) of the form expression(say E1) <operator> Expression(say E2) is

    integer, if both expressions are of type integer and the operator is arithmetic operator.
    real, if both the expressions are of type real and the operator is arithmetic operator.
    boolean, if both expressions are of type integer and the operator is relational operator.
    boolean, if both expressions are of type real and the operator is relational.
    boolean, if both expressions are of type boolean and the operator is logical.
    record type T if both E1 and E2 are of the same record type T.

The type of the expression is ERROR, if the above rules do not derive the type of E appropriately.

The type of an identifier or an expression is computed by traversing the abstract syntax tree.

Semantic Analyzer: This module verifies the semantics of the code.

    An identifier cannot be declared multiple times in the same scope.
    An identifier must be declared before its use.
    An identifier declared globally cannot be declared anywhere else in function definitions.
    The types and the number of parameters returned by a function must be the same as that of the parameters used in invoking the function.
    The parameters being returned by a function must be assigned a value. If a parameter does not get a value assigned within the function definition, it should be reported as an error.
    The function that does not return any value, must be invoked appropriately.
    The types of formal and actual parameters must be same.
    Number of actual parameters must be same as that of formal parameters.
    Function overloading is not allowed.
    The function cannot be invoked recursively.
    An identifier used beyond its scope must be viewed as undefined
    A record type definition is visible anywhere in the program.
    The right hand side expression of an assignment statement must be of the same type as that of the left hand side identifier.
    A function definition for a function being used (say F1) by another (say F2) must precede the definition of the function using it(i.e. F2).
    A while statement must redefine the variable that participates in the iterations. As an instance, consider the following example

while(c3<=c5)

write(c3);

c3<‐‐‐c3+2.34;

end

Code Generator : This module takes as input the abstract syntax tree (AST) as intermediate representation. The function generates 8086 assembly code. The task of code generation is made simpler with the following constraints on the given source code.

    Function  _main is the only function in the input source code.
    The input source code does not have function definitions.
    All other features of the language such as iterative and conditional constructs, all statement constructs, all types of variables (including records), expression evaluation etc. exist in the source code.
    Only trivial optimization such as avoiding redundant code, appropriate register usage etc are needed while the detailed code optimization techniques are not expected to be implemented.
