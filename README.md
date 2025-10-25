# Mini C Compiler/Interpreter

A fully functional Mini C compiler and interpreter built from scratch using Flex (Lex) and Bison (Yacc) in C.

## 🎯 Features

- **Lexical Analysis**: Token recognition for keywords, identifiers, operators, and literals
- **Syntax Parsing**: Complete grammar for C subset including functions, loops, and conditionals
- **Semantic Analysis**: Type checking and undeclared variable detection
- **AST Construction**: Abstract Syntax Tree generation
- **JSON Export**: AST visualization in JSON format
- **Interpreter Mode**: Direct execution of parsed code
- **Symbol Table**: Variable and function tracking

## 🏗️ Language Support

### Data Types
- `int` - Integer type
- `float` - Floating point type
- `void` - Void type (for functions)

### Control Structures
- `if` / `else` - Conditional statements
- `while` - While loops
- `for` - For loops

### Operations
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Relational: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Logical: `&&`, `||`, `!`

### Features
- Variable declarations and assignments
- Function definitions with parameters
- Function calls and recursion
- Return statements
- Input/Output (`scanf`, `printf`)

## 📦 Installation

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install flex bison gcc make graphviz python3-pip

# macOS
brew install flex bison gcc make graphviz
pip3 install graphviz

# Python dependencies
pip3 install graphviz
```

### Build
```bash
make clean
make
```

This will create the `mycc` executable.

## 🚀 Usage

### Basic Modes

#### 1. Print AST (Tree Format)
```bash
./mycc -p program.c
```

#### 2. Interpret and Execute
```bash
./mycc -i program.c
```

#### 3. Export AST as JSON
```bash
./mycc -a program.c > ast.json
```

#### 4. Semantic Analysis
```bash
./mycc -s program.c
```

### Visualize AST
```bash
# Generate JSON
./mycc -a samples/test1.c > ast.json

# Visualize
python3 ast_visualizer.py ast.json
```

This will create `ast_output.png` with the visual AST graph.

## 📁 Project Structure

```
.
├── scanner.l          # Lexical analyzer (Flex)
├── parser.y           # Syntax parser (Bison)
├── compiler.h         # Header definitions
├── compiler.c         # AST & interpreter implementation
├── main.c             # Entry point
├── Makefile           # Build configuration
├── ast_visualizer.py  # Python visualization tool
└── samples/           # Test programs
    └── test1.c        # Factorial example
```

## 🧪 Example Programs

### Test 1: Factorial (Recursion)
```c
int fact(int n) {
    if (n <= 1)
        return 1;
    else
        return n * fact(n - 1);
}

