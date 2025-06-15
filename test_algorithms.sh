#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Algorithm list
ALGORITHMS=("chunk" "greedy" "k_sort" "radix" "lis" "queue")
ALGORITHM_NAMES=("Chunk Sort" "Greedy Sort" "K-Sort" "Radix Sort" "LIS Sort" "Queue Sort")

# Test sizes
SMALL_SIZES=(3 5 10)
MEDIUM_SIZES=(50 100 200)
LARGE_SIZES=(500)

# Global variables
MODE=""
CHECKER_AVAILABLE=false
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
CURRENT_COMPILED_ALGO=""

# Check if external checker is available
check_checker_availability() {
    if [ -f "./checker_linux" ]; then
        CHECKER_AVAILABLE=true
        echo -e "${GREEN}✓ External checker (checker_linux) found${NC}"
    elif [ -f "./checker" ]; then
        CHECKER_AVAILABLE=true
        echo -e "${GREEN}✓ Local checker found${NC}"
    else
        echo -e "${YELLOW}⚠ No checker found - evaluation mode will be limited${NC}"
    fi
}

# Function to prompt for mode selection
select_mode() {
    echo -e "${CYAN}================== MODE SELECTION ==================${NC}"
    echo -e "${YELLOW}Choose testing mode:${NC}"
    echo "1) Evaluate mode (compare with checker, count operations)"
    echo "2) Debug mode (show verbose output, no comparison)"
    echo ""
    
    while true; do
        read -p "Enter your choice (1 or 2): " choice
        case $choice in
            1)
                MODE="evaluate"
                echo -e "${GREEN}✓ Evaluation mode selected${NC}"
                break
                ;;
            2)
                MODE="debug"
                echo -e "${GREEN}✓ Debug mode selected${NC}"
                break
                ;;
            *)
                echo -e "${RED}Invalid choice. Please enter 1 or 2.${NC}"
                ;;
        esac
    done
    echo ""
}

# Function to compile algorithm only if not already compiled
compile_algorithm_if_needed() {
    local algo=$1
    local debug_suffix=$2
    local target="${algo}${debug_suffix}"
    
    # Special case: chunk algorithm uses default compilation
    if [ "$algo" = "chunk" ] && [ "$debug_suffix" = "" ]; then
        target="all"  # Use default make target for chunk algorithm
    fi
    
    if [ "$CURRENT_COMPILED_ALGO" = "$target" ]; then
        return 0
    fi
    
    echo -e "${BLUE}🔧 Compiling $target...${NC}"
    make $target > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Failed to compile $target${NC}"
        return 1
    fi
    
    CURRENT_COMPILED_ALGO="$target"
    echo -e "${GREEN}✓ $target compiled successfully${NC}"
    return 0
}

# Function to generate random array
generate_random_array() {
    local size=$1
    seq 1 $size | shuf | tr '\n' ' '
}

# Function to test algorithm in evaluate mode (no recompilation)
test_algorithm_evaluate() {
    local algo_name=$1
    local size=$2
    local test_array=$3
    
    # Run push_swap and capture output
    local operations=$(./push_swap $test_array 2>/dev/null)
    local push_swap_exit=$?
    
    if [ $push_swap_exit -ne 0 ]; then
        echo -e "${RED}✗ Push_swap failed for $algo_name (size $size)${NC}"
        return 1
    fi
    
    # Count operations
    local op_count=$(echo "$operations" | grep -E "^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$" | wc -l)
    
    # Test with checker if available
    local checker_result="N/A"
    local checker_status=0
    if [ "$CHECKER_AVAILABLE" = true ]; then
        if [ -z "$operations" ] || [ "$op_count" -eq 0 ]; then
            # No operations means already sorted - should be OK
            # Test with empty input to checker
            if [ -f "./checker_linux" ]; then
                echo -n "" | ./checker_linux $test_array > /dev/null 2>&1
                checker_status=$?
            else
                echo -n "" | ./checker $test_array > /dev/null 2>&1
                checker_status=$?
            fi
        else
            # Normal case with operations
            if [ -f "./checker_linux" ]; then
                echo "$operations" | ./checker_linux $test_array > /dev/null 2>&1
                checker_status=$?
            else
                echo "$operations" | ./checker $test_array > /dev/null 2>&1
                checker_status=$?
            fi
        fi
        
        if [ $checker_status -eq 0 ]; then
            checker_result="OK"
            printf "   Size %3d: %4d ops | Checker: ${GREEN}%s${NC}\n" "$size" "$op_count" "$checker_result"
            return 0
        else
            checker_result="KO"
            printf "   Size %3d: %4d ops | Checker: ${RED}%s${NC}\n" "$size" "$op_count" "$checker_result"
            return 1
        fi
    else
        printf "   Size %3d: %4d ops | Checker: ${YELLOW}%s${NC}\n" "$size" "$op_count" "$checker_result"
        return 0  # Don't count as failure if no checker available
    fi
}

