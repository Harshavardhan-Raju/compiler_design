/**
 * compiler.c - Enhanced Mini C Compiler with Full Loop Support
 * 
 * New Features:
 * - Fixed while and for loop execution
 * - Proper variable update in loop iterations
 * - Enhanced GCC-style colored error messages
 * - All previous functionality preserved
 */

#include "compiler.h"

// Global filename for error reporting
char *current_filename = "input.c";

// ============================================================================
// ENHANCED ERROR REPORTING SYSTEM WITH COLORS
// ============================================================================

/**
 * Convert DataType to string for error messages
 */
const char *type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_VOID: return "void";
        case TYPE_UNKNOWN: return "unknown";
        default: return "unknown";
    }
}

/**
 * Report error in GCC style: filename:line:column: error: message
 */
void report_error(int line, int col, const char *error_type, const char *message) {
    fprintf(stderr, "\n%s:%d:%d: \033[1;31m%s:\033[0m %s\n", 
            current_filename, line, col, error_type, message);
    error_count++;
}

/**
 * Add a suggested fix note
 */
void suggest_fix(const char *suggestion) {
    fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
    fprintf(stderr, "    %s\n", suggestion);
}

/**
 * Report undeclared variable with helpful suggestion
 */
void report_undeclared_variable(const char *var_name, int line, int col) {
    char msg[512];
    snprintf(msg, sizeof(msg), "use of undeclared identifier '%s'", var_name);
    report_error(line, col, "error", msg);
    
    fprintf(stderr, "\033[1;36mnote:\033[0m variables must be declared before use\n");
    suggest_fix("Declare the variable before using it:");
    fprintf(stderr, "        int %s = 0;  // for integer variable\n", var_name);
    fprintf(stderr, "        float %s = 0.0;  // for floating-point variable\n", var_name);
}

/**
 * Report undeclared function with helpful suggestion
 */
void report_undeclared_function(const char *func_name, int line, int col) {
    char msg[512];
    snprintf(msg, sizeof(msg), "implicit declaration of function '%s'", func_name);
    report_error(line, col, "error", msg);
    
    fprintf(stderr, "\033[1;36mnote:\033[0m functions must be declared before calling them\n");
    suggest_fix("Define the function before main():");
    fprintf(stderr, "        int %s(int param) {\n", func_name);
    fprintf(stderr, "            // function body\n");
    fprintf(stderr, "            return 0;\n");
    fprintf(stderr, "        }\n");
}

/**
 * Report redeclaration error with previous location
 */
void report_redeclaration(const char *name, int line, int col, int prev_line, int is_function) {
    char msg[512];
    snprintf(msg, sizeof(msg), "redefinition of '%s'", name);
    report_error(line, col, "error", msg);
    
    fprintf(stderr, "\033[1;36mnote:\033[0m previous %s was at line %d\n", 
            is_function ? "definition" : "declaration", prev_line);
    
    if (is_function) {
        suggest_fix("Remove the duplicate function or rename it:");
        fprintf(stderr, "        int %s_v2() { ... }  // use different name\n", name);
    } else {
        suggest_fix("Remove the duplicate declaration or use the existing variable:");
        fprintf(stderr, "        %s = value;  // just assign to existing variable\n", name);
    }
}

/**
 * Report type mismatch in operations
 */
void report_type_mismatch(const char *op, DataType left, DataType right, int line, int col) {
    char msg[512];
    snprintf(msg, sizeof(msg), "invalid operands to binary '%s' ('%s' and '%s')", 
             op, type_to_string(left), type_to_string(right));
    report_error(line, col, "error", msg);
    
    fprintf(stderr, "\033[1;36mnote:\033[0m cannot perform operation on incompatible types\n");
    
    if (left == TYPE_INT && right == TYPE_FLOAT) {
        suggest_fix("Cast one operand to match the other:");
        fprintf(stderr, "        (float)int_var %s float_var  // cast int to float\n", op);
    } else if (left == TYPE_FLOAT && right == TYPE_INT) {
        suggest_fix("Cast one operand to match the other:");
        fprintf(stderr, "        float_var %s (float)int_var  // cast int to float\n", op);
    } else {
        suggest_fix("Ensure both operands are of compatible numeric types");
    }
}

/**
 * Report function argument count mismatch
 */
void report_argument_mismatch(const char *func_name, int expected, int provided, int line, int col) {
    char msg[512];
    if (provided < expected) {
        snprintf(msg, sizeof(msg), "too few arguments to function '%s'", func_name);
    } else {
        snprintf(msg, sizeof(msg), "too many arguments to function '%s'", func_name);
    }
    report_error(line, col, "error", msg);
    
    fprintf(stderr, "\033[1;36mnote:\033[0m function expects %d argument%s, %d provided\n", 
            expected, expected == 1 ? "" : "s", provided);
    
    suggest_fix("Provide the correct number of arguments:");
    fprintf(stderr, "        %s(", func_name);
    for (int i = 0; i < expected; i++) {
        fprintf(stderr, "arg%d", i + 1);
        if (i < expected - 1) fprintf(stderr, ", ");
    }
    fprintf(stderr, ");  // %d argument%s\n", expected, expected == 1 ? "" : "s");
}