int main() {
    int x;
    scanf("%d", &x);
    printf("%d", fact(x));
    return 0;
}
```

Run it:
```bash
./mycc -i samples/test1.c
5          # input
120        # output
```

### Test 2: Simple Conditionals
```c
int main() {
    int x;
    int y;
    x = 10;
    y = 20;
    
    if (x < y) {
        printf("%d", x);
    } else {
        printf("%d", y);
    }
    
    return 0;
}
```

### Test 3: While Loop
```c
int main() {
    int i;
    int sum;
    i = 1;
    sum = 0;
    
    while (i <= 10) {
        sum = sum + i;
        i = i + 1;
    }
    
    printf("%d", sum);  // Output: 55
    return 0;
}
```

### Test 4: For Loop
```c
int main() {
    int i;
    int sum;
    sum = 0;
    
    for (i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    
    printf("%d", sum);  // Output: 55
    return 0;
}
```

## 🔧 System Architecture

### 1. Lexical Analyzer (`scanner.l`)
- Tokenizes input source code
- Recognizes keywords, identifiers, literals, operators
- Handles comments (single-line `//` and multi-line `/* */`)

### 2. Parser (`parser.y`)
- Implements grammar rules
- Builds Abstract Syntax Tree
- Handles operator precedence and associativity

### 3. AST Construction (`compiler.c`)
- Creates and manages AST nodes
- Implements tree traversal
- Exports to JSON format

### 4. Symbol Table
- Tracks variables and functions
- Supports scoping
- Detects duplicate declarations

### 5. Semantic Analyzer
- Type checking
- Undeclared variable detection
- Function signature validation

### 6. Interpreter
- Direct execution of AST
- Variable storage and retrieval
- Function call handling with recursion

## 📊 AST Node Types

```
- NODE_PROGRAM          - Root program node
- NODE_FUNCTION_DECL    - Function declaration
- NODE_VAR_DECL         - Variable declaration
- NODE_PARAM            - Function parameter
- NODE_COMPOUND_STMT    - Block of statements
- NODE_IF_STMT          - If/else statement
- NODE_WHILE_STMT       - While loop
- NODE_FOR_STMT         - For loop
- NODE_RETURN_STMT      - Return statement
- NODE_EXPR_STMT        - Expression statement
- NODE_ASSIGN           - Assignment
- NODE_BINARY_OP        - Binary operation
- NODE_UNARY_OP         - Unary operation
- NODE_FUNC_CALL        - Function call
- NODE_IDENTIFIER       - Variable/function name
- NODE_INT_LITERAL      - Integer constant
- NODE_FLOAT_LITERAL    - Float constant
- NODE_PRINT_STMT       - Printf statement
- NODE_SCAN_STMT        - Scanf statement
```

## 🐛 Error Handling

The compiler detects and reports:
- **Syntax Errors**: Invalid grammar
- **Semantic Errors**: 
  - Undeclared variables
  - Duplicate declarations
  - Type mismatches
- **Parse Errors**: Malformed expressions

## 🔍 Testing

Run all tests:
```bash
make test
```

Individual tests:
```bash
# Create samples directory
mkdir -p samples

# Create test file
cat > samples/test1.c << 'EOF'
int fact(int n) {
    if (n <= 1)
        return 1;
    else
        return n * fact(n - 1);
}

int main() {
    int x;
    scanf("%d", &x);
    printf("%d", fact(x));
    return 0;
}
EOF

# Parse and print AST
./mycc -p samples/test1.c

# Semantic analysis
./mycc -s samples/test1.c

# Execute
echo "5" | ./mycc -i samples/test1.c

# Generate visualization
./mycc -a samples/test1.c > ast.json
python3 ast_visualizer.py ast.json
```

## 📝 Grammar Rules

### Program Structure
```
program → declaration_list

declaration_list → declaration_list declaration
                 | declaration

declaration → var_declaration
            | function_declaration
```

### Functions
```
function_declaration → type_specifier ID ( params ) compound_stmt

params → param_list
       | void
       | ε

param_list → param_list , param
           | param

param → type_specifier ID
```

### Statements
```
stmt → expr_stmt
     | compound_stmt
     | selection_stmt
     | iteration_stmt
     | return_stmt
     | print_stmt
     | scan_stmt
     | var_declaration

selection_stmt → if ( expr ) stmt
               | if ( expr ) stmt else stmt

iteration_stmt → while ( expr ) stmt
               | for ( expr_stmt expr_stmt expr ) stmt
```

### Expressions
```
expr → ID = expr
     | simple_expr

simple_expr → simple_expr relop additive_expr
            | additive_expr

additive_expr → additive_expr + term
              | additive_expr - term
              | term

term → term * factor
     | term / factor
     | term % factor
     | factor

factor → ( expr )
       | ID
       | call
       | INT_CONST
       | FLOAT_CONST
       | - factor
       | ! factor
```

## 🎨 JSON AST Format

Example output:
```json
{
  "type": "Program",
  "children": [
    {
      "type": "CompoundStmt",
      "name": "DeclarationList",
      "children": [
        {
          "type": "FunctionDecl",
          "name": "fact",
          "children": [
            {
              "type": "CompoundStmt",
              "name": "ParamList",
              "children": [
                {
                  "type": "Param",
                  "name": "n"
                }
              ]
            },
            {
              "type": "CompoundStmt",
              "name": "StmtList",
              "children": [
                {
                  "type": "IfStmt",
                  "name": "IfElse",
                  "children": [
                    {
                      "type": "BinaryOp",
                      "name": "<=",
                      "children": [
                        {
                          "type": "Identifier",
                          "name": "n"
                        },
                        {
                          "type": "IntLiteral",
                          "name": "int",
                          "value": 1
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  ]
}
```

## 🚧 Known Limitations

1. **Function Calls**: Recursive functions work in limited capacity. Full call stack not implemented.
2. **Arrays**: Not supported in current version
3. **Pointers**: Limited support (only for scanf)
4. **Strings**: Only as format strings for printf/scanf
5. **Global Variables**: Supported but limited scope management
6. **Type Coercion**: Minimal implicit type conversion

## 🔮 Future Enhancements

- [ ] Full call stack for complex recursion
- [ ] Array support with indexing
- [ ] Pointer arithmetic
- [ ] Struct/Union support
- [ ] Switch-case statements
- [ ] Do-while loops
- [ ] Break/continue statements
- [ ] Multi-file compilation
- [ ] Code generation (assembly output)
- [ ] Optimization passes

## 🛠️ Troubleshooting

### Build Errors

**Problem**: `flex: command not found`
```bash
sudo apt-get install flex  # Ubuntu/Debian
brew install flex          # macOS
```

**Problem**: `bison: command not found`
```bash
sudo apt-get install bison  # Ubuntu/Debian
brew install bison          # macOS
```

**Problem**: `cannot find -lfl`
```bash
# Install flex library
sudo apt-get install libfl-dev
```

### Runtime Errors

**Problem**: `Parsing failed`
- Check syntax errors in input file
- Ensure all statements end with semicolons
- Verify braces are balanced

**Problem**: `Semantic Error: Undeclared identifier`
- Declare variables before use
- Check function names match declarations

**Problem**: Visualization doesn't work
```bash
# Install graphviz
pip3 install graphviz

# System graphviz
sudo apt-get install graphviz  # Ubuntu
brew install graphviz          # macOS
```

## 📚 References

- Flex Documentation: https://github.com/westes/flex
- Bison Manual: https://www.gnu.org/software/bison/manual/
- Graphviz: https://graphviz.org/
- Compiler Design Principles

## 👥 Contributing

This is an educational project demonstrating compiler construction concepts. Feel free to:
1. Add new test cases
2. Implement additional features
3. Improve error messages
4. Enhance the interpreter
5. Add optimization passes

## 📄 License

This project is for educational purposes. Feel free to use and modify.

## 🎓 Learning Resources

### Key Concepts Demonstrated
1. **Lexical Analysis**: Pattern matching and tokenization
2. **Syntax Analysis**: Context-free grammars and parsing
3. **Semantic Analysis**: Type systems and symbol tables
4. **Tree Traversal**: AST construction and manipulation
5. **Interpretation**: Direct execution without compilation
6. **Visualization**: Data structure representation

### Understanding the Code

#### How Tokens Flow
```
Input Code → Scanner (Lex) → Tokens → Parser (Yacc) → AST
```

#### How Execution Works
```
AST → Semantic Check → Interpreter → Output
```

#### Symbol Table Lookup
```
Current Scope → Parent Scope → ... → Global Scope
```

## 🧩 Example Walkthrough

### Input Program
```c
int add(int a, int b) {
    return a + b;
}

int main() {
    int x;
    x = 10;
    printf("%d", add(x, 5));
    return 0;
}
```

### Parsing Steps
1. **Lexical Analysis**: Break into tokens
   - `int`, `add`, `(`, `int`, `a`, `,`, etc.

2. **Syntax Analysis**: Build parse tree
   - Program → Function List → Functions

3. **AST Construction**: Simplify to AST
   - FunctionDecl(add) with params and body
   - FunctionDecl(main) with statements

4. **Semantic Analysis**: Check validity
   - Verify `add` is declared before use
   - Check parameter types match

5. **Interpretation**: Execute
   - Call main()
   - Execute x = 10
   - Call add(10, 5)
   - Print result: 15

## 🎯 Quick Start Guide

```bash
# 1. Clone/Download all files
# 2. Build
make clean && make

# 3. Create a simple test
cat > test.c << 'EOF'
int main() {
    int x;
    x = 42;
    printf("%d", x);
    return 0;
}
EOF

# 4. Run different modes
./mycc -p test.c    # See AST
./mycc -s test.c    # Check semantics
./mycc -i test.c    # Execute (outputs: 42)
./mycc -a test.c > ast.json
python3 ast_visualizer.py ast.json

# 5. Success! 🎉
```

---

**Built with ❤️ using Flex, Bison, and C**
# compiler_design
