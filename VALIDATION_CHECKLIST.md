# Validation Checklist

Use this checklist to verify that all components of the C Compiler Execution Path Visualizer are working correctly.

---

## Build Validation

### Compiler Build
- [ ] `make clean` executes without errors
- [ ] `make` builds successfully
- [ ] `mycc.exe` (Windows) or `mycc` (Linux/Mac) is created
- [ ] No compilation warnings (or only expected warnings)
- [ ] Binary has execute permissions (Linux/Mac)

### File Verification
```bash
# Check if binary exists
ls -la mycc.exe  # Windows
ls -la mycc      # Linux/Mac

# Verify size (should be > 100KB)
# Windows: dir mycc.exe
# Linux/Mac: ls -lh mycc
```

---

## Command Line Validation

### Help Flag
- [ ] `./mycc -h` displays help message
- [ ] All flags are documented: `-p`, `-a`, `-s`, `-i`, `-t`, `-h`

**Expected output:**
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

### Parse Flag (`-p`)
- [ ] `./mycc -p test_simple_vars.c` shows tokens
- [ ] Token output includes: INT, IDENTIFIER, NUMBER, etc.
- [ ] No syntax errors for valid code

### AST Flag (`-a`)
- [ ] `./mycc -a test_simple_vars.c` generates JSON
- [ ] JSON is valid (can be parsed)
- [ ] AST contains expected nodes: Program, Function, Decl, etc.

**Validation:**
```bash
./mycc -a test_simple_vars.c | python -m json.tool
```

### Semantic Analysis (`-s`)
- [ ] `./mycc -s test_simple_vars.c` runs analysis
- [ ] Reports type errors correctly
- [ ] Reports undefined variables
- [ ] Reports redeclaration errors

### Interpretation (`-i`)
- [ ] `./mycc -i test_simple_vars.c` executes code
- [ ] Produces correct output
- [ ] Variables are initialized correctly
- [ ] Control flow works (if, while, for)
- [ ] Functions can be called
- [ ] Recursion works

### Trace Flag (`-t`)
- [ ] `./mycc -t test_trace.c` generates TRACE output
- [ ] Each line starts with "TRACE " or is valid JSON
- [ ] Trace includes: step, type, block, line, variables
- [ ] Variables are tracked correctly
- [ ] Control flow is traced (enter/exit blocks)

**Expected trace format:**
```json
TRACE {"step":1,"type":"enter","block":"function","line":1}
TRACE {"step":2,"type":"execute","block":"declaration","line":2,"content":"int x","variables":{"x":5}}
```

---

## Test Cases Validation

### Test 1: Simple Variables (`test_simple_vars.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `15`
- [ ] Trace shows variable declarations
- [ ] Trace shows arithmetic operation

### Test 2: If-Else (`test_if_else.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `Greater` (for x=7)
- [ ] Trace shows condition evaluation
- [ ] Trace shows branch taken

### Test 3: While Loop (`test_while_loop.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `Sum = 10`
- [ ] Trace shows loop iterations
- [ ] Trace shows variable updates in loop

### Test 4: For Loop (`test_for_loop.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `Sum = 55`
- [ ] Trace shows initialization, condition, update
- [ ] Trace shows all iterations

### Test 5: Factorial (`factorial_trace.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `Result = 120`
- [ ] Trace shows function calls
- [ ] Trace shows recursion depth
- [ ] Trace shows return values

### Test 6: Fibonacci (`test_fibonacci.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `Fibonacci = 13`
- [ ] Trace shows multiple recursive calls
- [ ] Trace shows call tree structure

### Test 7: Basic Trace (`test_trace.c`)
- [ ] Compiles without errors
- [ ] Executes with `-i` flag
- [ ] Output: `10`
- [ ] Trace shows if statement execution
- [ ] Trace shows variable modifications

---

## Automated Test Suite

### PowerShell Script (Windows)
- [ ] `run_tests.ps1` executes without errors
- [ ] All tests pass
- [ ] Summary shows correct counts
- [ ] AST generation test passes
- [ ] Interpretation test passes

**Run:**
```powershell
.\run_tests.ps1
```