// ============================================================================
// CALL STACK MANAGEMENT FOR RECURSION
// ============================================================================

#define MAX_CALL_DEPTH 1000
#define MAX_LOCALS 100

typedef struct StackFrame {
    char function_name[256];
    VarList *local_vars;
    int return_value_set;
    union {
        int int_val;
        float float_val;
    } return_value;
    DataType return_type;
    struct StackFrame *next;
} StackFrame;

static StackFrame *call_stack_top = NULL;
static int current_depth = 0;
static ASTNode *global_program_root = NULL;

StackFrame *pushStackFrame(const char *func_name) {
    if (current_depth >= MAX_CALL_DEPTH) {
        fprintf(stderr, "\n%s:runtime: \033[1;31merror:\033[0m stack overflow - maximum recursion depth exceeded\n", 
                current_filename);
        fprintf(stderr, "\033[1;36mnote:\033[0m recursion depth limit is %d calls\n", MAX_CALL_DEPTH);
        fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
        fprintf(stderr, "    Check function '%s' for infinite recursion\n", func_name);
        fprintf(stderr, "    Ensure base case is reachable: if (n <= 0) return 1;\n");
        exit(1);
    }
    
    StackFrame *frame = (StackFrame *)malloc(sizeof(StackFrame));
    if (!frame) {
        fprintf(stderr, "fatal error: memory allocation failed\n");
        exit(1);
    }
    
    strncpy(frame->function_name, func_name, 255);
    frame->function_name[255] = '\0';
    frame->local_vars = NULL;
    frame->return_value_set = 0;
    frame->return_value.int_val = 0;
    frame->return_type = TYPE_INT;
    frame->next = call_stack_top;
    
    call_stack_top = frame;
    current_depth++;
    
    return frame;
}

void popStackFrame() {
    if (!call_stack_top) {
        fprintf(stderr, "internal error: attempted to pop empty call stack\n");
        return;
    }
    
    StackFrame *frame = call_stack_top;
    call_stack_top = frame->next;
    current_depth--;
    
    VarList *var = frame->local_vars;
    while (var) {
        VarList *next = var->next;
        free(var->var.name);
        free(var);
        var = next;
    }
    
    free(frame);
}

StackFrame *getCurrentFrame() {
    return call_stack_top;
}

// ============================================================================
// AST MANAGEMENT FUNCTIONS
// ============================================================================

ASTNode *createNode(NodeType type, const char *name) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "fatal error: memory allocation failed for AST node\n");
        exit(1);
    }
    
    node->type = type;
    node->name = name ? strdup(name) : NULL;
    node->data_type = TYPE_UNKNOWN;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    node->value.int_val = 0;
    node->line = line_num;
    node->column = 0;
    
    return node;
}

void addChild(ASTNode *parent, ASTNode *child) {
    if (!parent) return;
    
    if (parent->child_count >= parent->child_capacity) {
        parent->child_capacity = (parent->child_capacity == 0) ? 4 : parent->child_capacity * 2;
        parent->children = (ASTNode **)realloc(parent->children, 
                                               parent->child_capacity * sizeof(ASTNode *));
        if (!parent->children) {
            fprintf(stderr, "fatal error: memory reallocation failed\n");
            exit(1);
        }
    }
    
    parent->children[parent->child_count++] = child;
}

void freeAST(ASTNode *node) {
    if (!node) return;
    
    for (int i = 0; i < node->child_count; i++) {
        freeAST(node->children[i]);
    }
    
    free(node->children);
    free(node->name);
    free(node);
}

const char *nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_PROGRAM: return "Program";
        case NODE_FUNCTION_DECL: return "FunctionDecl";
        case NODE_VAR_DECL: return "VarDecl";
        case NODE_PARAM: return "Param";
        case NODE_COMPOUND_STMT: return "CompoundStmt";
        case NODE_IF_STMT: return "IfStmt";
        case NODE_WHILE_STMT: return "WhileStmt";
        case NODE_FOR_STMT: return "ForStmt";
        case NODE_RETURN_STMT: return "ReturnStmt";
        case NODE_EXPR_STMT: return "ExprStmt";
        case NODE_ASSIGN: return "Assignment";
        case NODE_BINARY_OP: return "BinaryOp";
        case NODE_UNARY_OP: return "UnaryOp";
        case NODE_FUNC_CALL: return "FuncCall";
        case NODE_IDENTIFIER: return "Identifier";
        case NODE_INT_LITERAL: return "IntLiteral";
        case NODE_FLOAT_LITERAL: return "FloatLiteral";
        case NODE_PRINT_STMT: return "PrintStmt";
        case NODE_SCAN_STMT: return "ScanStmt";
        case NODE_STRING_LITERAL: return "StringLiteral";
        default: return "Unknown";
    }
}

