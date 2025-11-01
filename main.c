#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

extern int yyparse();
extern FILE *yyin;
extern ASTNode *root;
extern SymbolTable *global_scope;
extern int error_count;
extern char *current_filename;

void printUsage(const char *prog_name) {
    printf("Usage: %s [options] <source-file>\n", prog_name);
    printf("Options:\n");
    printf("  -p    Parse and display AST in tree format\n");
    printf("  -a    Generate and display AST in JSON format\n");
    printf("  -s    Perform semantic analysis\n");
    printf("  -i    Interpret and execute\n");
    printf("  -t    Trace execution (with JSON output)\n");
    printf("  -h    Display this help message\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    // If a single argument starting with '-' is provided, it's an option
    // without the required filename (or it's -h). Handle -h and report
    // missing filename for other options to avoid treating options as files.
    if (argc == 2 && argv[1][0] == '-') {
        if (strcmp(argv[1], "-h") == 0) {
            printUsage(argv[0]);
            return 0;
        }
        fprintf(stderr, "Error: Option '%s' requires a filename\n", argv[1]);
        printUsage(argv[0]);
        return 1;
    }
    
    char *filename = NULL;
    char mode = 'p'; // default: print AST
    
    // Parse command line arguments
    if (argc >= 3) {
        if (strcmp(argv[1], "-i") == 0) {
            mode = 'i';
            filename = argv[2];
        } else if (strcmp(argv[1], "-a") == 0) {
            mode = 'a';
            filename = argv[2];
        } else if (strcmp(argv[1], "-s") == 0) {
            mode = 's';
            filename = argv[2];
        } else if (strcmp(argv[1], "-p") == 0) {
            mode = 'p';
            filename = argv[2];
        } else if (strcmp(argv[1], "-t") == 0) {
            mode = 't';
            filename = argv[2];
        } else if (strcmp(argv[1], "-h") == 0) {
            printUsage(argv[0]);
            return 0;
        } else {
            filename = argv[1];
        }
    } else {
        filename = argv[1];
    }
    
    // Set global filename for error messages
    current_filename = filename;
    
    // Open input file
    yyin = fopen(filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return 1;
    }
    
    // Initialize global symbol table
    global_scope = createSymbolTable(NULL);
    
    // Parse the input (suppress messages for JSON mode)
    if (mode != 'a') {
        fprintf(stderr, "Parsing '%s'...\n", filename);
    }
    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result != 0 || error_count > 0) {
        fprintf(stderr, "\nCompilation failed with %d error(s)\n", error_count);
        if (root) freeAST(root);
        freeSymbolTable(global_scope);
        return 1;
    }
    
    if (mode != 'a') {
        fprintf(stderr, "Parsing successful!\n\n");
    }
    
    // Execute based on mode
    switch (mode) {
        case 'i': // Interpret
            printf("=== Interpreting Program ===\n");
            performSemanticAnalysis(root, global_scope);
            if (error_count > 0) {
                fprintf(stderr, "\nCompilation failed with %d semantic error(s)\n", error_count);
                fprintf(stderr, "Cannot interpret due to errors.\n");
            } else {
                interpretProgram(root);
                printf("\n=== Execution Complete ===\n");
            }
            break;
            
        case 'a': // Output JSON AST
            exportASTtoJSON(root, stdout, 0);
            printf("\n");
            break;
            
        case 's': // Semantic analysis
            printf("=== Performing Semantic Analysis ===\n");
            performSemanticAnalysis(root, global_scope);
            if (error_count > 0) {
                fprintf(stderr, "\nCompilation failed with %d semantic error(s)\n", error_count);
            } else {
                printf("\nNo semantic errors found.\n");
            }
            printSymbolTable(global_scope);
            break;
            
        case 't': // Trace execution
            performSemanticAnalysis(root, global_scope);
            if (error_count > 0) {
                fprintf(stderr, "\nCompilation failed with %d semantic error(s)\n", error_count);
                fprintf(stderr, "Cannot trace due to errors.\n");
            } else {
                interpretProgramWithTrace(root, stdout);
            }
            break;
            
        case 'p': // Print AST
        default:
            printf("=== Abstract Syntax Tree ===\n");
            printAST(root, 0);
            printf("\n");
            break;
    }
    
    // Cleanup
    if (root) freeAST(root);
    freeSymbolTable(global_scope);
    
    return (error_count > 0) ? 1 : 0;
}