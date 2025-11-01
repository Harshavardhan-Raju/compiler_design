# Quick Start Guide

Get up and running with the C Compiler Execution Path Visualizer in 5 minutes!

## Prerequisites

- **GCC/MinGW:** C compiler
- **Flex:** Lexical analyzer generator
- **Bison:** Parser generator
- **Python 3.8+:** For web interface
- **Make:** Build automation

## Installation (Windows)

### 1. Install Dependencies

```powershell
# Install Python packages
pip install -r requirements.txt
```

### 2. Build the Compiler

```powershell
# Clean and build
make clean
make

# Verify build
.\mycc.exe -h
```

### 3. Run Tests

```powershell
# Run automated test suite
.\run_tests.ps1

# Or run individual test
.\mycc.exe -t test_trace.c
```

### 4. Start Web Interface

```powershell
# Start Flask server
python app1.py
```

Open browser: **http://localhost:5000**

---

## Installation (Linux/Mac)

### 1. Install Dependencies

```bash
# Install system packages (Ubuntu/Debian)
sudo apt-get install flex bison gcc make

# Install Python packages
pip install -r requirements.txt
```

### 2. Build the Compiler

```bash
# Clean and build
make clean
make

# Verify build
./mycc -h
```

### 3. Run Tests

```bash
# Make script executable
chmod +x run_tests.sh

# Run automated test suite
./run_tests.sh

# Or run individual test
./mycc -t test_trace.c
```

### 4. Start Web Interface

```bash
# Start Flask server
python app1.py
```

Open browser: **http://localhost:5000**

---

## Quick Test

### Command Line Test

```bash
# Create a simple test file
echo 'int main() { int x = 5; printf("%d\n", x); return 0; }' > hello.c

# Run with trace
./mycc -t hello.c
```

**Expected output:**
```
TRACE {"step":1,"type":"enter","block":"function","line":1}
TRACE {"step":2,"type":"execute","block":"declaration","line":1,"content":"int x","variables":{"x":5}}
TRACE {"step":3,"type":"execute","block":"print","line":1,"content":"%d\n","variables":{"x":5}}
5
TRACE {"step":4,"type":"execute","block":"return","line":1,"content":"return 0","variables":{"x":5}}
TRACE {"step":5,"type":"exit","block":"function","line":1,"variables":{"x":5}}
```

### Web Interface Test

1. Open **http://localhost:5000**
2. Click **"Load Example"**
3. Click **"🔍 Visualize"**
4. Click **"▶ Run"**
5. Use **⏪ / ⏩** to step through execution

---

## Compiler Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-p` | Parse and display tokens | `./mycc -p file.c` |
| `-a` | Generate AST (JSON) | `./mycc -a file.c` |
| `-s` | Semantic analysis | `./mycc -s file.c` |
| `-i` | Interpret and execute | `./mycc -i file.c` |
| `-t` | Trace execution (JSON) | `./mycc -t file.c` |
| `-h` | Display help | `./mycc -h` |

---

## Common Issues

### Issue: `mycc: command not found`
**Solution:** Build the compiler first with `make`

### Issue: `flex: not found` or `bison: not found`
**Solution:** Install flex and bison:
- **Windows:** Install via MinGW or Cygwin
- **Linux:** `sudo apt-get install flex bison`
- **Mac:** `brew install flex bison`

### Issue: Flask not found
**Solution:** `pip install flask`

### Issue: Port 5000 already in use
**Solution:** Change port in `app1.py` (line 767):
```python
app.run(debug=True, host='0.0.0.0', port=8080)  # Change to 8080
```

---

## File Structure

```
compiler_design/
├── mycc.exe              # Compiled binary (Windows)
├── mycc                  # Compiled binary (Linux/Mac)
├── app1.py               # Flask web server
├── compiler.c            # Compiler implementation
├── compiler.h            # Header file
├── parser.y              # Bison grammar
├── scanner.l             # Flex lexer
├── Makefile              # Build configuration
├── requirements.txt      # Python dependencies
├── TESTING_GUIDE.md      # Comprehensive testing guide
├── QUICKSTART.md         # This file
├── run_tests.ps1         # Windows test script
├── run_tests.sh          # Linux/Mac test script
├── templates/
│   └── index.html        # Web interface template
└── test_*.c              # Test files
```

---

## Next Steps

1. **Read the full guide:** See `TESTING_GUIDE.md` for detailed instructions
2. **Try examples:** Run all test cases with `run_tests.ps1` or `run_tests.sh`
3. **Explore the web UI:** Test different C programs in the browser
4. **Customize:** Modify test cases or create your own

---

## Example Programs

### Simple Variables
```c
int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    printf("%d\n", c);
    return 0;
}
```

### Factorial
```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int result = factorial(5);
    printf("Factorial = %d\n", result);
    return 0;
}
```

### Loop
```c
int main() {
    int sum = 0;
    for (int i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    printf("Sum = %d\n", sum);
    return 0;
}
```

---

## Support

- **Documentation:** `TESTING_GUIDE.md`
- **Issues:** Check `debug.log` for errors
- **Examples:** See `test_*.c` files

---

**Happy Coding! 🚀**