void printAST(ASTNode *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) printf("  ");
    
    printf("%s", nodeTypeToString(node->type));
    if (node->name) printf(" (%s)", node->name);
    if (node->type == NODE_INT_LITERAL) printf(" [%d]", node->value.int_val);
    if (node->type == NODE_FLOAT_LITERAL) printf(" [%f]", node->value.float_val);
    printf("\n");
    
    for (int i = 0; i < node->child_count; i++) {
        printAST(node->children[i], depth + 1);
    }
}

void exportASTtoJSON(ASTNode *node, FILE *fp, int indent) {
    if (!node) {
        fprintf(fp, "null");
        return;
    }
    
    fprintf(fp, "{\n");
    
    for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
    fprintf(fp, "\"type\": \"%s\"", nodeTypeToString(node->type));
    
    if (node->type == NODE_BINARY_OP || node->type == NODE_UNARY_OP) {
        if (node->name) {
            fprintf(fp, ",\n");
            for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
            fprintf(fp, "\"operator\": \"%s\"", node->name);
        }
    } else {
        if (node->name && node->name[0] != '"') {
            fprintf(fp, ",\n");
            for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
            fprintf(fp, "\"name\": \"%s\"", node->name);
        }
    }
    
    if (node->type == NODE_INT_LITERAL) {
        fprintf(fp, ",\n");
        for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
        fprintf(fp, "\"value\": %d", node->value.int_val);
    } else if (node->type == NODE_FLOAT_LITERAL) {
        fprintf(fp, ",\n");
        for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
        fprintf(fp, "\"value\": %f", node->value.float_val);
    }
    
    if (node->child_count > 0) {
        fprintf(fp, ",\n");
        for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
        fprintf(fp, "\"children\": [\n");
        
        for (int i = 0; i < node->child_count; i++) {
            for (int j = 0; j <= indent + 1; j++) fprintf(fp, "  ");
            exportASTtoJSON(node->children[i], fp, indent + 1);
            if (i < node->child_count - 1) fprintf(fp, ",");
            fprintf(fp, "\n");
        }
        
        for (int i = 0; i <= indent; i++) fprintf(fp, "  ");
        fprintf(fp, "]");
    }
    
    fprintf(fp, "\n");
    for (int i = 0; i < indent; i++) fprintf(fp, "  ");
    fprintf(fp, "}");
}

// ============================================================================
// SYMBOL TABLE MANAGEMENT
// ============================================================================

SymbolTable *createSymbolTable(SymbolTable *parent) {
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "fatal error: memory allocation failed for symbol table\n");
        exit(1);
    }
    
    table->head = NULL;
    table->parent = parent;
    return table;
}

void insertSymbol(SymbolTable *table, const char *name, DataType type, int is_function) {
    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) {
        fprintf(stderr, "fatal error: memory allocation failed for symbol\n");
        exit(1);
    }
    
    sym->name = strdup(name);
    sym->type = type;
    sym->is_function = is_function;
    sym->param_count = 0;
    sym->param_types = NULL;
    sym->line = line_num;
    sym->next = table->head;
    table->head = sym;
}

Symbol *lookupSymbol(SymbolTable *table, const char *name) {
    while (table) {
        Symbol *sym = table->head;
        while (sym) {
            if (strcmp(sym->name, name) == 0) {
                return sym;
            }
            sym = sym->next;
        }
        table = table->parent;
    }
    return NULL;
}

void printSymbolTable(SymbolTable *table) {
    printf("\n=== Symbol Table ===\n");
    Symbol *sym = table->head;
    while (sym) {
        const char *type_str = type_to_string(sym->type);
        printf("Name: %-15s Type: %-6s IsFunction: %d Line: %d\n", 
               sym->name, type_str, sym->is_function, sym->line);
        sym = sym->next;
    }
    printf("====================\n\n");
}

void freeSymbolTable(SymbolTable *table) {
    if (!table) return;
    
    Symbol *sym = table->head;
    while (sym) {
        Symbol *next = sym->next;
        free(sym->name);
        free(sym->param_types);
        free(sym);
        sym = next;
    }
    free(table);
}

// ============================================================================
// ENHANCED SEMANTIC ANALYSIS
// ============================================================================

void semantic_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    error_count++;
}