# Function to test algorithm in debug mode (no recompilation)
test_algorithm_debug() {
    local algo_name=$1
    local size=$2
    local test_array=$3
    
    echo -e "${PURPLE}============ DEBUG: $algo_name (size $size) ============${NC}"
    echo -e "${CYAN}Input array:${NC} $(echo $test_array | cut -d' ' -f1-10)..."
    echo -e "${CYAN}Running with verbose output:${NC}"
    echo ""
    
    # Run with debug output
    ./push_swap $test_array
    local exit_code=$?
    
    echo ""
    echo -e "${PURPLE}===============================================${NC}"
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}✗ Algorithm failed with exit code $exit_code${NC}"
        return 1
    fi
    
    return 0
}

# Function to run comprehensive test for one algorithm
test_single_algorithm() {
    local algo=$1
    local algo_name=$2
    
    echo -e "\n${YELLOW}========== TESTING $algo_name ==========${NC}"
    
    # Compile algorithm once based on mode
    local debug_suffix=""
    if [ "$MODE" = "debug" ]; then
        debug_suffix="_debug"
    fi
    
    if ! compile_algorithm_if_needed "$algo" "$debug_suffix"; then
        echo -e "${RED}✗ Skipping $algo_name due to compilation failure${NC}"
        return 1
    fi
    
    local algo_passed=0
    local algo_total=0
    local algo_failed=0
    
    # Test different sizes based on mode
    if [ "$MODE" = "evaluate" ]; then
        echo -e "${BLUE}Running evaluation tests for $algo_name...${NC}"
        
        # Test multiple sizes in evaluate mode
        for size in "${SMALL_SIZES[@]}" "${MEDIUM_SIZES[@]}"; do
            for run in {1..3}; do
                local test_array=$(generate_random_array $size)
                ((algo_total++))
                ((TOTAL_TESTS++))
                
                if test_algorithm_evaluate "$algo_name" "$size" "$test_array"; then
                    ((algo_passed++))
                    ((PASSED_TESTS++))
                else
                    ((algo_failed++))
                    ((FAILED_TESTS++))
                fi
            done
        done
        
        # Test one large size
        if [ ${#LARGE_SIZES[@]} -gt 0 ]; then
            for size in "${LARGE_SIZES[@]}"; do
                local test_array=$(generate_random_array $size)
                ((algo_total++))
                ((TOTAL_TESTS++))
                
                if test_algorithm_evaluate "$algo_name" "$size" "$test_array"; then
                    ((algo_passed++))
                    ((PASSED_TESTS++))
                else
                    ((algo_failed++))
                    ((FAILED_TESTS++))
                fi
            done
        fi
        
        # Show algorithm results with proper color
        if [ $algo_failed -eq 0 ]; then
            echo -e "${GREEN}$algo_name Results: $algo_passed/$algo_total tests passed${NC}"
        else
            echo -e "${RED}$algo_name Results: $algo_passed/$algo_total tests passed ($algo_failed failed)${NC}"
        fi
        
    else
        # Debug mode - test one example of each size
        for size in 5 50 100; do
            local test_array=$(generate_random_array $size)
            
            if test_algorithm_debug "$algo_name" "$size" "$test_array"; then
                echo -e "${GREEN}✓ Debug test completed successfully${NC}"
            else
                echo -e "${RED}✗ Debug test failed${NC}"
            fi
            
            echo ""
            read -p "Press Enter to continue to next test, or 'q' to quit: " user_input
            if [ "$user_input" = "q" ]; then
                echo -e "${YELLOW}Testing interrupted by user${NC}"
                return 1
            fi
        done
    fi
    
    return 0
}

# Function to run all algorithm tests
run_all_tests() {
    echo -e "${CYAN}========== STARTING ALGORITHM TESTS ==========${NC}"
    echo -e "Mode: ${YELLOW}$MODE${NC}"
    echo -e "Checker available: ${YELLOW}$CHECKER_AVAILABLE${NC}"
    echo ""
    
    # Run tests for each algorithm
    for i in "${!ALGORITHMS[@]}"; do
        local algo="${ALGORITHMS[$i]}"
        local algo_name="${ALGORITHM_NAMES[$i]}"
        
        test_single_algorithm "$algo" "$algo_name"
        
        if [ "$?" -ne 0 ] && [ "$MODE" = "debug" ]; then
            echo -e "${YELLOW}Testing interrupted${NC}"
            break
        fi
        
        if [ "$MODE" = "evaluate" ]; then
            echo ""
        fi
    done
}

# Function to display final results
show_final_results() {
    if [ "$MODE" = "evaluate" ]; then
        echo -e "\n${CYAN}=============== FINAL RESULTS ===============${NC}"
        echo -e "Total tests: $TOTAL_TESTS"
        
        if [ $FAILED_TESTS -eq 0 ]; then
            echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
            echo -e "Failed: ${GREEN}$FAILED_TESTS${NC}"
            echo -e "${GREEN}🎉 All tests passed!${NC}"
        else
            echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
            echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
            echo -e "${RED}⚠ Some tests failed${NC}"
        fi
        
        # Calculate success rate
        if [ $TOTAL_TESTS -gt 0 ]; then
            local success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
            if [ $success_rate -eq 100 ]; then
                echo -e "Success rate: ${GREEN}$success_rate%${NC}"
            elif [ $success_rate -ge 90 ]; then
                echo -e "Success rate: ${YELLOW}$success_rate%${NC}"
            else
                echo -e "Success rate: ${RED}$success_rate%${NC}"
            fi
        fi
        
        echo -e "${CYAN}=============================================${NC}"
    else
        echo -e "\n${CYAN}=============== DEBUG SESSION COMPLETE ===============${NC}"
        echo -e "${GREEN}Debug testing completed successfully!${NC}"
        echo -e "${CYAN}=================================================${NC}"
    fi
}

# Function to run quick performance comparison
run_performance_comparison() {
    if [ "$MODE" = "evaluate" ]; then
        echo -e "\n${PURPLE}========== PERFORMANCE COMPARISON ==========${NC}"
        echo -e "${YELLOW}Testing all algorithms with same 100-element array...${NC}"
        
        local test_array=$(generate_random_array 100)
        echo -e "Test array: $(echo $test_array | cut -d' ' -f1-10)... (first 10 elements)"
        echo ""
        
        for i in "${!ALGORITHMS[@]}"; do
            local algo="${ALGORITHMS[$i]}"
            local algo_name="${ALGORITHM_NAMES[$i]}"
            
            echo -e "${BLUE}🔧 Compiling $algo for performance test...${NC}"
            if compile_algorithm_if_needed "$algo" ""; then
                local operations=$(./push_swap $test_array 2>/dev/null)
                local op_count=$(echo "$operations" | grep -E "^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$" | wc -l)
                
                # Test with checker for performance comparison
                if [ "$CHECKER_AVAILABLE" = true ]; then
                    local checker_status
                    if [ -z "$operations" ] || [ "$op_count" -eq 0 ]; then
                        # Handle 0 operations case
                        if [ -f "./checker_linux" ]; then
                            echo -n "" | ./checker_linux $test_array > /dev/null 2>&1
                            checker_status=$?
                        else
                            echo -n "" | ./checker $test_array > /dev/null 2>&1
                            checker_status=$?
                        fi
                    else
                        if [ -f "./checker_linux" ]; then
                            echo "$operations" | ./checker_linux $test_array > /dev/null 2>&1
                            checker_status=$?
                        else
                            echo "$operations" | ./checker $test_array > /dev/null 2>&1
                            checker_status=$?
                        fi
                    fi
                    
                    if [ $checker_status -eq 0 ]; then
                        printf "%-12s: %4d operations (${GREEN}OK${NC})\n" "$algo_name" "$op_count"
                    else
                        printf "%-12s: %4d operations (${RED}KO${NC})\n" "$algo_name" "$op_count"
                    fi
                else
                    printf "%-12s: %4d operations\n" "$algo_name" "$op_count"
                fi
            else
                printf "%-12s: ${RED}COMPILE ERROR${NC}\n" "$algo_name"
            fi
        done
        
        echo -e "${PURPLE}===========================================${NC}"
    fi
}

# Main function
main() {
    echo -e "${CYAN}🧪 PUSH_SWAP ALGORITHM TESTING SUITE 🧪${NC}"
    echo ""
    
    # Check prerequisites
    if [ ! -f "Makefile" ]; then
        echo -e "${RED}Error: No Makefile found${NC}"
        exit 1
    fi
    
    check_checker_availability
    select_mode
    
    # Ask if user wants performance comparison (only in evaluate mode)
    local run_perf_comp=false
    if [ "$MODE" = "evaluate" ]; then
        echo -e "${YELLOW}Do you want to run performance comparison at the end? (y/n)${NC}"
        read -p "Choice: " perf_choice
        if [ "$perf_choice" = "y" ] || [ "$perf_choice" = "Y" ]; then
            run_perf_comp=true
        fi
        echo ""
    fi
    
    # Run the tests
    run_all_tests
    
    # Show results
    show_final_results
    
    # Run performance comparison if requested
    if [ "$run_perf_comp" = true ]; then
        run_performance_comparison
    fi
}

# Run main function
main "$@"