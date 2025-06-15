#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Paths
CHECKER="./checker"
CHECKER_LINUX="./checker_linux"
PUSH_SWAP="./push_swap"

# Check if all required programs exist
check_prerequisites() {
    if [ ! -f "$CHECKER" ]; then
        echo -e "${RED}❌ Error: $CHECKER not found${NC}"
        echo "Run 'make bonus' to build the checker"
        exit 1
    fi
    
    if [ ! -f "$CHECKER_LINUX" ]; then
        echo -e "${YELLOW}⚠ Warning: $CHECKER_LINUX not found - using basic validation${NC}"
        CHECKER_LINUX=""
    fi
    
    if [ ! -f "$PUSH_SWAP" ]; then
        echo -e "${YELLOW}⚠ Warning: $PUSH_SWAP not found - limited testing${NC}"
    fi
}

# Compact test function
test_checker_compact() {
    local test_name="$1"
    local operations="$2"
    local args=("${@:3}")
    
    ((TOTAL_TESTS++))
    
    # Get our checker output
    local our_output
    local our_exit_code
    our_output=$(echo -e "$operations" | $CHECKER "${args[@]}" 2>&1)
    our_exit_code=$?
    
    # Get reference checker output if available
    if [ -n "$CHECKER_LINUX" ]; then
        local ref_output
        local ref_exit_code
        ref_output=$(echo -e "$operations" | $CHECKER_LINUX "${args[@]}" 2>&1)
        ref_exit_code=$?
        
        # Compare outputs and exit codes
        if [ "$our_output" = "$ref_output" ] && [ "$our_exit_code" = "$ref_exit_code" ]; then
            echo -e "   ${GREEN}✓${NC} $test_name"
            ((PASSED_TESTS++))
        else
            echo -e "   ${RED}✗${NC} $test_name (got: '$our_output' exit:$our_exit_code, expected: '$ref_output' exit:$ref_exit_code)"
            ((FAILED_TESTS++))
        fi
    else
        # Without reference, just check for basic sanity
        if [ "$our_output" = "OK" ] || [ "$our_output" = "KO" ] || [ "$our_output" = "Error" ]; then
            echo -e "   ${GREEN}✓${NC} $test_name ($our_output)"
            ((PASSED_TESTS++))
        else
            echo -e "   ${RED}✗${NC} $test_name (invalid output: '$our_output')"
            ((FAILED_TESTS++))
        fi
    fi
}

# Test with push_swap generated operations (compact)
test_with_push_swap_compact() {
    local test_name="$1"
    local args=("${@:2}")
    
    if [ ! -f "$PUSH_SWAP" ]; then
        return
    fi
    
    ((TOTAL_TESTS++))
    
    # Generate operations with push_swap
    local operations
    operations=$($PUSH_SWAP "${args[@]}" 2>/dev/null)
    local ps_exit_code=$?
    
    if [ $ps_exit_code -ne 0 ]; then
        operations=""
    fi
    
    # Test our checker
    local our_output
    our_output=$(echo "$operations" | $CHECKER "${args[@]}" 2>&1)
    local our_exit_code=$?
    
    # Test reference checker if available
    if [ -n "$CHECKER_LINUX" ]; then
        local ref_output
        ref_output=$(echo "$operations" | $CHECKER_LINUX "${args[@]}" 2>&1)
        local ref_exit_code=$?
        
        if [ "$our_output" = "$ref_output" ] && [ "$our_exit_code" = "$ref_exit_code" ]; then
            echo -e "   ${GREEN}✓${NC} $test_name (${#args[@]} elements)"
            ((PASSED_TESTS++))
        else
            echo -e "   ${RED}✗${NC} $test_name (${#args[@]} elements) - mismatch"
            ((FAILED_TESTS++))
        fi
    else
        # Expect OK for valid push_swap operations
        if [ "$our_output" = "OK" ]; then
            echo -e "   ${GREEN}✓${NC} $test_name (${#args[@]} elements)"
            ((PASSED_TESTS++))
        else
            echo -e "   ${RED}✗${NC} $test_name (${#args[@]} elements) - not OK"
            ((FAILED_TESTS++))
        fi
    fi
}

# Generate random array
generate_random_array() {
    local size=$1
    seq 1 $size | shuf | tr '\n' ' '
}