void performSemanticAnalysis(ASTNode *node, SymbolTable *table) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_FUNCTION_DECL: {
            Symbol *existing = table->head;
            while (existing) {
                if (strcmp(existing->name, node->name) == 0 && existing->is_function) {
                    report_redeclaration(node->name, node->line, node->column, 
                                       existing->line, 1);
                    return;
                }
                existing = existing->next;
            }
            
            insertSymbol(table, node->name, node->data_type, 1);
            
            SymbolTable *func_scope = createSymbolTable(table);
            
            if (node->child_count > 0) {
                ASTNode *params = node->children[0];
                
                if (params->type == NODE_COMPOUND_STMT) {
                    for (int i = 0; i < params->child_count; i++) {
                        ASTNode *param = params->children[i];
                        if (param->type == NODE_PARAM && param->name && 
                            strcmp(param->name, "void") != 0 && 
                            strcmp(param->name, "empty") != 0) {
                            insertSymbol(func_scope, param->name, param->data_type, 0);
                        }
                    }
                } else if (params->type == NODE_PARAM && params->name && 
                          strcmp(params->name, "void") != 0 && 
                          strcmp(params->name, "empty") != 0) {
                    insertSymbol(func_scope, params->name, params->data_type, 0);
                }
            }
            
            if (node->child_count > 1) {
                performSemanticAnalysis(node->children[1], func_scope);
            }
            
            freeSymbolTable(func_scope);
            return;
        }
            
        case NODE_VAR_DECL: {
            Symbol *sym = table->head;
            while (sym) {
                if (strcmp(sym->name, node->name) == 0 && !sym->is_function) {
                    report_redeclaration(node->name, node->line, node->column, 
                                       sym->line, 0);
                    break;
                }
                sym = sym->next;
            }
            
            insertSymbol(table, node->name, node->data_type, 0);
            
            if (node->child_count > 0) {
                performSemanticAnalysis(node->children[0], table);
            }
            return;
        }
            
        case NODE_IDENTIFIER: {
            if (node->name && node->name[0] == '"') break;
            
            if (!lookupSymbol(table, node->name)) {
                report_undeclared_variable(node->name, node->line, node->column);
            }
            break;
        }
        
        case NODE_FUNC_CALL: {
            Symbol *func = lookupSymbol(table, node->name);
            if (!func) {
                report_undeclared_function(node->name, node->line, node->column);
            } else if (!func->is_function) {
                char msg[512];
                snprintf(msg, sizeof(msg), "'%s' is not a function", node->name);
                report_error(node->line, node->column, "error", msg);
                fprintf(stderr, "\033[1;36mnote:\033[0m '%s' was declared as a variable at line %d\n", 
                       node->name, func->line);
                suggest_fix("Use a function name, or remove parentheses to access the variable");
            }
            
            if (node->child_count > 0) {
                performSemanticAnalysis(node->children[0], table);
            }
            break;
        }
        
        case NODE_PRINT_STMT:
        case NODE_SCAN_STMT:
            for (int i = 1; i < node->child_count; i++) {
                performSemanticAnalysis(node->children[i], table);
            }
            return;
            
        case NODE_COMPOUND_STMT: {
            SymbolTable *block_scope = createSymbolTable(table);
            for (int i = 0; i < node->child_count; i++) {
                performSemanticAnalysis(node->children[i], block_scope);
            }
            freeSymbolTable(block_scope);
            return;
        }
            
        default:
            break;
    }
    
    for (int i = 0; i < node->child_count; i++) {
        performSemanticAnalysis(node->children[i], table);
    }
}

// ============================================================================
// PRINTF/SCANF HANDLERS
// ============================================================================

void handlePrintf(const char *format, ASTNode **args, int arg_count, VarList *vars) {
    const char *p = format;
    int arg_index = 0;
    
    while (*p) {
        if (*p == '%' && *(p + 1)) {
            p++;
            switch (*p) {
                case '%':
                    printf("%%");
                    break;
                case 'd':
                    if (arg_index < arg_count) {
                        int val = evaluateIntExpression(args[arg_index++], vars);
                        printf("%d", val);
                    }
                    break;
                case 'f':
                    if (arg_index < arg_count) {
                        float val = evaluateFloatExpression(args[arg_index++], vars);
                        printf("%f", val);
                    }
                    break;
                case 'c':
                    if (arg_index < arg_count) {
                        int val = evaluateIntExpression(args[arg_index++], vars);
                        printf("%c", (char)val);
                    }
                    break;
                case 's':
                    if (arg_index < arg_count) {
                        if (args[arg_index]->type == NODE_IDENTIFIER) {
                            printf("%s", args[arg_index]->name);
                        }
                        arg_index++;
                    }
                    break;
                default:
                    printf("%%%c", *p);
                    break;
            }
            p++;
        } else {
            printf("%c", *p++);
        }
    }
}

void handleScanf(const char *format, ASTNode **args, int arg_count, VarList **vars) {
    const char *p = format;
    int arg_index = 0;
    
    while (*p) {
        if (*p == '%' && *(p + 1)) {
            p++;
            
            if (*p == 'd' && arg_index < arg_count) {
                ASTNode *arg = args[arg_index++];
                if (arg->type == NODE_UNARY_OP && strcmp(arg->name, "&") == 0) {
                    ASTNode *id = arg->children[0];
                    int val;
                    if (scanf("%d", &val) == 1) {
                        setVariable(vars, id->name, TYPE_INT, val, 0.0);
                    }
                }
            } else if (*p == 'f' && arg_index < arg_count) {
                ASTNode *arg = args[arg_index++];
                if (arg->type == NODE_UNARY_OP && strcmp(arg->name, "&") == 0) {
                    ASTNode *id = arg->children[0];
                    float val;
                    if (scanf("%f", &val) == 1) {
                        setVariable(vars, id->name, TYPE_FLOAT, 0, val);
                    }
                }
            }
            p++;
        } else {
            p++;
        }
    }
}

