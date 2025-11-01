# Build Instructions for Windows

## Important: Toolchain Setup

Your system has **two different GCC toolchains**:
1. **MSYS64** (`C:\msys64\usr\bin`) - Used for the original build
2. **MinGW64** (`C:\mingw64\bin`) - Currently in your PATH

The existing `mycc.exe` was built with MSYS64. To rebuild or make changes, you **must** use MSYS64.

---

## Quick Rebuild (Using MSYS64)

### Step 1: Set PATH to MSYS64
```powershell
$env:PATH = "C:\msys64\usr\bin;" + $env:PATH
```

### Step 2: Verify GCC Version
```powershell
gcc --version
# Should show MSYS64 GCC, not MinGW64
```

### Step 3: Clean and Build
```powershell
make clean
make
```

### Step 4: Test
```powershell
.\mycc.exe -h
```

---

## Current Status

✅ **mycc.exe** - Restored from git (original working version)  
✅ **Test files** - All 7 test files created  
✅ **Documentation** - Complete testing guide created  
✅ **Test scripts** - PowerShell and Bash scripts ready  

⚠️ **main.c** - Has been reverted to original (help flag fix not applied)  
⚠️ **Makefile** - Has been reverted to original  

---

## Recommended: Apply Fixes with MSYS64

Once you set the PATH to MSYS64, apply these fixes:

### Fix 1: Update main.c for -h flag

The `-h` flag currently doesn't work because it's treated as a filename. Apply this fix:

**File:** `main.c`  
**Line:** After line 28 (after the `argc < 2` check)

Add:
```c
// Check for help flag first
if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printUsage(argv[0]);
    return 0;
}
```

### Fix 2: Add -t flag support

**File:** `main.c`

1. In the argument parsing section (around line 47), add:
```c
} else if (strcmp(argv[1], "-t") == 0) {
    mode = 't';
    filename = argv[2];
```

2. In the switch statement (around line 142), add before the 'p' case:
```c
case 't': // Trace mode
    performSemanticAnalysis(root, global_scope);
    if (error_count > 0) {
        fprintf(stderr, "\nCompilation failed with %d semantic error(s)\n", error_count);
        fprintf(stderr, "Cannot trace due to errors.\n");
    } else {
        interpretProgramWithTrace(root, stdout);
    }
    break;
```

3. Update the help message in `printUsage()`:
```c
printf("Usage: %s [options] <source-file>\n", prog_name);
printf("Options:\n");
printf("  -p    Parse and display tokens\n");
printf("  -a    Generate and display AST\n");
printf("  -s    Perform semantic analysis\n");
printf("  -i    Interpret and execute\n");
printf("  -t    Trace execution (with JSON output)\n");
printf("  -h    Display this help message\n");
```

### Fix 3: Update Makefile for cross-platform

**File:** `Makefile`

Replace lines 1-11 with:
```makefile
CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -g -Wno-unused-function -Wno-implicit-function-declaration
TARGET = mycc
OBJS = parser.tab.o lex.yy.o compiler.o main.o

# Detect OS for library linking
ifeq ($(OS),Windows_NT)
    LDFLAGS = 
    TARGET = mycc.exe
else
    LDFLAGS = -lfl
    TARGET = mycc
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
```

---

## After Applying Fixes

### Rebuild
```powershell
# Ensure MSYS64 is in PATH
$env:PATH = "C:\msys64\usr\bin;" + $env:PATH

# Clean and rebuild
make clean
make
```

### Test the fixes
```powershell
# Test help flag
.\mycc.exe -h

# Test trace flag
.\mycc.exe -t test_trace.c

# Run all tests
.\run_tests.ps1
```

---

## Troubleshooting

### Error: "undefined reference to `__getreent`"
**Cause:** Using MinGW64 instead of MSYS64  
**Solution:** Set PATH to MSYS64 first

### Error: "cannot find -lfl"
**Cause:** Flex library not found  
**Solution:** Use the updated Makefile (Fix 3) which doesn't require -lfl on Windows

### Error: "make: command not found"
**Cause:** MSYS64 not in PATH  
**Solution:** Run `$env:PATH = "C:\msys64\usr\bin;" + $env:PATH`

---

## Alternative: Use MSYS64 Terminal

Instead of PowerShell, you can use the MSYS64 terminal directly:

1. Open **MSYS2 MSYS** from Start Menu
2. Navigate to project: `cd /c/Onedrive_Docs/Sem5/CD/PROJECT/compiler_design`
3. Run: `make clean && make`
4. Test: `./mycc.exe -h`

---

## Files Status

### Restored (Working)
- ✅ mycc.exe (original binary)
- ✅ main.c (original code)
- ✅ Makefile (original)

### Created (New)
- ✅ test_trace.c
- ✅ factorial_trace.c
- ✅ test_simple_vars.c
- ✅ test_if_else.c
- ✅ test_while_loop.c
- ✅ test_for_loop.c
- ✅ test_fibonacci.c
- ✅ run_tests.ps1
- ✅ run_tests.sh
- ✅ TESTING_GUIDE.md
- ✅ QUICKSTART.md
- ✅ VALIDATION_CHECKLIST.md
- ✅ PROJECT_SUMMARY.md
- ✅ requirements.txt (updated with Flask)

---

## Next Steps

1. **Set MSYS64 PATH** (required for rebuilding)
2. **Apply the 3 fixes** above
3. **Rebuild** with `make clean && make`
4. **Test** with `.\mycc.exe -h`
5. **Run test suite** with `.\run_tests.ps1`
6. **Start Flask server** with `python app1.py`

---

**Last Updated:** 2025-11-02
