#!/bin/bash
# filepath: /home/dlesieur/Documents/projects-42/Push_swap/dylan/ulysse/ulysse/test_push_swap.sh

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Path to push_swap and checker programs
PUSH_SWAP="./push_swap"
CHECKER="./checker"

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: push_swap program not found at $PUSH_SWAP${NC}"
    exit 1
fi

# Function to test push_swap with given arguments
test_push_swap() {
    local test_name=$1
    local expected_result=$2
    local args=("${@:3}")
    
    echo -e "${BLUE}Test: $test_name${NC}"
    echo -n "Arguments: "
    echo "${args[@]}"
    
    # Run push_swap and capture output and return code
    output=$("$PUSH_SWAP" "${args[@]}" 2>&1)
    return_code=$?
    # Count number of operations
    op_count=$(echo "$output" | grep -E "^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$" | wc -l)
    
    # Check if we expect an error
    if [ "$expected_result" = "error" ]; then
        if [[ "$output" == *"Error"* ]]; then
            echo -e "${GREEN}✓ Test passed: Error message received as expected${NC}"
        else
            echo -e "${RED}✗ Test failed: Expected error but got:${NC}"
            echo "$output"
        fi
    else
        # Check if the output is sorted (when checker is available)
        if [ -f "$CHECKER" ]; then
            echo "$output" | "$CHECKER" "${args[@]}" > /dev/null 2>&1
            if [ $? -eq 0 ]; then
                echo -e "${GREEN}✓ Test passed: Numbers sorted correctly${NC}"
            else
                echo -e "${RED}✗ Test failed: Numbers not sorted correctly${NC}"
            fi
        fi
        
        echo "Number of operations: $op_count"
        
        # For already sorted input, expect 0 operations
        if [ "$expected_result" = "already_sorted" ] && [ "$op_count" -ne 0 ]; then
            echo -e "${YELLOW}⚠ Warning: Expected 0 operations for already sorted input${NC}"
        fi
    fi
    
    echo "----------------------------------------"
}

echo -e "${YELLOW}====== PUSH_SWAP TESTING SCRIPT ======${NC}"

# Test 1: Empty input
test_push_swap "Empty input" "error"

# Test 2: Single number
test_push_swap "Single number" "sorted" 42

# Test 3: Already sorted numbers
test_push_swap "Already sorted numbers" "already_sorted" 1 2 3 4 5

# Test 4: Reverse sorted numbers
test_push_swap "Reverse sorted numbers" "sorted" 5 4 3 2 1

# Test 5: Duplicate numbers
test_push_swap "Duplicate numbers" "error" 1 2 3 3 5

# Test 6: Non-numeric input
test_push_swap "Non-numeric input" "error" 1 2 3 a 5

# Test 7: Numbers exceeding INT_MAX
test_push_swap "Number exceeding INT_MAX" "error" 1 2 2147483648

# Test 8: Numbers below INT_MIN
test_push_swap "Number below INT_MIN" "error" 1 -2147483649 3

# Test 9: Very large input set (simple version)
large_set=($(seq 1 100 | sort -R))
test_push_swap "Large input set (100 numbers)" "sorted" "${large_set[@]}"

# Test 10: Mixed positive and negative numbers
test_push_swap "Mixed positive and negative numbers" "sorted" -5 3 -2 7 -10

# Test 11: Input with leading plus sign
test_push_swap "Input with leading plus sign" "sorted" +1 +2 +3

# Test 12: Random 3 numbers
test_push_swap "Random 3 numbers" "sorted" 3 1 2

# Test 13: Random 5 numbers
test_push_swap "Random 5 numbers" "sorted" 4 2 5 1 3

# Test 14: Zero handling
test_push_swap "Zero handling" "sorted" 0 -1 1

# Test 15: Close numbers
test_push_swap "Close numbers" "sorted" 1 2 3 4 5 6

echo -e "${YELLOW}====== ADDITIONAL ERROR TESTING ======${NC}"

