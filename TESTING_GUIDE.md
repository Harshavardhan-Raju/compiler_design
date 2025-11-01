# Complete Build and Testing Guide

## Overview
This guide provides comprehensive instructions for building, testing, and running the C compiler with execution path visualization.

---

## Step 1: Rebuild the Compiler

### Clean Previous Build
```bash
make clean
```

### Rebuild with New Trace Functions
```bash
make
```

### Verify Build
```bash
./mycc -h
```

**Expected Output:**
```
Usage: mycc [options] <source-file>
Options:
  -p    Parse and display tokens
  -a    Generate and display AST
  -s    Perform semantic analysis
  -i    Interpret and execute
  -t    Trace execution (with JSON output)
  -h    Display this help message
```

---

## Step 2: Test Trace Output

### Basic Trace Test

**File:** `test_trace.c`
```c
int main() {
    int x = 5;
    int y = 10;
    if (x > 3) {
        x = x * 2;
        y = y + x;
    }
    printf("%d\n", x);
    return 0;
}
```

**Run with trace flag:**
```bash
./mycc -t test_trace.c
```

**Expected Output:**
```
TRACE {"step":1,"type":"enter","block":"function","line":1}
TRACE {"step":2,"type":"execute","block":"declaration","line":2,"content":"int x","variables":{"x":5}}
TRACE {"step":3,"type":"execute","block":"declaration","line":3,"content":"int y","variables":{"x":5,"y":10}}
TRACE {"step":4,"type":"enter","block":"if","line":4,"content":"condition = 1","variables":{"x":5,"y":10}}
TRACE {"step":5,"type":"execute","block":"assignment","line":5,"content":"x = 10","variables":{"x":5,"y":10}}
TRACE {"step":6,"type":"execute","block":"assignment","line":6,"content":"y = 20","variables":{"x":10,"y":10}}
TRACE {"step":7,"type":"exit","block":"if","line":7,"variables":{"x":10,"y":20}}
TRACE {"step":8,"type":"execute","block":"print","line":8,"content":"%d\n","variables":{"x":10,"y":20}}
10
TRACE {"step":9,"type":"execute","block":"return","line":9,"content":"return 0","variables":{"x":10,"y":20}}
TRACE {"step":10,"type":"exit","block":"function","line":9,"variables":{"x":10,"y":20}}
```

---

## Step 3: Test with Recursion

**File:** `factorial_trace.c`
```c
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int result;
    result = factorial(5);
    printf("Result = %d\n", result);
    return 0;
}
```

**Run:**
```bash
./mycc -t factorial_trace.c
```

---

## Step 4: Start Flask Server

### Install Dependencies
```bash
pip install flask
```

Or install all dependencies:
```bash
pip install -r requirements.txt
```

### Run Server
```bash
python app1.py
```

**Expected Output:**
```
✓ Found mycc at: c:\...\mycc.exe
============================================================
🚀 Advanced Execution Path Visualizer
============================================================
📁 Base Directory: c:\...\compiler_design
🔧 Compiler Path: c:\...\mycc.exe
⏱️  Timeout: 10s
📊 Max Code Size: 50000 bytes
============================================================

 * Serving Flask app 'app1'
 * Debug mode: on
 * Running on http://0.0.0.0:5000
```

### Open Browser
Navigate to: **http://localhost:5000**

---

## Step 5: Test in Browser

### Basic Workflow
1. **Load Example:** Click "Load Example" to load default code
2. **Visualize:** Click "🔍 Visualize" to generate trace
3. **Run:** Click "▶ Run" to execute step-by-step
4. **Step Through:** Use ⏪ / ⏩ buttons to step through execution

### Features to Test
- [ ] Code editor accepts input
- [ ] Syntax highlighting works
- [ ] Visualization button generates trace
- [ ] Step-by-step execution highlights code
- [ ] Variables update in real-time
- [ ] AST renders correctly
- [ ] CFG shows control flow
- [ ] Error messages display properly

---

## Common Test Cases

### Test 1: Simple Variables
**File:** `test_simple_vars.c`
```c
int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    printf("%d\n", c);
    return 0;
}
```

**Run:**
```bash
./mycc -t test_simple_vars.c
```

---

### Test 2: If-Else
**File:** `test_if_else.c`
```c
int main() {
    int x = 7;
    if (x > 5) {
        printf("Greater\n");
    } else {
        printf("Smaller\n");
    }
    return 0;
}
```

**Run:**
```bash
./mycc -t test_if_else.c
```

---

### Test 3: While Loop
**File:** `test_while_loop.c`
```c
int main() {
    int i = 0;
    int sum = 0;
    while (i < 5) {
        sum = sum + i;
        i = i + 1;
    }
    printf("Sum = %d\n", sum);
    return 0;
}
```

**Run:**
```bash
./mycc -t test_while_loop.c
```

**Expected:** Sum = 10

---

### Test 4: For Loop
**File:** `test_for_loop.c`
```c
int main() {
    int i;
    int sum = 0;
    for (i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    printf("Sum = %d\n", sum);
    return 0;
}
```

**Run:**
```bash
./mycc -t test_for_loop.c
```

**Expected:** Sum = 55

---

### Test 5: Recursion (Factorial)
**File:** `factorial_trace.c`
```c
int fact(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * fact(n - 1);
}

int main() {
    int result;
    result = fact(5);
    printf("Factorial = %d\n", result);
    return 0;
}
```

**Run:**
```bash
./mycc -t factorial_trace.c
```

