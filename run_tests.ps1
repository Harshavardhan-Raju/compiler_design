# PowerShell Test Script for Compiler Visualization
# Run all test cases and verify output

Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "  C Compiler Execution Path Visualizer - Test Suite" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""

# Check if mycc.exe exists
if (-Not (Test-Path ".\mycc.exe")) {
    Write-Host "ERROR: mycc.exe not found!" -ForegroundColor Red
    Write-Host "Please run 'make' to build the compiler first." -ForegroundColor Yellow
    exit 1
}

Write-Host "Found mycc.exe" -ForegroundColor Green
Write-Host ""

# Test counter
$testsPassed = 0
$testsFailed = 0

function Run-Test {
    param(
        [string]$TestName,
        [string]$TestFile,
        [string]$ExpectedOutput
    )
    
    Write-Host "Running: $TestName" -ForegroundColor Yellow
    Write-Host "File: $TestFile" -ForegroundColor Gray
    
    if (-Not (Test-Path $TestFile)) {
    Write-Host "  FAILED: Test file not found" -ForegroundColor Red
        $script:testsFailed++
        Write-Host ""
        return
    }
    
    # Run with trace flag
    $output = & .\mycc.exe -t $TestFile 2>&1 | Out-String
    
    if ($LASTEXITCODE -eq 0) {
    Write-Host "  PASSED: Execution successful" -ForegroundColor Green
        
        # Check for TRACE output
        if ($output -match "TRACE") {
            Write-Host "  TRACE output detected" -ForegroundColor Green
        } else {
            Write-Host "  WARNING: No TRACE output found" -ForegroundColor Yellow
        }
        
        # Check expected output if provided
        if ($ExpectedOutput -and $output -match [regex]::Escape($ExpectedOutput)) {
            Write-Host "  Expected output found: $ExpectedOutput" -ForegroundColor Green
        }
        
        $script:testsPassed++
    } else {
    Write-Host "  FAILED: Execution error" -ForegroundColor Red
    Write-Host "  Output: $output" -ForegroundColor Red
        $script:testsFailed++
    }
    
    Write-Host ""
}

# Run all tests
Write-Host "Starting Test Suite..." -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""

Run-Test "Test 1: Simple Variables" "test_simple_vars.c" "15"
Run-Test "Test 2: If-Else Statement" "test_if_else.c" "Greater"
Run-Test "Test 3: While Loop" "test_while_loop.c" "Sum = 10"
Run-Test "Test 4: For Loop" "test_for_loop.c" "Sum = 55"
Run-Test "Test 5: Factorial (Recursion)" "factorial_trace.c" "Result = 120"
Run-Test "Test 6: Fibonacci (Recursion)" "test_fibonacci.c" "Fibonacci = 13"
Run-Test "Test 7: Basic Trace" "test_trace.c" "10"

# Summary
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "  Test Summary" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "Tests Passed: $testsPassed" -ForegroundColor Green
Write-Host "Tests Failed: $testsFailed" -ForegroundColor $(if ($testsFailed -gt 0) { "Red" } else { "Green" })
Write-Host "Total Tests:  $($testsPassed + $testsFailed)" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan
Write-Host ""

# Test AST generation
Write-Host "Testing AST Generation..." -ForegroundColor Yellow
$astOutput = & .\mycc.exe -a test_simple_vars.c 2>&1 | Out-String
if ($LASTEXITCODE -eq 0 -and $astOutput -match "\{") {
    Write-Host "AST generation working" -ForegroundColor Green
} else {
    Write-Host "✗ AST generation failed" -ForegroundColor Red
}
Write-Host ""

# Test interpretation
Write-Host "Testing Interpretation..." -ForegroundColor Yellow
$interpOutput = & .\mycc.exe -i test_simple_vars.c 2>&1 | Out-String
if ($LASTEXITCODE -eq 0) {
    Write-Host "Interpretation working" -ForegroundColor Green
} else {
    Write-Host "✗ Interpretation failed" -ForegroundColor Red
}
Write-Host ""

# Exit with appropriate code
if ($testsFailed -gt 0) {
    exit 1
} else {
    Write-Host "All tests passed!" -ForegroundColor Green
    exit 0
}
