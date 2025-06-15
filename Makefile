# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 14:02:06 by ugerkens          #+#    #+#              #
#    Updated: 2025/06/15 23:13:30 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================ #

CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -Iinclude -g3
RM					=	rm -rf

# Program names
PUSH_SWAP			=	push_swap
CHECKER				=	checker

# Library configuration
LIBFT_DIR			=	include/libft
LIBFT_FILE			=	$(LIBFT_DIR)/libft.a
LIBS				=	$(LIBFT_FILE)

# Include directories
INCLUDES			=	-I include \
						-I $(LIBFT_DIR)

CFLAGS				+=	$(INCLUDES)

# ============================= SOURCE FILES =============================== #

# Find all C files recursively in src directory (including debugger)
PUSH_SWAP_SRCS		=	$(shell find src -name "*.c" | grep -v checker_bonus | grep -v debug_stub.c | grep -v "src/debug/")
CHECKER_SRCS		=	src/checker_bonus/checker_bonus.c \
						src/checker_bonus/checker_init.c \
						src/checker_bonus/checker_operations.c \
						src/checker_bonus/checker_stack_ops.c \
						src/checker_bonus/string_to_op.c \
						src/stack/init_push_swap.c \
						src/stack/convert_stack.c \
						src/push_swap/parser.c \
						src/push_swap/parser_utils.c \
						src/push_swap/collector_data.c \
						src/push_swap/op_utils.c \
						src/utils/get.c \
						src/utils/check.c \
						src/utils/exit.c

# ================================ OBJECTS ================================== #

# Object directories
OBJ_DIR				=	obj