### Bash Script (Linux/Mac)
- [ ] `run_tests.sh` has execute permissions
- [ ] Script executes without errors
- [ ] All tests pass
- [ ] Summary shows correct counts
- [ ] AST generation test passes
- [ ] Interpretation test passes

**Run:**
```bash
chmod +x run_tests.sh
./run_tests.sh
```

---

## Web Interface Validation

### Flask Server
- [ ] `python app1.py` starts without errors
- [ ] Server displays startup message
- [ ] Shows correct paths (mycc, base directory)
- [ ] Listens on port 5000
- [ ] No Python import errors

**Expected startup:**
```
✓ Found mycc at: .../mycc.exe
============================================================
🚀 Advanced Execution Path Visualizer
============================================================
 * Running on http://0.0.0.0:5000
```

### Web Interface Access
- [ ] Browser opens http://localhost:5000
- [ ] Page loads without errors
- [ ] No 404 errors in browser console
- [ ] CSS styles load correctly
- [ ] JavaScript loads without errors

### UI Components
- [ ] Code editor is visible and editable
- [ ] "Load Example" button works
- [ ] "🔍 Visualize" button is present
- [ ] "▶ Run" button is present
- [ ] "⏪ Previous" button is present
- [ ] "⏩ Next" button is present
- [ ] Input textarea is present
- [ ] Output area is present

### Load Example Feature
- [ ] Click "Load Example" loads code
- [ ] Example code is valid C
- [ ] Example includes variables and control flow

### Visualization Feature
- [ ] Click "🔍 Visualize" generates trace
- [ ] AST is displayed (if available)
- [ ] CFG is displayed (if available)
- [ ] No JavaScript errors in console
- [ ] Loading indicator appears during processing

### Execution Feature
- [ ] Click "▶ Run" starts execution
- [ ] Current line is highlighted
- [ ] Variables panel shows current values
- [ ] Step counter updates
- [ ] Output appears in output panel

### Step Navigation
- [ ] "⏩ Next" advances to next step
- [ ] "⏪ Previous" goes to previous step
- [ ] First step: "Previous" is disabled
- [ ] Last step: "Next" is disabled
- [ ] Line highlighting updates correctly
- [ ] Variables update correctly

### AST Visualization
- [ ] AST tree is rendered
- [ ] Nodes are expandable/collapsible
- [ ] Node labels are readable
- [ ] Tree structure is correct
- [ ] No rendering errors

### CFG Visualization
- [ ] CFG graph is rendered
- [ ] Nodes are positioned correctly
- [ ] Edges connect correct nodes
- [ ] True/false branches are labeled
- [ ] Loop back-edges are visible
- [ ] Graph is readable

### Error Handling
- [ ] Syntax errors are displayed
- [ ] Error messages are clear
- [ ] Line numbers are shown for errors
- [ ] Invalid code doesn't crash server
- [ ] Timeout errors are handled gracefully

---

## API Endpoint Validation

### `/health` Endpoint
- [ ] GET request succeeds
- [ ] Returns JSON with status
- [ ] Shows mycc availability
- [ ] Shows mycc path

**Test:**
```bash
curl http://localhost:5000/health
```

**Expected:**
```json
{
  "status": "healthy",
  "mycc_available": true,
  "mycc_path": "/path/to/mycc"
}
```

### `/compile` Endpoint
- [ ] POST request with valid code succeeds
- [ ] Returns execution output
- [ ] Returns execution time
- [ ] Handles input correctly
- [ ] Reports errors for invalid code

**Test:**
```bash
curl -X POST http://localhost:5000/compile \
  -H "Content-Type: application/json" \
  -d '{"code":"int main() { return 0; }","input":""}'
```

### `/get_trace` Endpoint
- [ ] POST request with valid code succeeds
- [ ] Returns trace array
- [ ] Returns AST object
- [ ] Returns CFG object
- [ ] Returns execution output
- [ ] Handles errors gracefully

**Test:**
```bash
curl -X POST http://localhost:5000/get_trace \
  -H "Content-Type: application/json" \
  -d '{"code":"int main() { int x = 5; return 0; }","input":""}'
```

### `/analyze` Endpoint
- [ ] POST request with valid code succeeds
- [ ] Returns analysis results
- [ ] Reports semantic errors
- [ ] Returns execution time