// ============================================================================
// INTERPRETER: VARIABLE MANAGEMENT
// ============================================================================

Variable *findVariable(VarList *vars, const char *name) {
    StackFrame *frame = getCurrentFrame();
    if (frame) {
        VarList *local = frame->local_vars;
        while (local) {
            if (strcmp(local->var.name, name) == 0) {
                return &local->var;
            }
            local = local->next;
        }
    }
    
    while (vars) {
        if (strcmp(vars->var.name, name) == 0) {
            return &vars->var;
        }
        vars = vars->next;
    }
    
    return NULL;
}

void setVariable(VarList **vars, const char *name, DataType type, int int_val, float float_val) {
    StackFrame *frame = getCurrentFrame();
    
    if (frame) {
        Variable *v = findVariable(frame->local_vars, name);
        if (v) {
            v->type = type;
            if (type == TYPE_INT) v->value.int_val = int_val;
            else v->value.float_val = float_val;
            return;
        }
        
        VarList *new_var = (VarList *)malloc(sizeof(VarList));
        new_var->var.name = strdup(name);
        new_var->var.type = type;
        if (type == TYPE_INT) new_var->var.value.int_val = int_val;
        else new_var->var.value.float_val = float_val;
        new_var->next = frame->local_vars;
        frame->local_vars = new_var;
        return;
    }
    
    Variable *v = findVariable(*vars, name);
    if (v) {
        v->type = type;
        if (type == TYPE_INT) v->value.int_val = int_val;
        else v->value.float_val = float_val;
    } else {
        VarList *new_var = (VarList *)malloc(sizeof(VarList));
        new_var->var.name = strdup(name);
        new_var->var.type = type;
        if (type == TYPE_INT) new_var->var.value.int_val = int_val;
        else new_var->var.value.float_val = float_val;
        new_var->next = *vars;
        *vars = new_var;
    }
}

// ============================================================================
// INTERPRETER: FUNCTION EXECUTION
// ============================================================================

void executeStatement(ASTNode *node, VarList **vars);
int evaluateIntExpression(ASTNode *node, VarList *vars);
float evaluateFloatExpression(ASTNode *node, VarList *vars);

ASTNode *findFunction(ASTNode *program, const char *name) {
    if (!program || program->type != NODE_PROGRAM) return NULL;
    if (program->child_count == 0) return NULL;
    
    ASTNode *decl_list = program->children[0];
    for (int i = 0; i < decl_list->child_count; i++) {
        ASTNode *decl = decl_list->children[i];
        if (decl->type == NODE_FUNCTION_DECL && strcmp(decl->name, name) == 0) {
            return decl;
        }
    }
    return NULL;
}

int executeFunction(const char *func_name, VarList *args, ASTNode *program) {
    ASTNode *func = findFunction(program, func_name);
    if (!func || func->child_count < 2) {
        fprintf(stderr, "\n%s:runtime: \033[1;31merror:\033[0m function '%s' not found or incomplete\n", 
                current_filename, func_name);
        fprintf(stderr, "\033[1;36mnote:\033[0m ensure function is defined with a body\n");
        fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
        fprintf(stderr, "    int %s() {\n", func_name);
        fprintf(stderr, "        // function body\n");
        fprintf(stderr, "        return 0;\n");
        fprintf(stderr, "    }\n");
        return 0;
    }
    
    StackFrame *frame = pushStackFrame(func_name);
    
    ASTNode *params = func->children[0];
    ASTNode *body = func->children[1];
    
    if (params->type == NODE_COMPOUND_STMT) {
        VarList *arg_ptr = args;
        for (int i = 0; i < params->child_count && arg_ptr; i++) {
            ASTNode *param = params->children[i];
            if (param->type == NODE_PARAM && param->name && 
                strcmp(param->name, "void") != 0 && strcmp(param->name, "empty") != 0) {
                
                VarList *new_var = (VarList *)malloc(sizeof(VarList));
                new_var->var.name = strdup(param->name);
                new_var->var.type = arg_ptr->var.type;
                if (arg_ptr->var.type == TYPE_INT) {
                    new_var->var.value.int_val = arg_ptr->var.value.int_val;
                } else {
                    new_var->var.value.float_val = arg_ptr->var.value.float_val;
                }
                new_var->next = frame->local_vars;
                frame->local_vars = new_var;
                
                arg_ptr = arg_ptr->next;
            }
        }
    } else if (params->type == NODE_PARAM && params->name && 
               strcmp(params->name, "void") != 0 && 
               strcmp(params->name, "empty") != 0 && args) {
        VarList *new_var = (VarList *)malloc(sizeof(VarList));
        new_var->var.name = strdup(params->name);
        new_var->var.type = args->var.type;
        if (args->var.type == TYPE_INT) {
            new_var->var.value.int_val = args->var.value.int_val;
        } else {
            new_var->var.value.float_val = args->var.value.float_val;
        }
        new_var->next = frame->local_vars;
        frame->local_vars = new_var;
    }
    
    int return_value = 0;
    for (int i = 0; i < body->child_count; i++) {
        if (body->children[i]->type == NODE_RETURN_STMT) {
            if (body->children[i]->child_count > 0) {
                return_value = evaluateIntExpression(body->children[i]->children[0], NULL);
            }
            frame->return_value_set = 1;
            frame->return_value.int_val = return_value;
            break;
        }
        
        executeStatement(body->children[i], NULL);
        
        if (frame->return_value_set) {
            return_value = frame->return_value.int_val;
            break;
        }
    }
    
    popStackFrame();
    
    return return_value;
}