# Object files with proper source mapping
PUSH_SWAP_OBJS		=	$(PUSH_SWAP_SRCS:src/%.c=$(OBJ_DIR)/%.o)
CHECKER_OBJS		=	$(CHECKER_SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Header dependencies
HEADERS				=	$(shell find include -name "*.h")

# ================================= RULES =================================== #

.PHONY: all clean fclean re bonus lib_clean lib_fclean debug test test-algos test-leaks

# Default target
all: $(PUSH_SWAP)

# Bonus target
bonus: $(CHECKER)

# Both programs
both: $(PUSH_SWAP) $(CHECKER)

# Push swap program
$(PUSH_SWAP): $(LIBS) $(PUSH_SWAP_OBJS)
	@echo "🔗 Linking $(PUSH_SWAP)..."
	@$(CC) $(CFLAGS) $(PUSH_SWAP_OBJS) $(LIBS) -o $@
	@echo "✅ $(PUSH_SWAP) compiled successfully! 🎉"

# Checker program
$(CHECKER): $(LIBS) $(CHECKER_OBJS)
	@echo "🔗 Linking $(CHECKER)..."
	@$(CC) $(CFLAGS) $(CHECKER_OBJS) $(LIBS) -o $@
	@echo "✅ $(CHECKER) compiled successfully! 🎉"

# Object compilation rule - this is the key fix
$(OBJ_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# ============================== LIBRARIES ================================== #

# Build libraries
$(LIBFT_FILE):
	@echo "📚 Building libft..."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# Library cleanup
lib_clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

lib_fclean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

# ============================== CLEANUP ================================== #

# Clean object files
clean: lib_clean
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ_DIR)

# Full clean
fclean: clean lib_fclean
	@echo "🗑️  Removing executables..."
	@$(RM) $(PUSH_SWAP) $(CHECKER)

# Rebuild everything
re: fclean all

# =============================== DEBUGGING ================================= #

# Debug build
debug: CFLAGS += -g3 -DDEBUG -fsanitize=address
debug: re

# ================================ TESTING ================================== #

# Run algorithm testing suite
test-algos: $(PUSH_SWAP)
	@if [ -f "test_algorithms.sh" ]; then \
		echo "🧪 Running algorithm testing suite..."; \
		chmod +x test_algorithms.sh; \
		./test_algorithms.sh; \
	else \
		echo "❌ Algorithm test script not found"; \
	fi

# Run tests
test: $(PUSH_SWAP) $(CHECKER)
	@if [ -f "test_push_swap.sh" ]; then \
		echo "🧪 Running tests..."; \
		chmod +x test_push_swap.sh; \
		./test_push_swap.sh; \
	else \
		echo "❌ Test script not found"; \
	fi

# Run checker testing suite
test-checker: $(CHECKER)
	@if [ -f "test_checker.sh" ]; then \
		echo "🧪 Running checker testing suite..."; \
		chmod +x test_checker.sh; \
		./test_checker.sh; \
	else \
		echo "❌ Checker test script not found"; \
	fi

# Run memory leak tests
test-leaks: $(PUSH_SWAP)
	@if [ -f "leak_test.sh" ]; then \
		echo "🧪 Running leak tests..."; \
		chmod +x leak_test.sh; \
		./leak_test.sh; \
	else \
		echo "❌ Leak test script not found"; \
	fi

# ============================== UTILITIES ================================== #

# Show help
help:
	@echo "🎯 Available targets:"
	@echo "   all          - Build push_swap (default)"
	@echo "   bonus        - Build checker"
	@echo "   both         - Build both programs"
	@echo "   clean        - Remove object files"
	@echo "   fclean       - Remove object files and executables"
	@echo "   re           - Rebuild everything"
	@echo "   debug        - Build with debug symbols and sanitizer"
	@echo "   test         - Run basic test suite"
	@echo "   test-algos   - Run comprehensive algorithm testing suite"
	@echo "   test-checker - Run comprehensive checker testing suite"
	@echo "   test-leaks   - Run memory leak tests"
	@echo "   list-sources - Show source files that will be compiled"
	@echo "   info         - Show compilation information"
	@echo "   help         - Show this help message"

# ============================== ALGORITHM MODES ============================== #

# Algorithm-only modes (evaluation - just print operations)
chunk: CFLAGS += "-DMODE=0"
chunk: re
	@echo "📦 Chunk algorithm (evaluation mode)"

greedy: CFLAGS += "-DMODE=1"
greedy: re
	@echo "🧠 Greedy algorithm (evaluation mode)"

k_sort: CFLAGS += "-DMODE=4"
k_sort: re
	@echo "📊 K-Sort algorithm (evaluation mode)"

radix: CFLAGS += "-DMODE=8"
radix: re
	@echo "🔢 Radix algorithm (evaluation mode)"

lis: CFLAGS += "-DMODE=12"
lis: re
	@echo "🔗 LIS algorithm (evaluation mode)"

queue: CFLAGS += "-DMODE=5"
queue: re
	@echo "🚛 Queue algorithm (evaluation mode)"

# Algorithm + Debug modes (simple debug ON/OFF)
chunk_debug: CFLAGS += "-DMODE=16"
chunk_debug: re
	@echo "📦 Chunk algorithm + debug mode"

greedy_debug: CFLAGS += "-DMODE=17"
greedy_debug: re
	@echo "🧠 Greedy algorithm + debug mode"

k_sort_debug: CFLAGS += "-DMODE=20"
k_sort_debug: re
	@echo "📊 K-Sort algorithm + debug mode"

radix_debug: CFLAGS += "-DMODE=24"
radix_debug: re
	@echo "🔢 Radix algorithm + debug mode"

lis_debug: CFLAGS += "-DMODE=28"
lis_debug: re
	@echo "🔗 LIS algorithm + debug mode"

queue_debug: CFLAGS += "-DMODE=21"
queue_debug: re
	@echo "🚛 Queue algorithm + debug mode"

# Default modes
default: CFLAGS += "-DMODE=0"
default: re
	@echo "📦 Default mode (chunk + evaluation)"

debug: CFLAGS += "-DMODE=16"
debug: re
	@echo "🐛 Debug mode (chunk + debug)"
