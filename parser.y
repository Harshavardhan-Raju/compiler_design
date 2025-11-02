%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

extern int yylex();
extern int line_num;
extern FILE *yyin;
extern char *yytext;

ASTNode *root = NULL;
SymbolTable *current_scope = NULL;
SymbolTable *global_scope = NULL;
int error_count = 0;

void yyerror(const char *s) {
    fprintf(stderr, "\n%s:%d:1: \033[1;31merror:\033[0m %s\n", current_filename, line_num, s);
    fprintf(stderr, "    %s\n", s);
    error_count++;
}

void detailed_error(const char *error_msg, const char *note, const char *fix) {
    fprintf(stderr, "\n%s:%d:1: \033[1;31merror:\033[0m %s\n", current_filename, line_num, error_msg);
    if (note) {
        fprintf(stderr, "\033[1;36mnote:\033[0m %s\n", note);
    }
    if (fix) {
        fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n%s\n", fix);
    }
    error_count++;
}
%}

%union {
    int int_val;
    float float_val;
    char *str;
    struct ASTNode *node;
    int type;
}

%token <str> ID STRING
%token <int_val> INT_CONST
%token <float_val> FLOAT_CONST
%token INT FLOAT VOID
%token IF ELSE WHILE FOR RETURN PRINTF SCANF
%token PLUS MINUS MULT DIV MOD
%token EQ NE LT GT LE GE
%token AND OR NOT
%token ASSIGN SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE AMPERSAND

%type <node> program declaration_list declaration var_declaration function_declaration
%type <node> params param_list param compound_stmt stmt_list stmt
%type <node> expr_stmt selection_stmt iteration_stmt return_stmt print_stmt scan_stmt
%type <node> expr simple_expr additive_expr term factor call args arg_list
%type <type> type_specifier

%right ASSIGN
%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT UMINUS
%left LPAREN RPAREN

%error-verbose

%%

program:
    declaration_list {
        root = createNode(NODE_PROGRAM, "Program");
        addChild(root, $1);
        $$ = root;
    }
    ;

declaration_list:
    declaration_list declaration {
        $$ = $1;
        addChild($$, $2);
    }
    | declaration {
        $$ = createNode(NODE_COMPOUND_STMT, "DeclarationList");
        addChild($$, $1);
    }
    ;

declaration:
    var_declaration { $$ = $1; }
    | function_declaration { $$ = $1; }
    ;

var_declaration:
    type_specifier ID SEMICOLON {
        $$ = createNode(NODE_VAR_DECL, $2);
        $$->data_type = $1;
        free($2);
    }
    | type_specifier ID ASSIGN expr SEMICOLON {
        $$ = createNode(NODE_VAR_DECL, $2);
        $$->data_type = $1;
        addChild($$, $4);
        free($2);
    }
    | type_specifier ID error {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected ';' after variable declaration");
        snprintf(note, sizeof(note), "variable '%s' is missing semicolon terminator", $2);
        snprintf(fix, sizeof(fix), "    %s %s;  // add semicolon here", 
                 $1 == TYPE_INT ? "int" : ($1 == TYPE_FLOAT ? "float" : "void"), $2);
        detailed_error(msg, note, fix);
        yyerrok;
        $$ = createNode(NODE_VAR_DECL, $2);
        $$->data_type = $1;
        free($2);
    }
    | type_specifier ID ASSIGN expr error {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected ';' after initialization");
        snprintf(note, sizeof(note), "initialized variable '%s' is missing semicolon", $2);
        snprintf(fix, sizeof(fix), "    %s %s = <value>;  // add semicolon at the end", 
                 $1 == TYPE_INT ? "int" : ($1 == TYPE_FLOAT ? "float" : "void"), $2);
        detailed_error(msg, note, fix);
        yyerrok;
        $$ = createNode(NODE_VAR_DECL, $2);
        $$->data_type = $1;
        addChild($$, $4);
        free($2);
    }
    ;

type_specifier:
    INT { $$ = TYPE_INT; }
    | FLOAT { $$ = TYPE_FLOAT; }
    | VOID { $$ = TYPE_VOID; }
    ;