// ============================================================================
// INTERPRETER: EXPRESSION EVALUATION
// ============================================================================

int evaluateIntExpression(ASTNode *node, VarList *vars) {
    if (!node) return 0;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            return node->value.int_val;
            
        case NODE_IDENTIFIER: {
            Variable *v = findVariable(vars, node->name);
            if (v) {
                if (v->type == TYPE_INT) return v->value.int_val;
                if (v->type == TYPE_FLOAT) return (int)v->value.float_val;
            }
            return 0;
        }
        
        case NODE_FUNC_CALL: {
            if (!global_program_root) {
                fprintf(stderr, "\n%s:runtime: \033[1;31merror:\033[0m cannot call function '%s' - no program context\n", 
                        current_filename, node->name);
                return 0;
            }
            
            VarList *arg_vals = NULL;
            
            if (node->child_count > 0) {
                ASTNode *args = node->children[0];
                
                if (args->type == NODE_COMPOUND_STMT && args->name && 
                    strcmp(args->name, "EmptyArgs") == 0) {
                    // No arguments
                } else {
                    for (int i = 0; i < args->child_count; i++) {
                        int val = evaluateIntExpression(args->children[i], vars);
                        
                        VarList *new_arg = (VarList *)malloc(sizeof(VarList));
                        new_arg->var.name = strdup("arg");
                        new_arg->var.type = TYPE_INT;
                        new_arg->var.value.int_val = val;
                        new_arg->next = arg_vals;
                        arg_vals = new_arg;
                    }
                    
                    VarList *reversed = NULL;
                    while (arg_vals) {
                        VarList *temp = arg_vals;
                        arg_vals = arg_vals->next;
                        temp->next = reversed;
                        reversed = temp;
                    }
                    arg_vals = reversed;
                }
            }
            
            int result = executeFunction(node->name, arg_vals, global_program_root);
            
            while (arg_vals) {
                VarList *temp = arg_vals;
                arg_vals = arg_vals->next;
                free(temp->var.name);
                free(temp);
            }
            
            return result;
        }
        
        case NODE_BINARY_OP: {
            int left = evaluateIntExpression(node->children[0], vars);
            int right = evaluateIntExpression(node->children[1], vars);
            
            if (strcmp(node->name, "+") == 0) return left + right;
            if (strcmp(node->name, "-") == 0) return left - right;
            if (strcmp(node->name, "*") == 0) return left * right;
            if (strcmp(node->name, "/") == 0) {
                if (right == 0) {
                    fprintf(stderr, "\n%s:%d:%d: \033[1;31merror:\033[0m division by zero\n", 
                            current_filename, node->line, node->column);
                    fprintf(stderr, "\033[1;36mnote:\033[0m the divisor evaluated to zero\n");
                    fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
                    fprintf(stderr, "    if (divisor != 0) {\n");
                    fprintf(stderr, "        result = numerator / divisor;\n");
                    fprintf(stderr, "    }\n");
                    return 0;
                }
                return left / right;
            }
            if (strcmp(node->name, "%") == 0) {
                if (right == 0) {
                    fprintf(stderr, "\n%s:%d:%d: \033[1;31merror:\033[0m modulo by zero\n", 
                            current_filename, node->line, node->column);
                    fprintf(stderr, "\033[1;36mnote:\033[0m the divisor evaluated to zero\n");
                    fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
                    fprintf(stderr, "    if (divisor != 0) {\n");
                    fprintf(stderr, "        result = numerator %% divisor;\n");
                    fprintf(stderr, "    }\n");
                    return 0;
                }
                return left % right;
            }
            if (strcmp(node->name, "==") == 0) return left == right;
            if (strcmp(node->name, "!=") == 0) return left != right;
            if (strcmp(node->name, "<") == 0) return left < right;
            if (strcmp(node->name, ">") == 0) return left > right;
            if (strcmp(node->name, "<=") == 0) return left <= right;
            if (strcmp(node->name, ">=") == 0) return left >= right;
            if (strcmp(node->name, "&&") == 0) return left && right;
            if (strcmp(node->name, "||") == 0) return left || right;
            return 0;
        }
        
        case NODE_UNARY_OP:
            if (strcmp(node->name, "-") == 0) {
                return -evaluateIntExpression(node->children[0], vars);
            }
            if (strcmp(node->name, "!") == 0) {
                return !evaluateIntExpression(node->children[0], vars);
            }
            return 0;
            
        default:
            return 0;
    }
}

