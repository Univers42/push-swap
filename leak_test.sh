#!/bin/bash

echo "🧪 Quick Memory Leak Testing..."

# Function to run valgrind test
run_leak_test() {
    local size=$1
    local algo=$2
    local count=${3:-5}
    
    echo "  Testing $algo with size $size ($count runs)..."
    
    for i in $(seq 1 $count); do
        SHUF=$(seq 1 $size | shuf)
        valgrind --leak-check=full --error-exitcode=1 --quiet \
            ./push_swap $SHUF > /dev/null 2>&1
        
        if [ $? -ne 0 ]; then
            echo "  ❌ LEAK DETECTED in $algo (size $size, run $i)!"
            echo "  Running detailed analysis..."
            valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
                ./push_swap $SHUF
            return 1
        fi
    done
    
    echo "  ✅ $algo (size $size) - No leaks"
    return 0
}

# Test different algorithms quickly
ALGORITHMS=("chunk" "greedy" "k_sort" "radix" "lis")
SIZES=(5 50 200)

for algo in "${ALGORITHMS[@]}"; do
    echo "📊 Testing $algo algorithm..."
    make $algo > /dev/null 2>&1
    
    for size in "${SIZES[@]}"; do
        run_leak_test $size $algo 3
        if [ $? -ne 0 ]; then
            exit 1
        fi
    done
done

# Test edge cases
echo "🎯 Testing edge cases..."
make chunk > /dev/null 2>&1

echo "  Testing size 2..."
valgrind --leak-check=full --error-exitcode=1 --quiet ./push_swap 2 1 > /dev/null 2>&1
[ $? -eq 0 ] && echo "  ✅ Size 2 - No leaks" || echo "  ❌ Size 2 - LEAK!"

echo "  Testing already sorted..."
valgrind --leak-check=full --error-exitcode=1 --quiet ./push_swap 1 2 3 4 5 > /dev/null 2>&1
[ $? -eq 0 ] && echo "  ✅ Already sorted - No leaks" || echo "  ❌ Already sorted - LEAK!"

echo "  Testing reverse sorted..."
valgrind --leak-check=full --error-exitcode=1 --quiet ./push_swap 10 9 8 7 6 5 4 3 2 1 > /dev/null 2>&1
[ $? -eq 0 ] && echo "  ✅ Reverse sorted - No leaks" || echo "  ❌ Reverse sorted - LEAK!"

echo "✅ All leak tests completed!"