function_declaration:
    type_specifier ID LPAREN params RPAREN compound_stmt {
        $$ = createNode(NODE_FUNCTION_DECL, $2);
        $$->data_type = $1;
        addChild($$, $4);
        addChild($$, $6);
        free($2);
    }
    | type_specifier ID LPAREN params RPAREN error {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected function body after declaration");
        snprintf(note, sizeof(note), "function '%s' is missing opening brace '{'", $2);
        snprintf(fix, sizeof(fix), 
                 "    %s %s(...) {\n        // function body\n        return 0;\n    }", 
                 $1 == TYPE_INT ? "int" : ($1 == TYPE_FLOAT ? "float" : "void"), $2);
        detailed_error(msg, note, fix);
        yyerrok;
        $$ = createNode(NODE_FUNCTION_DECL, $2);
        $$->data_type = $1;
        addChild($$, $4);
        addChild($$, createNode(NODE_COMPOUND_STMT, "EmptyBlock"));
        free($2);
    }
    ;

params:
    param_list { $$ = $1; }
    | VOID {
        $$ = createNode(NODE_PARAM, "void");
        $$->data_type = TYPE_VOID;
    }
    | /* empty */ {
        $$ = createNode(NODE_PARAM, "empty");
    }
    ;

param_list:
    param_list COMMA param {
        $$ = $1;
        addChild($$, $3);
    }
    | param {
        $$ = createNode(NODE_COMPOUND_STMT, "ParamList");
        addChild($$, $1);
    }
    ;

param:
    type_specifier ID {
        $$ = createNode(NODE_PARAM, $2);
        $$->data_type = $1;
        free($2);
    }
    ;

