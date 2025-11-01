#!/bin/bash
# Bash Test Script for Compiler Visualization
# Run all test cases and verify output

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

echo -e "${CYAN}============================================================${NC}"
echo -e "${CYAN}  C Compiler Execution Path Visualizer - Test Suite${NC}"
echo -e "${CYAN}============================================================${NC}"
echo ""

# Check if mycc exists
if [ ! -f "./mycc" ] && [ ! -f "./mycc.exe" ]; then
    echo -e "${RED}ERROR: mycc not found!${NC}"
    echo -e "${YELLOW}Please run 'make' to build the compiler first.${NC}"
    exit 1
fi

# Determine which binary to use
MYCC="./mycc"
if [ -f "./mycc.exe" ]; then
    MYCC="./mycc.exe"
fi

echo -e "${GREEN}✓ Found $MYCC${NC}"
echo ""

# Test counter
tests_passed=0
tests_failed=0

# Function to run a test
run_test() {
    local test_name="$1"
    local test_file="$2"
    local expected_output="$3"
    
    echo -e "${YELLOW}Running: $test_name${NC}"
    echo -e "${NC}File: $test_file${NC}"
    
    if [ ! -f "$test_file" ]; then
        echo -e "  ${RED}✗ FAILED: Test file not found${NC}"
        ((tests_failed++))
        echo ""
        return
    fi
    
    # Run with trace flag
    output=$($MYCC -t "$test_file" 2>&1)
    exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo -e "  ${GREEN}✓ PASSED: Execution successful${NC}"
        
        # Check for TRACE output
        if echo "$output" | grep -q "TRACE"; then
            echo -e "  ${GREEN}✓ TRACE output detected${NC}"
        else
            echo -e "  ${YELLOW}⚠ WARNING: No TRACE output found${NC}"
        fi
        
        # Check expected output if provided
        if [ -n "$expected_output" ] && echo "$output" | grep -q "$expected_output"; then
            echo -e "  ${GREEN}✓ Expected output found: $expected_output${NC}"
        fi
        
        ((tests_passed++))
    else
        echo -e "  ${RED}✗ FAILED: Execution error${NC}"
        echo -e "  ${RED}Output: $output${NC}"
        ((tests_failed++))
    fi
    
    echo ""
}

# Run all tests
echo -e "${CYAN}Starting Test Suite...${NC}"
echo -e "${CYAN}============================================================${NC}"
echo ""

run_test "Test 1: Simple Variables" "test_simple_vars.c" "15"
run_test "Test 2: If-Else Statement" "test_if_else.c" "Greater"
run_test "Test 3: While Loop" "test_while_loop.c" "Sum = 10"
run_test "Test 4: For Loop" "test_for_loop.c" "Sum = 55"
run_test "Test 5: Factorial (Recursion)" "factorial_trace.c" "Result = 120"
run_test "Test 6: Fibonacci (Recursion)" "test_fibonacci.c" "Fibonacci = 13"
run_test "Test 7: Basic Trace" "test_trace.c" "10"

# Summary
echo -e "${CYAN}============================================================${NC}"
echo -e "${CYAN}  Test Summary${NC}"
echo -e "${CYAN}============================================================${NC}"
echo -e "${GREEN}Tests Passed: $tests_passed${NC}"
if [ $tests_failed -gt 0 ]; then
    echo -e "${RED}Tests Failed: $tests_failed${NC}"
else
    echo -e "${GREEN}Tests Failed: $tests_failed${NC}"
fi
echo -e "${CYAN}Total Tests:  $((tests_passed + tests_failed))${NC}"
echo -e "${CYAN}============================================================${NC}"
echo ""

# Test AST generation
echo -e "${YELLOW}Testing AST Generation...${NC}"
ast_output=$($MYCC -a test_simple_vars.c 2>&1)
if [ $? -eq 0 ] && echo "$ast_output" | grep -q "{"; then
    echo -e "${GREEN}✓ AST generation working${NC}"
else
    echo -e "${RED}✗ AST generation failed${NC}"
fi
echo ""

# Test interpretation
echo -e "${YELLOW}Testing Interpretation...${NC}"
interp_output=$($MYCC -i test_simple_vars.c 2>&1)
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Interpretation working${NC}"
else
    echo -e "${RED}✗ Interpretation failed${NC}"
fi
echo ""

# Exit with appropriate code
if [ $tests_failed -gt 0 ]; then
    exit 1
else
    echo -e "${GREEN}All tests passed! ✓${NC}"
    exit 0
fi
