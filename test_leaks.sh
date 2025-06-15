#!/bin/bash

echo "🧪 Comprehensive Memory Leak Testing..."

# Test different sizes
SIZES=(3 5 10 50 100 200 500)
ALGORITHMS=("chunk_debug" "greedy_debug" "k_sort_debug" "radix_debug" "lis_debug")

for size in "${SIZES[@]}"; do
    echo "📊 Testing size: $size"
    SHUF=$(seq 1 $size | shuf)
    
    echo "  🔍 Basic leak check..."
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 \
        ./push_swap $SHUF > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo "  ✅ No leaks detected for size $size"
    else
        echo "  ❌ LEAKS DETECTED for size $size!"
        echo "  Running detailed analysis..."
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
            ./push_swap $SHUF
        break
    fi
done

echo "🏁 Testing different algorithms..."
for algo in "${ALGORITHMS[@]}"; do
    echo "📊 Testing algorithm: $algo"
    make $algo > /dev/null 2>&1
    
    SHUF=$(seq 1 100 | shuf)
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 \
        ./push_swap $SHUF > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo "  ✅ No leaks in $algo"
    else
        echo "  ❌ LEAKS in $algo!"
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
            ./push_swap $SHUF
        break
    fi
done

echo "🎯 Edge case testing..."
# Test edge cases
echo "  Testing size 2..."
valgrind --leak-check=full --error-exitcode=1 ./push_swap 2 1 > /dev/null 2>&1

echo "  Testing already sorted..."
valgrind --leak-check=full --error-exitcode=1 ./push_swap 1 2 3 4 5 > /dev/null 2>&1

echo "  Testing reverse sorted..."
valgrind --leak-check=full --error-exitcode=1 ./push_swap 5 4 3 2 1 > /dev/null 2>&1

echo "✅ Comprehensive leak testing completed!"