compound_stmt:
    LBRACE stmt_list RBRACE { $$ = $2; }
    | LBRACE RBRACE {
        $$ = createNode(NODE_COMPOUND_STMT, "EmptyBlock");
    }
    | LBRACE error RBRACE {
        detailed_error("invalid statement in block", 
                      "syntax error inside braces",
                      "    {\n        // check for missing semicolons\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_COMPOUND_STMT, "ErrorBlock");
    }
    ;

stmt_list:
    stmt_list stmt {
        $$ = $1;
        addChild($$, $2);
    }
    | stmt {
        $$ = createNode(NODE_COMPOUND_STMT, "StmtList");
        addChild($$, $1);
    }
    ;

stmt:
    expr_stmt { $$ = $1; }
    | compound_stmt { $$ = $1; }
    | selection_stmt { $$ = $1; }
    | iteration_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    | print_stmt { $$ = $1; }
    | scan_stmt { $$ = $1; }
    | var_declaration { $$ = $1; }
    ;

expr_stmt:
    expr SEMICOLON {
        $$ = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild($$, $1);
    }
    | expr error {
        detailed_error("expected ';' after expression",
                      "expressions must be terminated with semicolon",
                      "    expression;  // add semicolon here");
        yyerrok;
        $$ = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild($$, $1);
    }
    | SEMICOLON {
        $$ = createNode(NODE_EXPR_STMT, "EmptyStmt");
    }
    ;

selection_stmt:
    IF LPAREN expr RPAREN stmt {
        $$ = createNode(NODE_IF_STMT, "If");
        addChild($$, $3);
        addChild($$, $5);
    }
    | IF LPAREN expr RPAREN stmt ELSE stmt {
        $$ = createNode(NODE_IF_STMT, "IfElse");
        addChild($$, $3);
        addChild($$, $5);
        addChild($$, $7);
    }
    | IF LPAREN expr error {
        detailed_error("expected ')' after if condition",
                      "if statement condition is not properly closed",
                      "    if (condition) {  // add closing parenthesis\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_IF_STMT, "If");
        addChild($$, $3);
        addChild($$, createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
    | IF error {
        detailed_error("expected '(' after 'if'",
                      "if keyword must be followed by opening parenthesis",
                      "    if (condition) {\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_IF_STMT, "If");
    }
    ;

iteration_stmt:
    WHILE LPAREN expr RPAREN stmt {
        $$ = createNode(NODE_WHILE_STMT, "While");
        addChild($$, $3);
        addChild($$, $5);
    }
    | WHILE LPAREN expr error {
        detailed_error("expected ')' after while condition",
                      "while loop condition is not properly closed",
                      "    while (condition) {  // add closing parenthesis\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_WHILE_STMT, "While");
        addChild($$, $3);
        addChild($$, createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
    | FOR LPAREN expr_stmt expr_stmt expr RPAREN stmt {
        $$ = createNode(NODE_FOR_STMT, "For");
        addChild($$, $3);
        addChild($$, $4);
        addChild($$, $5);
        addChild($$, $7);
    }
    | FOR LPAREN expr_stmt expr_stmt expr error {
        detailed_error("expected ')' after for loop header",
                      "for loop is missing closing parenthesis",
                      "    for (init; condition; increment) {  // add ')' here\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_FOR_STMT, "For");
        addChild($$, $3);
        addChild($$, $4);
        addChild($$, $5);
        addChild($$, createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
    | FOR error {
        detailed_error("expected '(' after 'for'",
                      "for keyword must be followed by opening parenthesis",
                      "    for (init; condition; increment) {\n        statement;\n    }");
        yyerrok;
        $$ = createNode(NODE_FOR_STMT, "For");
    }
    ;

return_stmt:
    RETURN SEMICOLON {
        $$ = createNode(NODE_RETURN_STMT, "Return");
    }
    | RETURN expr SEMICOLON {
        $$ = createNode(NODE_RETURN_STMT, "Return");
        addChild($$, $2);
    }
    | RETURN expr error {
        detailed_error("expected ';' after return statement",
                      "return statement must be terminated with semicolon",
                      "    return value;  // add semicolon here");
        yyerrok;
        $$ = createNode(NODE_RETURN_STMT, "Return");
        addChild($$, $2);
    }
    ;

print_stmt:
    PRINTF LPAREN STRING COMMA arg_list RPAREN SEMICOLON {
        $$ = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        addChild($$, $5);
        free($3);
    }
    | PRINTF LPAREN STRING RPAREN SEMICOLON {
        $$ = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        free($3);
    }
    | PRINTF LPAREN STRING COMMA arg_list RPAREN error {
        detailed_error("expected ';' after printf statement",
                      "printf must be terminated with semicolon",
                      "    printf(\"format\", args);  // add semicolon");
        yyerrok;
        $$ = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        addChild($$, $5);
        free($3);
    }
    | PRINTF LPAREN STRING RPAREN error {
        detailed_error("expected ';' after printf statement",
                      "printf must be terminated with semicolon",
                      "    printf(\"format\");  // add semicolon");
        yyerrok;
        $$ = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        free($3);
    }
    | PRINTF error {
        detailed_error("expected '(' after printf",
                      "printf requires format string in parentheses",
                      "    printf(\"format string\", args);");
        yyerrok;
        $$ = createNode(NODE_PRINT_STMT, "Printf");
    }
    ;

scan_stmt:
    SCANF LPAREN STRING COMMA arg_list RPAREN SEMICOLON {
        $$ = createNode(NODE_SCAN_STMT, "Scanf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        addChild($$, $5);
        free($3);
    }
    | SCANF LPAREN STRING COMMA arg_list RPAREN error {
        detailed_error("expected ';' after scanf statement",
                      "scanf must be terminated with semicolon",
                      "    scanf(\"format\", &var);  // add semicolon");
        yyerrok;
        $$ = createNode(NODE_SCAN_STMT, "Scanf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, $3);
        addChild($$, fmt);
        addChild($$, $5);
        free($3);
    }
    ;

expr:
    ID ASSIGN expr {
        $$ = createNode(NODE_ASSIGN, "=");
        ASTNode *id = createNode(NODE_IDENTIFIER, $1);
        addChild($$, id);
        addChild($$, $3);
        free($1);
    }
    | simple_expr { $$ = $1; }
    ;

simple_expr:
    simple_expr OR additive_expr {
        $$ = createNode(NODE_BINARY_OP, "||");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr AND additive_expr {
        $$ = createNode(NODE_BINARY_OP, "&&");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr EQ additive_expr {
        $$ = createNode(NODE_BINARY_OP, "==");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr NE additive_expr {
        $$ = createNode(NODE_BINARY_OP, "!=");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr LT additive_expr {
        $$ = createNode(NODE_BINARY_OP, "<");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr LE additive_expr {
        $$ = createNode(NODE_BINARY_OP, "<=");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr GT additive_expr {
        $$ = createNode(NODE_BINARY_OP, ">");
        addChild($$, $1);
        addChild($$, $3);
    }
    | simple_expr GE additive_expr {
        $$ = createNode(NODE_BINARY_OP, ">=");
        addChild($$, $1);
        addChild($$, $3);
    }
    | additive_expr { $$ = $1; }
    ;

additive_expr:
    additive_expr PLUS term {
        $$ = createNode(NODE_BINARY_OP, "+");
        addChild($$, $1);
        addChild($$, $3);
    }
    | additive_expr MINUS term {
        $$ = createNode(NODE_BINARY_OP, "-");
        addChild($$, $1);
        addChild($$, $3);
    }
    | term { $$ = $1; }
    ;

term:
    term MULT factor {
        $$ = createNode(NODE_BINARY_OP, "*");
        addChild($$, $1);
        addChild($$, $3);
    }
    | term DIV factor {
        $$ = createNode(NODE_BINARY_OP, "/");
        addChild($$, $1);
        addChild($$, $3);
    }
    | term MOD factor {
        $$ = createNode(NODE_BINARY_OP, "%");
        addChild($$, $1);
        addChild($$, $3);
    }
    | factor { $$ = $1; }
    ;

factor:
    LPAREN expr RPAREN { $$ = $2; }
    | ID {
        $$ = createNode(NODE_IDENTIFIER, $1);
        free($1);
    }
    | call { $$ = $1; }
    | INT_CONST {
        $$ = createNode(NODE_INT_LITERAL, "int");
        $$->value.int_val = $1;
        $$->data_type = TYPE_INT;
    }
    | FLOAT_CONST {
        $$ = createNode(NODE_FLOAT_LITERAL, "float");
        $$->value.float_val = $1;
        $$->data_type = TYPE_FLOAT;
    }
    | MINUS factor %prec UMINUS {
        $$ = createNode(NODE_UNARY_OP, "-");
        addChild($$, $2);
    }
    | NOT factor {
        $$ = createNode(NODE_UNARY_OP, "!");
        addChild($$, $2);
    }
    ;

call:
    ID LPAREN args RPAREN {
        $$ = createNode(NODE_FUNC_CALL, $1);
        addChild($$, $3);
        free($1);
    }
    | ID LPAREN RPAREN {
        $$ = createNode(NODE_FUNC_CALL, $1);
        ASTNode *empty_args = createNode(NODE_COMPOUND_STMT, "EmptyArgs");
        addChild($$, empty_args);
        free($1);
    }
    | ID LPAREN error RPAREN {
        char msg[512];
        snprintf(msg, sizeof(msg), "invalid argument list for function '%s'", $1);
        detailed_error(msg, 
                      "check for syntax errors in function arguments",
                      "    function(arg1, arg2);  // comma-separated arguments");
        yyerrok;
        $$ = createNode(NODE_FUNC_CALL, $1);
        addChild($$, createNode(NODE_COMPOUND_STMT, "EmptyArgs"));
        free($1);
    }
    ;

args:
    arg_list { $$ = $1; }
    ;

arg_list:
    arg_list COMMA expr {
        $$ = $1;
        addChild($$, $3);
    }
    | expr {
        $$ = createNode(NODE_COMPOUND_STMT, "ArgList");
        addChild($$, $1);
    }
    | AMPERSAND ID {
        $$ = createNode(NODE_COMPOUND_STMT, "ArgList");
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, $2);
        addChild(ref, id);
        addChild($$, ref);
        free($2);
    }
    | arg_list COMMA AMPERSAND ID {
        $$ = $1;
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, $4);
        addChild(ref, id);
        addChild($$, ref);
        free($4);
    }
    ;

%%