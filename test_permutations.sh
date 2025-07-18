#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Check for required arguments
if [ $# -lt 1 ] || [ $# -gt 2 ]; then
    echo -e "${RED}Usage: $0 <permutation_size> [num_permutations]${NC}"
    echo "Example: $0 5"
    echo "Example: $0 500 2000"
    exit 1
fi

PERM_SIZE=$1
NUM_PERMS=$2

# Validate permutation size
if ! [[ "$PERM_SIZE" =~ ^[0-9]+$ ]] || [ "$PERM_SIZE" -lt 1 ]; then
    echo -e "${RED}Error: Permutation size must be a positive integer${NC}"
    exit 1
fi

# Set default number of permutations
if [ -z "$NUM_PERMS" ]; then
    if [ $PERM_SIZE -le 5 ]; then
        NUM_PERMS=$(python3 -c "import math; print(math.factorial($PERM_SIZE))")
    else
        NUM_PERMS=5000 # Default for larger sizes
    fi
elif ! [[ "$NUM_PERMS" =~ ^[0-9]+$ ]] || [ "$NUM_PERMS" -lt 1 ]; then
    echo -e "${RED}Error: Number of permutations must be a positive integer${NC}"
    exit 1
fi

# Check if required programs exist
if [ ! -f "./push_swap" ]; then
    echo -e "${RED}Error: push_swap not found in current directory${NC}"
    exit 1
fi

if [ ! -f "./checker_linux" ]; then
    echo -e "${RED}Error: checker_linux not found in current directory${NC}"
    exit 1
fi

# Set operation thresholds based on input size
if [ $PERM_SIZE -le 5 ]; then
    MAX_MOVES=12
elif [ $PERM_SIZE -le 100 ]; then
    MAX_MOVES=700
elif [ $PERM_SIZE -le 500 ]; then
    MAX_MOVES=5500
else
    MAX_MOVES=10000 # Arbitrary high threshold for larger sizes
fi

# Output file for failed tests
FAIL_LOG="failed_tests.log"
> "$FAIL_LOG" # Clear the log file

# Function to generate a random permutation
generate_random_permutation() {
    local size=$1
    python3 -c "
import random
numbers = list(range(1, $size + 1))
random.shuffle(numbers)
print(' '.join(map(str, numbers)))
"
}

# Function to display ASCII progress bar
display_progress() {
    local current=$1
    local total=$2
    local bar_length=50
    local filled=$((current * bar_length / total))
    local empty=$((bar_length - filled))
    local percentage=$((current * 100 / total))
    
    printf "\r${CYAN}Testing permutations: ["
    printf "%${filled}s" | tr ' ' '#'
    printf "%${empty}s" | tr ' ' '-'
    printf "] %d/%d (%d%%)${NC}" $current $total $percentage
}

# Main script
echo -e "${CYAN}Testing random permutations of size $PERM_SIZE${NC}"
echo -e "${CYAN}Maximum allowed moves: $MAX_MOVES${NC}"
echo -e "${CYAN}Total permutations to test: $NUM_PERMS${NC}"
echo -e "${CYAN}=======================================${NC}"
echo ""

# Counters
good_count=0
ok_but_long_count=0
bad_count=0
invalid_count=0

# Generate and test permutations
for ((i=1; i<=NUM_PERMS; i++)); do
    # Generate a random permutation
    ARG=$(generate_random_permutation $PERM_SIZE)
    
    # Run push_swap and capture output
    moves_output=$(./push_swap $ARG 2>/dev/null)
    push_swap_exit_code=$?
    
    # Update progress bar
    display_progress $i $NUM_PERMS
    
    # Check if push_swap succeeded
    if [ $push_swap_exit_code -ne 0 ]; then
        echo -e "Permutation $i: $ARG" >> "$FAIL_LOG"
        echo -e "Error: push_swap failed with exit code $push_swap_exit_code" >> "$FAIL_LOG"
        echo -e "-------------------" >> "$FAIL_LOG"
        ((invalid_count++))
        continue
    fi
    
    # Count moves
    if [ -z "$moves_output" ]; then
        moves_count=0
    else
        moves_count=$(echo "$moves_output" | wc -l)
    fi
    
    # Test with checker
    checker_result=$(echo "$moves_output" | ./checker_linux $ARG 2>/dev/null)
    checker_exit_code=$?
    
    # Determine status and log failures
    if [ $checker_exit_code -eq 0 ] && [ "$checker_result" = "OK" ]; then
        if [ $moves_count -lt $MAX_MOVES ]; then
            ((good_count++))
        else
            ((ok_but_long_count++))
            echo -e "Permutation $i: $ARG" >> "$FAIL_LOG"
            echo -e "Error: Too many moves ($moves_count >= $MAX_MOVES)" >> "$FAIL_LOG"
            echo -e "Operations:\n$moves_output" >> "$FAIL_LOG"
            echo -e "Checker result: $checker_result" >> "$FAIL_LOG"
            echo -e "-------------------" >> "$FAIL_LOG"
        fi
    else
        ((bad_count++))
        echo -e "Permutation $i: $ARG" >> "$FAIL_LOG"
        echo -e "Error: Checker failed (result: $checker_result, exit code: $checker_exit_code)" >> "$FAIL_LOG"
        echo -e "Operations:\n$moves_output" >> "$FAIL_LOG"
        echo -e "-------------------" >> "$FAIL_LOG"
    fi
done

# Clear progress bar line
echo ""

# Display summary
echo -e "${CYAN}=======================================${NC}"
echo -e "${CYAN}Summary:${NC}"
printf "${GREEN}Perfect (< %d moves + checker OK): %d${NC}\n" $MAX_MOVES $good_count
printf "${YELLOW}OK but ≥ %d moves: %d${NC}\n" $MAX_MOVES $ok_but_long_count
printf "${RED}Checker failed: %d${NC}\n" $bad_count
printf "${RED}Push_swap errors: %d${NC}\n" $invalid_count
echo -e "Total tested: $NUM_PERMS"

if [ $good_count -eq $NUM_PERMS ] && [ $bad_count -eq 0 ] && [ $invalid_count -eq 0 ] && [ $ok_but_long_count -eq 0 ]; then
    echo ""
    printf "${GREEN}🎉 ALL TESTS PASSED PERFECTLY! 🎉${NC}\n"
    printf "${GREEN}All permutations solved in < %d moves!${NC}\n" $MAX_MOVES
elif [ $((good_count + ok_but_long_count)) -eq $NUM_PERMS ] && [ $bad_count -eq 0 ] && [ $invalid_count -eq 0 ]; then
    echo ""
    printf "${YELLOW}✅ All tests passed but some use ≥ %d moves${NC}\n" $MAX_MOVES
else
    echo ""
    printf "${RED}❌ Some tests failed. See %s for details${NC}\n" "$FAIL_LOG"
fi

# Display failure log if it exists and has content
if [ -s "$FAIL_LOG" ]; then
    echo ""
    echo -e "${CYAN}Failed tests logged in $FAIL_LOG${NC}"
fi