float evaluateFloatExpression(ASTNode *node, VarList *vars) {
    if (!node) return 0.0;
    
    switch (node->type) {
        case NODE_FLOAT_LITERAL:
            return node->value.float_val;
            
        case NODE_INT_LITERAL:
            return (float)node->value.int_val;
            
        case NODE_IDENTIFIER: {
            Variable *v = findVariable(vars, node->name);
            if (v) {
                if (v->type == TYPE_FLOAT) return v->value.float_val;
                if (v->type == TYPE_INT) return (float)v->value.int_val;
            }
            return 0.0;
        }
        
        case NODE_BINARY_OP: {
            float left = evaluateFloatExpression(node->children[0], vars);
            float right = evaluateFloatExpression(node->children[1], vars);
            
            if (strcmp(node->name, "+") == 0) return left + right;
            if (strcmp(node->name, "-") == 0) return left - right;
            if (strcmp(node->name, "*") == 0) return left * right;
            if (strcmp(node->name, "/") == 0) {
                if (right == 0.0) {
                    fprintf(stderr, "\n%s:%d:%d: \033[1;31merror:\033[0m division by zero (float)\n", 
                            current_filename, node->line, node->column);
                    fprintf(stderr, "\033[1;36mnote:\033[0m the divisor evaluated to zero\n");
                    fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
                    fprintf(stderr, "    if (divisor != 0.0) result = numerator / divisor;\n");
                    return 0.0;
                }
                return left / right;
            }
            return 0.0;
        }
        
        case NODE_UNARY_OP:
            if (strcmp(node->name, "-") == 0) {
                return -evaluateFloatExpression(node->children[0], vars);
            }
            return 0.0;
        
        default:
            return 0.0;
    }
}

// ============================================================================
// INTERPRETER: STATEMENT EXECUTION WITH FIXED LOOP SUPPORT
// ============================================================================

void executeStatement(ASTNode *node, VarList **vars) {
    if (!node) return;
    
    StackFrame *frame = getCurrentFrame();
    VarList *current_vars = vars ? *vars : NULL;
    
    switch (node->type) {
        case NODE_VAR_DECL:
            if (node->child_count > 0) {
                int val = evaluateIntExpression(node->children[0], current_vars);
                setVariable(vars, node->name, node->data_type, val, 0.0);
            } else {
                setVariable(vars, node->name, node->data_type, 0, 0.0);
            }
            break;
            
        case NODE_ASSIGN: {
            ASTNode *id = node->children[0];
            ASTNode *expr = node->children[1];
            int val = evaluateIntExpression(expr, current_vars);
            setVariable(vars, id->name, TYPE_INT, val, 0.0);
            break;
        }
        
        case NODE_EXPR_STMT:
            for (int i = 0; i < node->child_count; i++) {
                ASTNode *child = node->children[i];
                if (child->type == NODE_ASSIGN) {
                    executeStatement(child, vars);
                    current_vars = vars ? *vars : NULL; // Update after assignment
                } else {
                    evaluateIntExpression(child, current_vars);
                }
            }
            break;
        
        case NODE_IF_STMT: {
            int cond = evaluateIntExpression(node->children[0], current_vars);
            if (cond) {
                executeStatement(node->children[1], vars);
            } else if (node->child_count > 2) {
                executeStatement(node->children[2], vars);
            }
            break;
        }
        
        case NODE_WHILE_STMT: {
            while (1) {
                current_vars = vars ? *vars : NULL;
                int cond = evaluateIntExpression(node->children[0], current_vars);
                if (!cond) break;
                
                executeStatement(node->children[1], vars);
                if (frame && frame->return_value_set) break;
            }
            break;
        }
        
        case NODE_FOR_STMT: {
            // Initialize (first child)
            executeStatement(node->children[0], vars);
            
            // Loop: condition (second child), body (fourth child), increment (third child)
            while (1) {
                // Update current_vars
                current_vars = vars ? *vars : NULL;
                
                // Check condition
                int cond_result = 0;
                if (node->children[1]->child_count > 0) {
                    cond_result = evaluateIntExpression(node->children[1]->children[0], current_vars);
                } else {
                    // Empty condition means infinite loop (like for(;;))
                    cond_result = 1;
                }
                
                if (!cond_result) break;
                
                // Execute body
                executeStatement(node->children[3], vars);
                
                if (frame && frame->return_value_set) break;
                
                // Execute increment expression
                current_vars = vars ? *vars : NULL;
                if (node->children[2]->child_count > 0) {
                    // The increment is typically an expression like i = i + 1
                    ASTNode *incr_expr = node->children[2];
                    if (incr_expr->child_count > 0) {
                        ASTNode *actual_expr = incr_expr->children[0];
                        if (actual_expr->type == NODE_ASSIGN) {
                            executeStatement(actual_expr, vars);
                        } else {
                            evaluateIntExpression(actual_expr, current_vars);
                        }
                    }
                }
            }
            break;
        }
        
        case NODE_PRINT_STMT: {
            if (node->child_count > 0) {
                ASTNode *fmt = node->children[0];
                const char *format = fmt->name;
                
                if (node->child_count > 1) {
                    ASTNode *args = node->children[1];
                    ASTNode **arg_array = (ASTNode **)malloc(args->child_count * sizeof(ASTNode *));
                    for (int i = 0; i < args->child_count; i++) {
                        arg_array[i] = args->children[i];
                    }
                    handlePrintf(format, arg_array, args->child_count, current_vars);
                    free(arg_array);
                } else {
                    handlePrintf(format, NULL, 0, current_vars);
                }
            }
            break;
        }
        
        case NODE_SCAN_STMT: {
            if (node->child_count > 1) {
                ASTNode *fmt = node->children[0];
                const char *format = fmt->name;
                ASTNode *args = node->children[1];
                
                ASTNode **arg_array = (ASTNode **)malloc(args->child_count * sizeof(ASTNode *));
                for (int i = 0; i < args->child_count; i++) {
                    arg_array[i] = args->children[i];
                }
                handleScanf(format, arg_array, args->child_count, vars);
                free(arg_array);
            }
            break;
        }
        
        case NODE_COMPOUND_STMT:
            for (int i = 0; i < node->child_count; i++) {
                executeStatement(node->children[i], vars);
                if (frame && frame->return_value_set) break;
            }
            break;
        
        case NODE_RETURN_STMT:
            if (frame) {
                if (node->child_count > 0) {
                    frame->return_value.int_val = evaluateIntExpression(node->children[0], current_vars);
                } else {
                    frame->return_value.int_val = 0;
                }
                frame->return_value_set = 1;
            }
            break;
            
        default:
            break;
    }
}