**Expected:** Factorial = 120

---

### Test 6: Fibonacci
**File:** `test_fibonacci.c`
```c
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int result;
    result = fib(7);
    printf("Fibonacci = %d\n", result);
    return 0;
}
```

**Run:**
```bash
./mycc -t test_fibonacci.c
```

**Expected:** Fibonacci = 13

---

## Troubleshooting

### Issue: No trace output
**Solution:** Verify you're using `-t` flag, not `-i`
```bash
# Wrong
./mycc -i test_trace.c

# Correct
./mycc -t test_trace.c
```

### Issue: Trace lines mixed with program output
**Solution:** Flask app filters TRACE lines automatically. The web interface separates trace data from program output.

### Issue: Missing variables in trace
**Solution:** Check that variables are properly updated in `executeStatementWithTrace` function in `compiler.c`

### Issue: CFG not rendering
**Solution:** Verify AST is being generated with `-a` flag first
```bash
./mycc -a test_trace.c
```

### Issue: AST empty
**Solution:** Check for syntax errors in code
```bash
./mycc -p test_trace.c  # Check parsing
```

### Issue: Flask app won't start
**Solution:** 
1. Check if port 5000 is already in use
2. Verify Flask is installed: `pip install flask`
3. Check if `mycc.exe` exists in the project directory

### Issue: Compiler not found
**Solution:**
```bash
# Rebuild the compiler
make clean
make

# Verify it exists
ls -la mycc.exe  # Windows
ls -la mycc      # Linux/Mac
```

---

## Performance Tips

### Large Recursion Depth
May generate many trace lines - adjust `MAX_CALL_DEPTH` in compiler if needed.

### Long Loops
Limit iterations for visualization clarity. For example:
```c
// Instead of this:
for (i = 0; i < 1000; i++) { ... }

// Use this for testing:
for (i = 0; i < 10; i++) { ... }
```

### Complex Expressions
Break into smaller statements for better trace:
```c
// Instead of this:
int result = (a + b) * (c - d) / e;

// Use this:
int temp1 = a + b;
int temp2 = c - d;
int temp3 = temp1 * temp2;
int result = temp3 / e;
```

---

## Validation Checklist

- [ ] Compiler builds without errors
- [ ] `-t` flag generates TRACE output
- [ ] Flask app starts and loads
- [ ] Code editor accepts input
- [ ] Visualization button works
- [ ] Step-by-step execution highlights code
- [ ] Variables update in real-time
- [ ] AST renders correctly
- [ ] CFG shows control flow
- [ ] Error messages display properly
- [ ] All test cases work

---

## Quick Test Script

Run all tests at once:

```bash
# Test 1: Simple variables
echo "Test 1: Simple Variables"
./mycc -t test_simple_vars.c
echo ""

# Test 2: If-Else
echo "Test 2: If-Else"
./mycc -t test_if_else.c
echo ""

# Test 3: While Loop
echo "Test 3: While Loop"
./mycc -t test_while_loop.c
echo ""

# Test 4: For Loop
echo "Test 4: For Loop"
./mycc -t test_for_loop.c
echo ""

# Test 5: Factorial
echo "Test 5: Factorial"
./mycc -t factorial_trace.c
echo ""

# Test 6: Fibonacci
echo "Test 6: Fibonacci"
./mycc -t test_fibonacci.c
echo ""
```

---

## Next Steps

After basic functionality works:

1. **CFG Node Highlighting:** Add CFG node highlighting synchronized with trace
2. **Call Stack Visualization:** Implement call stack visualization for recursion
3. **Breakpoint Support:** Add breakpoint support for debugging
4. **Export Trace:** Export trace as video/GIF
5. **Sample Library:** Add more test cases to sample library
6. **Performance Optimization:** Optimize trace generation for large programs
7. **Error Recovery:** Improve error handling and recovery
8. **Documentation:** Add inline documentation and tooltips

---

## API Endpoints

### `/compile` (POST)
Compile and run C code with input.

**Request:**
```json
{
  "code": "int main() { return 0; }",
  "input": ""
}
```

**Response:**
```json
{
  "success": true,
  "output": "",
  "errors": "",
  "execution_time": 123.45
}
```

### `/get_trace` (POST)
Get execution trace for visualization.

**Request:**
```json
{
  "code": "int main() { int x = 5; return 0; }",
  "input": ""
}
```

**Response:**
```json
{
  "code": "...",
  "trace": [...],
  "ast": {...},
  "cfg": {...},
  "output": "",
  "execution_time": 123.45,
  "errors": []
}
```

### `/analyze` (POST)
Perform semantic analysis.

**Request:**
```json
{
  "code": "int main() { return 0; }"
}
```

**Response:**
```json
{
  "success": true,
  "output": "Analysis completed successfully",
  "execution_time": 123.45
}
```

### `/health` (GET)
Health check endpoint.

**Response:**
```json
{
  "status": "healthy",
  "mycc_available": true,
  "mycc_path": "/path/to/mycc"
}
```

---

## Additional Resources

- **README.md:** Project overview and setup instructions
- **compiler.c:** Main compiler implementation
- **app1.py:** Flask web server
- **visualizer.html:** Web interface template
- **parser.y:** Bison grammar file
- **scanner.l:** Flex lexer file

---

## Support

For issues or questions:
1. Check the troubleshooting section
2. Review the validation checklist
3. Examine debug.log for detailed error messages
4. Test with simpler code examples first

---

**Last Updated:** 2025-11-02