# Invalid Characters Tests
echo -e "${BLUE}=== Testing Invalid Characters ====${NC}"
test_push_swap "Non-numeric input" "error" abc
test_push_swap "Mixed valid/invalid input" "error" 1 2 abc
test_push_swap "String input" "error" "hello world"
test_push_swap "Decimal numbers" "error" 1.5
test_push_swap "Mixed integer/decimal" "error" 1 2.0
test_push_swap "Just a plus sign" "error" +
test_push_swap "Just a minus sign" "error" -
test_push_swap "Empty string" "error" ""
test_push_swap "Just whitespace" "error" " "
test_push_swap "Mixed numbers and letters" "error" 1a2
test_push_swap "Number followed by letters" "error" 42foo

# Duplicates Tests
echo -e "${BLUE}=== Testing Duplicates ====${NC}"
test_push_swap "Simple duplicate" "error" 1 2 1
test_push_swap "Duplicate in middle" "error" 5 3 5 1
test_push_swap "Duplicate zeros" "error" 0 0
test_push_swap "Duplicate negatives" "error" -1 -1
test_push_swap "Multiple values with one duplicate" "error" 1 2 3 2 4

# Out of Range Values Tests
echo -e "${BLUE}=== Testing Out of Range Values ====${NC}"
test_push_swap "INT_MAX + 1" "error" 2147483648
test_push_swap "INT_MIN - 1" "error" -2147483649
test_push_swap "Very large number" "error" 999999999999
test_push_swap "Very large negative" "error" -999999999999
test_push_swap "Slightly over INT_MAX" "error" 21474836471

# Empty or No Arguments Tests
echo -e "${BLUE}=== Testing Empty Arguments ====${NC}"
test_push_swap "Empty string argument" "error" ""

# Leading Zeros and Signs Tests
echo -e "${BLUE}=== Testing Leading Zeros and Signs ====${NC}"
test_push_swap "Leading zeros" "sorted" 007
test_push_swap "Plus sign" "sorted" +42
test_push_swap "Double plus" "error" ++42
test_push_swap "Double minus" "error" --42
test_push_swap "Mixed signs (plus-minus)" "error" +-42
test_push_swap "Mixed signs (minus-plus)" "error" -+42

# Boundary Values Tests
echo -e "${BLUE}=== Testing Boundary Values ====${NC}"
test_push_swap "INT_MAX" "sorted" 2147483647
test_push_swap "INT_MIN" "sorted" -2147483648
test_push_swap "Zero" "sorted" 0
test_push_swap "Negative zero" "sorted" -0
test_push_swap "Positive zero" "sorted" +0

# Whitespace Handling Tests
echo -e "${BLUE}=== Testing Whitespace Handling ====${NC}"
test_push_swap "Single string with spaces" "error" "1 2 3"

# Special Number Formats Tests
echo -e "${BLUE}=== Testing Special Number Formats ====${NC}"
test_push_swap "Leading zeros" "sorted" 0001
test_push_swap "Leading zeros with minus" "sorted" -0001
test_push_swap "Leading zeros with plus" "sorted" +0001

# Performance Tests
echo -e "${BLUE}=== Performance Tests ====${NC}"
test_push_swap "3 numbers performance" "sorted" 3 2 1
test_push_swap "5 numbers performance" "sorted" 5 4 3 2 1

# Generate random arrays of various sizes
echo -e "${BLUE}=== Random Array Tests ====${NC}"
random_small=($(seq 1 5 | sort -R))
test_push_swap "Random small array (5)" "sorted" "${random_small[@]}"

if [ -f "$CHECKER" ]; then
    echo -e "${BLUE}=== Complex Stack Operations Tests ====${NC}"
    # Test a simple sequence of operations
    echo "sa\npb\nra\nrb\npa\nrra" | "$CHECKER" 1 2 3
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Test passed: Checker operations worked correctly${NC}"
    else
        echo -e "${RED}✗ Test failed: Checker operations failed${NC}"
    fi
fi

echo -e "${YELLOW}====== TESTING COMPLETE ======${NC}"