---

## Performance Validation

### Compilation Speed
- [ ] Simple programs compile in < 1 second
- [ ] Complex programs compile in < 5 seconds
- [ ] No memory leaks during compilation

### Execution Speed
- [ ] Simple programs execute in < 1 second
- [ ] Loops (< 100 iterations) execute in < 2 seconds
- [ ] Recursion (depth < 10) executes in < 2 seconds

### Web Interface Responsiveness
- [ ] Page loads in < 2 seconds
- [ ] Visualization generates in < 3 seconds
- [ ] Step navigation is instant (< 100ms)
- [ ] No UI freezing during execution

### Memory Usage
- [ ] Compiler uses < 100MB RAM
- [ ] Flask server uses < 200MB RAM
- [ ] No memory leaks during repeated tests
- [ ] Browser tab uses < 500MB RAM

---

## Error Handling Validation

### Syntax Errors
- [ ] Missing semicolon is detected
- [ ] Unmatched braces are detected
- [ ] Invalid tokens are detected
- [ ] Error messages include line numbers

**Test:**
```c
int main() {
    int x = 5  // Missing semicolon
    return 0;
}
```

### Semantic Errors
- [ ] Undefined variables are detected
- [ ] Type mismatches are detected
- [ ] Redeclarations are detected
- [ ] Invalid operations are detected

**Test:**
```c
int main() {
    int x = y;  // Undefined variable
    return 0;
}
```

### Runtime Errors
- [ ] Division by zero is handled
- [ ] Stack overflow is detected (deep recursion)
- [ ] Timeout is enforced (infinite loops)

**Test:**
```c
int main() {
    int x = 5 / 0;  // Division by zero
    return 0;
}
```

---

## Cross-Platform Validation

### Windows
- [ ] Builds with MinGW/Cygwin
- [ ] `mycc.exe` runs correctly
- [ ] PowerShell script works
- [ ] Flask server starts
- [ ] Web interface accessible

### Linux
- [ ] Builds with GCC
- [ ] `mycc` runs correctly
- [ ] Bash script works
- [ ] Flask server starts
- [ ] Web interface accessible

### macOS
- [ ] Builds with Clang/GCC
- [ ] `mycc` runs correctly
- [ ] Bash script works
- [ ] Flask server starts
- [ ] Web interface accessible

---

## Documentation Validation

### README.md
- [ ] Exists and is up-to-date
- [ ] Describes project purpose
- [ ] Lists features
- [ ] Provides installation instructions
- [ ] Includes usage examples

### TESTING_GUIDE.md
- [ ] Exists and is comprehensive
- [ ] Covers all test cases
- [ ] Includes expected outputs
- [ ] Provides troubleshooting tips

### QUICKSTART.md
- [ ] Exists and is concise
- [ ] Provides quick setup steps
- [ ] Includes minimal examples
- [ ] Links to detailed documentation

### Code Comments
- [ ] Functions are documented
- [ ] Complex logic is explained
- [ ] TODOs are marked clearly
- [ ] API endpoints are documented

---

## Security Validation

### Input Validation
- [ ] Code size is limited
- [ ] Execution timeout is enforced
- [ ] File paths are sanitized
- [ ] No arbitrary code execution

### Web Security
- [ ] No XSS vulnerabilities
- [ ] No SQL injection (N/A - no database)
- [ ] CORS is configured appropriately
- [ ] Error messages don't leak sensitive info

---

## Final Checklist

### Before Release
- [ ] All tests pass
- [ ] Documentation is complete
- [ ] No known critical bugs
- [ ] Performance is acceptable
- [ ] Security checks pass
- [ ] Cross-platform compatibility verified

### Before Demo
- [ ] Clean build from scratch works
- [ ] Example programs run correctly
- [ ] Web interface is responsive
- [ ] Visualizations render correctly
- [ ] No errors in console/logs

---

## Sign-Off

**Tested by:** ___________________  
**Date:** ___________________  
**Version:** ___________________  
**Platform:** ___________________  
**Status:** ☐ Pass ☐ Fail ☐ Partial  

**Notes:**
```
[Add any additional notes or issues found during validation]
```

---

**Last Updated:** 2025-11-02
