#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AST Node Types
typedef enum {
    NODE_PROGRAM,
    NODE_FUNCTION_DECL,
    NODE_VAR_DECL,
    NODE_PARAM,
    NODE_COMPOUND_STMT,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_RETURN_STMT,
    NODE_EXPR_STMT,
    NODE_ASSIGN,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNC_CALL,
    NODE_IDENTIFIER,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_PRINT_STMT,
    NODE_SCAN_STMT,
    NODE_STRING_LITERAL
} NodeType;

// Data types
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_VOID,
    TYPE_UNKNOWN
} DataType;

// AST Node Structure with line information
typedef struct ASTNode {
    NodeType type;
    char *name;
    DataType data_type;
    struct ASTNode **children;
    int child_count;
    int child_capacity;
    union {
        int int_val;
        float float_val;
        char *str_val;
    } value;
    int line;      // Line number for error reporting
    int column;    // Column number for error reporting
} ASTNode;

// Symbol Table Entry
typedef struct Symbol {
    char *name;
    DataType type;
    int is_function;
    int param_count;
    DataType *param_types;
    int line;      // Line where symbol was declared
    struct Symbol *next;
} Symbol;

// Symbol Table
typedef struct SymbolTable {
    Symbol *head;
    struct SymbolTable *parent;
} SymbolTable;

// Interpreter Variable
typedef struct {
    char *name;
    union {
        int int_val;
        float float_val;
    } value;
    DataType type;
} Variable;

// Variable List for runtime
typedef struct VarList {
    Variable var;
    struct VarList *next;
} VarList;

// Global variables
extern ASTNode *root;
extern SymbolTable *current_scope;
extern SymbolTable *global_scope;
extern int error_count;
extern char *current_filename;  // For error messages
extern int line_num;            // Current line number

// AST Functions
ASTNode *createNode(NodeType type, const char *name);
void addChild(ASTNode *parent, ASTNode *child);
void freeAST(ASTNode *node);
void printAST(ASTNode *node, int depth);
void exportASTtoJSON(ASTNode *node, FILE *fp, int indent);
const char *nodeTypeToString(NodeType type);

// Symbol Table Functions
SymbolTable *createSymbolTable(SymbolTable *parent);
void insertSymbol(SymbolTable *table, const char *name, DataType type, int is_function);
Symbol *lookupSymbol(SymbolTable *table, const char *name);
void printSymbolTable(SymbolTable *table);
void freeSymbolTable(SymbolTable *table);

// Semantic Analysis
void performSemanticAnalysis(ASTNode *node, SymbolTable *table);
DataType getExpressionType(ASTNode *node, SymbolTable *table);

// Interpreter Functions
void interpretProgram(ASTNode *node);
void interpretProgramWithTrace(ASTNode *node, FILE *trace_fp);
void executeStatement(ASTNode *node, VarList **vars);
void executeStatementWithTrace(ASTNode *node, VarList **vars);
int evaluateIntExpression(ASTNode *node, VarList *vars);
float evaluateFloatExpression(ASTNode *node, VarList *vars);
Variable *findVariable(VarList *vars, const char *name);
void setVariable(VarList **vars, const char *name, DataType type, int int_val, float float_val);

// Trace Functions
void enable_trace_output(FILE *fp);
void disable_trace_output(void);
void emit_trace(const char *type, const char *block, int line, const char *content, VarList *vars);

// Helper functions
char *processEscapes(const char *str);
void handlePrintf(const char *format, ASTNode **args, int arg_count, VarList *vars);
void handleScanf(const char *format, ASTNode **args, int arg_count, VarList **vars);

// Enhanced Error Reporting Functions
// ----------------------------- ERROR HANDLING ------------------------------

const char *type_to_string(DataType type);

/**
 * Report general compiler error (old GCC style, with line and column)
 */
void report_error(int line, int col, const char *error_type, const char *message);

/**
 * Report undeclared variable (with line and column)
 */
void report_undeclared_variable(const char *var_name, int line, int col);

/**
 * Report undeclared function (with line and column)
 */
void report_undeclared_function(const char *func_name, int line, int col);

/**
 * Report redeclaration (with line, column, and previous line)
 */
void report_redeclaration(const char *name, int line, int col, int prev_line, int is_function);

/**
 * Report type mismatch in binary operations
 */
void report_type_mismatch(const char *op, DataType left, DataType right, int line, int col);

/**
 * Report argument mismatch for function calls
 */
void report_argument_mismatch(const char *func_name, int expected, int provided, int line, int col);


// Error handling
void yyerror(const char *s);
void semantic_error(const char *msg);

// Type name conversion
const char *type_to_string(DataType type);

#endif