// ============================================================================
// INTERPRETER: MAIN PROGRAM EXECUTION
// ============================================================================

void interpretProgram(ASTNode *node) {
    if (!node) {
        fprintf(stderr, "\n%s:runtime: \033[1;31merror:\033[0m no program to interpret\n", current_filename);
        return;
    }
    
    global_program_root = node;
    VarList *global_vars = NULL;
    
    call_stack_top = NULL;
    current_depth = 0;
    
    if (node->type == NODE_PROGRAM && node->child_count > 0) {
        ASTNode *decl_list = node->children[0];
        
        int found_main = 0;
        for (int i = 0; i < decl_list->child_count; i++) {
            ASTNode *decl = decl_list->children[i];
            
            if (decl->type == NODE_FUNCTION_DECL && strcmp(decl->name, "main") == 0) {
                found_main = 1;
                
                if (decl->child_count > 1) {
                    StackFrame *main_frame = pushStackFrame("main");
                    
                    ASTNode *body = decl->children[1];
                    for (int j = 0; j < body->child_count; j++) {
                        executeStatement(body->children[j], &global_vars);
                        
                        if (main_frame->return_value_set) break;
                    }
                    
                    popStackFrame();
                }
                break;
            }
        }
        
        if (!found_main) {
            fprintf(stderr, "\n%s:1:1: \033[1;31merror:\033[0m no main function found\n", current_filename);
            fprintf(stderr, "\033[1;36mnote:\033[0m every program must have a main function\n");
            fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n");
            fprintf(stderr, "    int main() {\n");
            fprintf(stderr, "        // your code here\n");
            fprintf(stderr, "        return 0;\n");
            fprintf(stderr, "    }\n");
        }
    }
    
    while (global_vars) {
        VarList *temp = global_vars;
        global_vars = global_vars->next;
        free(temp->var.name);
        free(temp);
    }
    
    while (call_stack_top) {
        popStackFrame();
    }
    
    global_program_root = NULL;
}

// ============================================================================
// TYPE INFERENCE FOR ENHANCED ERROR MESSAGES
// ============================================================================

DataType getExpressionType(ASTNode *node, SymbolTable *table) {
    if (!node) return TYPE_UNKNOWN;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            return TYPE_INT;
            
        case NODE_FLOAT_LITERAL:
            return TYPE_FLOAT;
            
        case NODE_IDENTIFIER: {
            Symbol *sym = lookupSymbol(table, node->name);
            if (sym) return sym->type;
            return TYPE_UNKNOWN;
        }
        
        case NODE_BINARY_OP: {
            DataType left = getExpressionType(node->children[0], table);
            DataType right = getExpressionType(node->children[1], table);
            
            // If either is float, result is float
            if (left == TYPE_FLOAT || right == TYPE_FLOAT) {
                return TYPE_FLOAT;
            }
            // Both int
            if (left == TYPE_INT && right == TYPE_INT) {
                return TYPE_INT;
            }
            return TYPE_UNKNOWN;
        }
        
        case NODE_FUNC_CALL: {
            Symbol *func = lookupSymbol(table, node->name);
            if (func && func->is_function) {
                return func->type;
            }
            return TYPE_UNKNOWN;
        }
        
        default:
            return TYPE_UNKNOWN;
    }
}

// ============================================================================
// END OF ENHANCED COMPILER.C WITH FULL LOOP SUPPORT
// ============================================================================