# Main testing function with progress indicators
run_tests() {
    echo -e "${CYAN}🧪 CHECKER TESTING SUITE${NC}"
    echo ""
    
    check_prerequisites
    echo ""
    
    # Test 1: Valid operations
    echo -e "${BLUE}=== Valid Operations Tests ===${NC}"
    test_checker_compact "Simple swap" "sa" 2 1
    test_checker_compact "Push operations" "pb\npa" 1 2 3
    test_checker_compact "Complex sequence" "pb\nsa\nra\npa" 3 1 2
    test_checker_compact "All operations" "sa\nsb\nss\npa\npb\nra\nrb\nrr\nrra\nrrb\nrrr" 1 2 3
    test_checker_compact "Rotation cycle" "ra\nrra" 1 2 3
    test_checker_compact "Push cycle" "pb\npa" 1 2 3
    
    # Test 2: Invalid operations
    echo -e "${BLUE}=== Invalid Operations Tests ===${NC}"
    test_checker_compact "Invalid operation" "invalid" 1 2 3
    test_checker_compact "Partial operation" "s" 1 2 3
    test_checker_compact "Unknown command" "xyz" 1 2 3
    test_checker_compact "Mixed valid/invalid" "sa\ninvalid\nra" 1 2 3
    test_checker_compact "Empty operation" "" 1 2 3
    
    # Test 3: Edge cases
    echo -e "${BLUE}=== Edge Cases Tests ===${NC}"
    test_checker_compact "Single element" "sa" 42
    test_checker_compact "Already sorted" "" 1 2 3 4 5
    test_checker_compact "Large numbers" "sa" 2147483647 -2147483648
    test_checker_compact "Two elements" "sa" 2 1
    test_checker_compact "Three elements sorted" "sa\nra\nsa\nrra" 3 1 2
    
    # Test 4: Error conditions
    echo -e "${BLUE}=== Error Conditions Tests ===${NC}"
    test_checker_compact "No arguments" "sa"
    test_checker_compact "Invalid numbers" "sa" abc 123
    test_checker_compact "Duplicate numbers" "sa" 1 2 2 3
    test_checker_compact "Out of range" "sa" 2147483648
    test_checker_compact "Negative out of range" "sa" -2147483649
    
    # Test 5: Correct sorting results
    echo -e "${BLUE}=== Correct Sorting Tests ===${NC}"
    test_checker_compact "2-element sort" "sa" 2 1
    test_checker_compact "3-element sort complete" "pb\nsa\npa\nra\nsa\nrra" 3 1 2
    test_checker_compact "Identity operations" "ra\nrra" 1 2 3
    test_checker_compact "Cancel operations" "pb\npa" 1 2 3
    test_checker_compact "Double swap cancel" "sa\nsa" 2 1
    
    # Test 6: Incorrect sorting results (should be KO)
    echo -e "${BLUE}=== Incorrect Sorting Tests ===${NC}"
    test_checker_compact "Wrong operation" "ra" 2 1
    test_checker_compact "Incomplete sort" "pb" 3 1 2
    test_checker_compact "Wrong direction" "rra\nsa" 1 2 3
    test_checker_compact "Partial sort only" "sa" 3 1 2
    
    # Test 7: Push_swap integration
    if [ -f "$PUSH_SWAP" ]; then
        echo -e "${BLUE}=== Push_swap Integration Tests ===${NC}"
        test_with_push_swap_compact "Small random 1" $(generate_random_array 5)
        test_with_push_swap_compact "Small random 2" $(generate_random_array 5)
        test_with_push_swap_compact "Medium random 1" $(generate_random_array 25)
        test_with_push_swap_compact "Medium random 2" $(generate_random_array 25)
        test_with_push_swap_compact "Large random" $(generate_random_array 100)
        test_with_push_swap_compact "Already sorted" 1 2 3 4 5 6 7 8 9 10
        test_with_push_swap_compact "Reverse sorted" 10 9 8 7 6 5 4 3 2 1
        test_with_push_swap_compact "Single element" 42
        test_with_push_swap_compact "Two elements" 2 1
    fi
    
    # Test 8: Stress testing (compact)
    echo -e "${BLUE}=== Stress Tests ===${NC}"
    for i in {1..5}; do
        local random_args=($(generate_random_array 10))
        test_with_push_swap_compact "Stress $i" "${random_args[@]}"
    done
    
    # Test 9: Boundary conditions
    echo -e "${BLUE}=== Boundary Tests ===${NC}"
    test_checker_compact "Long operation sequence" "$(printf 'ra\n%.0s' {1..50})" 1 2 3 4 5
    test_checker_compact "Mixed newlines" "sa\n\nra\n" 2 1 3
    test_checker_compact "Whitespace operations" "  sa  \n  ra  " 2 1 3
    test_checker_compact "Empty lines" "\nsa\n\nra\n" 2 1 3
}

# Show final results with summary
show_results() {
    echo ""
    echo -e "${CYAN}=============== FINAL RESULTS ===============${NC}"
    echo -e "Total tests: $TOTAL_TESTS"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
        echo -e "Failed: ${GREEN}$FAILED_TESTS${NC}"
        echo -e "${GREEN}🎉 All tests passed! Your checker works perfectly! 🎉${NC}"
    else
        echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
        echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
        echo -e "${RED}⚠ Some tests failed - check implementation${NC}"
    fi
    
    local success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "Success rate: ${YELLOW}$success_rate%${NC}"
    echo -e "${CYAN}=============================================${NC}"
    
    # Show quick summary of what was tested
    echo ""
    echo -e "${PURPLE}Test Coverage Summary:${NC}"
    echo -e "• Valid operations and sequences"
    echo -e "• Invalid operation handling"
    echo -e "• Edge cases and boundary conditions"
    echo -e "• Error detection and reporting"
    echo -e "• Integration with push_swap"
    echo -e "• Stress testing with random inputs"
}

# Run the complete test suite
run_tests
show_results