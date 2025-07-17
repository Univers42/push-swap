# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 13:37:35 by codespace         #+#    #+#              #
#    Updated: 2025/07/17 09:19:29 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DEFINES AND MACROS CONFIGURATIONS
define cmd_build
	$(MAKE) -C $(1) $(2)
endef

# COMMANDS AND FLAGS
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I./include -I./libft -g3 -O3
RM					=	rm -rf
AR					=	ar rcs

# PROGRAM NAMES
PUSH_SWAP			=	push_swap
CHECKER				=	checker
NAME				=	$(PUSH_SWAP)

# DIRECTORIES
D_PROJECT			=	.
D_LIBFT				=	$(D_PROJECT)/libft
D_SRC				=	$(D_PROJECT)/src
D_ALGORITHMS		=	$(D_SRC)/algorithms
D_CHUNK				=	$(D_ALGORITHMS)/chunk
D_GREEDY			=	$(D_ALGORITHMS)/greedy
D_K					=	$(D_ALGORITHMS)/k
D_LIS				=	$(D_ALGORITHMS)/lis
D_RADIX				=	$(D_ALGORITHMS)/radix
D_QUEUE				=	$(D_ALGORITHMS)/queue
D_PERMUTATIONS		=	$(D_ALGORITHMS)/permutations
D_CHECKER_BONUS		=	$(D_SRC)/checker_bonus
D_OPERATIONS		=	$(D_SRC)/operations
D_OPTIMIZATIONS		=	$(D_SRC)/optimizations
D_PUSH_SWAP			=	$(D_SRC)/push_swap
D_STACK				=	$(D_SRC)/stack
D_UTILS				=	$(D_SRC)/utils
D_PARSER			=	$(D_SRC)/parser
D_ALG_HELPERS		=	$(D_SRC)/algorithm_helpers
D_VISUALIZER		=	$(D_CHECKER_BONUS)/visualizer

# SOURCE FILES
CHUNK_SRCS			=	$(D_CHUNK)/chunk_sort.c \
						$(D_CHUNK)/chunk_split.c \
						$(D_CHUNK)/sort.c \
						$(D_CHUNK)/helpers.c

GREEDY_SRCS			=	$(D_GREEDY)/greedy.c \
						$(D_GREEDY)/execution.c \
						$(D_GREEDY)/push.c \
						$(D_GREEDY)/position.c \
						$(D_GREEDY)/rotation.c \
						$(D_GREEDY)/compute.c

K_SRCS				=	$(D_K)/final.c \
						$(D_K)/helpers.c \
						$(D_K)/helpers2.c \
						$(D_K)/rotation.c \
						$(D_K)/sort.c

LIS_SRCS			=	$(D_LIS)/rotation.c \
						$(D_LIS)/sort.c \
						$(D_LIS)/helpers.c \
						$(D_LIS)/utils2.c

RADIX_SRCS			=	$(D_RADIX)/helpers.c \
						$(D_RADIX)/radix.c

QUEUE_SRCS			=	$(D_QUEUE)/queue_sort.c

PERM_SRCS			=	$(D_PERMUTATIONS)/easy_perm.c \
						$(D_PERMUTATIONS)/one_perm.c \
						$(D_PERMUTATIONS)/three_perm.c \
						$(D_PERMUTATIONS)/two_perm.c \
						$(D_PERMUTATIONS)/3_perm.c

OPERATIONS_SRCS		=	$(D_OPERATIONS)/push.c \
						$(D_OPERATIONS)/rotate.c \
						$(D_OPERATIONS)/rrotate.c \
						$(D_OPERATIONS)/swap.c

OPTIMIZATIONS_SRCS	=	$(D_OPTIMIZATIONS)/fsm.c \
						$(D_OPTIMIZATIONS)/fusops.c \
						$(D_OPTIMIZATIONS)/redox.c \
						$(D_OPTIMIZATIONS)/remops.c

STACK_SRCS			=	$(D_STACK)/cv_stack.c

UTILS_SRCS			=	$(D_UTILS)/check.c \
						$(D_UTILS)/exit.c \
						$(D_UTILS)/get.c \
						$(D_UTILS)/math.c

PUSH_SWAP_SRCS		=	$(D_PUSH_SWAP)/main.c \
						$(D_PUSH_SWAP)/helpers.c \
						$(D_PUSH_SWAP)/init.c \
						$(D_PUSH_SWAP)/unit_ctrl.c \
						$(D_PUSH_SWAP)/goinfre.c \
						$(D_PUSH_SWAP)/config_algos.c \
						$(D_PUSH_SWAP)/init_algos.c

PARSER_SRCS			=	$(D_PARSER)/helpers.c \
						$(D_PARSER)/parser.c

ALG_HELPERS_SRCS	=	$(D_ALG_HELPERS)/chunk_utils.c \
						$(D_ALG_HELPERS)/move.c

VISUALIZER_SRCS		=	$(D_VISUALIZER)/helper.c \
						$(D_VISUALIZER)/replay.c \
						$(D_VISUALIZER)/singleton.c \
						$(D_VISUALIZER)/visualizer.c

# COMMON SOURCES (shared by all algorithms - NO algorithm-specific files)
COMMON_SRCS			=	$(OPERATIONS_SRCS) \
						$(OPTIMIZATIONS_SRCS) \
						$(STACK_SRCS) \
						$(UTILS_SRCS) \
						$(PUSH_SWAP_SRCS) \
						$(PARSER_SRCS) \
						$(ALG_HELPERS_SRCS) \
						$(PERM_SRCS)

# ALGORITHM-SPECIFIC BUILDS (include ALL algorithms for proper linking)
CHUNK_ALL_SRCS		=	$(COMMON_SRCS) $(CHUNK_SRCS) $(GREEDY_SRCS) $(K_SRCS) $(LIS_SRCS) $(RADIX_SRCS) $(QUEUE_SRCS)
GREEDY_ALL_SRCS		=	$(COMMON_SRCS) $(GREEDY_SRCS) $(CHUNK_SRCS) $(K_SRCS) $(LIS_SRCS) $(RADIX_SRCS) $(QUEUE_SRCS)
K_ALL_SRCS			=	$(COMMON_SRCS) $(K_SRCS) $(CHUNK_SRCS) $(GREEDY_SRCS) $(LIS_SRCS) $(RADIX_SRCS) $(QUEUE_SRCS)
LIS_ALL_SRCS		=	$(COMMON_SRCS) $(LIS_SRCS) $(CHUNK_SRCS) $(GREEDY_SRCS) $(K_SRCS) $(RADIX_SRCS) $(QUEUE_SRCS)
RADIX_ALL_SRCS		=	$(COMMON_SRCS) $(RADIX_SRCS) $(CHUNK_SRCS) $(GREEDY_SRCS) $(K_SRCS) $(LIS_SRCS) $(QUEUE_SRCS)
QUEUE_ALL_SRCS		=	$(COMMON_SRCS) $(QUEUE_SRCS) $(CHUNK_SRCS) $(GREEDY_SRCS) $(K_SRCS) $(LIS_SRCS) $(RADIX_SRCS)

# BONUS SOURCES
CHECKER_SRCS		=	$(D_CHECKER_BONUS)/checker_bonus.c \
						$(D_CHECKER_BONUS)/init_bonus.c \
						$(D_CHECKER_BONUS)/ops_bonus.c \
						$(D_CHECKER_BONUS)/op_wrap_bonus.c \
						$(D_CHECKER_BONUS)/ops_wrap2_bonus.c \
						$(D_CHECKER_BONUS)/checker_stack_ops_bonus.c \
						$(D_CHECKER_BONUS)/strop_bonus.c \
						$(D_CHECKER_BONUS)/parser_bonus.c \
						$(D_STACK)/cv_stack.c \
						$(D_UTILS)/check.c \
						$(D_UTILS)/exit.c \
						$(D_UTILS)/get.c \
						$(D_UTILS)/math.c \
						$(D_PARSER)/helpers.c

VISUALIZER_SRCS		=	$(D_CHECKER_BONUS)/visualizer/visualizer.c \
						$(D_CHECKER_BONUS)/visualizer/helper.c \
						$(D_CHECKER_BONUS)/visualizer/singleton.c \
						$(D_CHECKER_BONUS)/visualizer/replay.c

# OBJECT FILES
OBJ_DIR				=	obj
CHUNK_OBJS			=	$(CHUNK_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
GREEDY_OBJS			=	$(GREEDY_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
K_OBJS				=	$(K_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
LIS_OBJS			=	$(LIS_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
RADIX_OBJS			=	$(RADIX_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
QUEUE_OBJS			=	$(QUEUE_ALL_SRCS:%.c=$(OBJ_DIR)/%.o)
CHECKER_OBJS		=	$(CHECKER_SRCS:%.c=$(OBJ_DIR)/%.o)
VISUALIZER_OBJS		=	$(CHECKER_SRCS:%.c=$(OBJ_DIR)/%.o)

# DEFAULT TARGET (chunk algorithm)
all: build_libft $(PUSH_SWAP)

# Main targets
$(PUSH_SWAP): $(CHUNK_OBJS)
	$(CC) $(CFLAGS) $(CHUNK_OBJS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

chunk: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_CHUNK $(CHUNK_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

greedy: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_GREEDY $(GREEDY_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

k_sort: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_K_SORT $(K_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

lis: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_LIS $(LIS_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

radix: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_RADIX $(RADIX_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

queue: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_QUEUE $(QUEUE_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

# Debug versions
chunk_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_CHUNK -DDEBUG=1 $(CHUNK_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

greedy_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_GREEDY -DDEBUG=1 $(GREEDY_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

k_sort_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_K_SORT -DDEBUG=1 $(K_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

lis_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_LIS -DDEBUG=1 $(LIS_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

radix_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_RADIX -DDEBUG=1 $(RADIX_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

queue_debug: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_QUEUE -DDEBUG=1 $(QUEUE_ALL_SRCS) -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

# Bonus target
bonus: build_libft $(CHECKER)

$(CHECKER): $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $(CHECKER_OBJS) -L$(D_LIBFT) -lft -o $(CHECKER)

# Visualization versions
visualize: build_libft
	$(CC) $(CFLAGS) -DALGORITHM=ALGO_CHUNK -DVISUALIZE=1 $(CHUNK_ALL_SRCS) $(D_CHECKER_BONUS)/visualizer_bonus.c -L$(D_LIBFT) -lft -o $(PUSH_SWAP)

checker_visual: build_libft
	$(CC) $(CFLAGS) -DVISUALIZE=1 -DOVERRIDE_MAIN_LOGIC $(CHECKER_SRCS) $(VISUALIZER_SRCS) -L$(D_LIBFT) -lft -o $(CHECKER)

# Object compilation rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
build_libft:
	$(call cmd_build, $(D_LIBFT), all)

# Clean targets
clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(PUSH_SWAP) $(CHECKER)
	$(call cmd_build, $(D_LIBFT), fclean)

re: fclean all

# Utility targets
test: $(PUSH_SWAP)
	@echo "Testing with small array: 3 1 2"
	@./$(PUSH_SWAP) 3 1 2

help:
	@echo "Available targets:"
	@echo "  all          - Build default (chunk algorithm)"
	@echo "  chunk        - Build with chunk algorithm"
	@echo "  greedy       - Build with greedy algorithm"
	@echo "  k_sort       - Build with k-sort algorithm"
	@echo "  lis          - Build with LIS algorithm"
	@echo "  radix        - Build with radix algorithm"
	@echo "  queue        - Build with queue algorithm"
	@echo "  bonus        - Build checker"
	@echo "  *_debug      - Build debug versions"
	@echo "  visualize    - Build with visualization"
	@echo "  test         - Quick test"
	@echo "  clean        - Remove object files"
	@echo "  fclean       - Remove all built files"
	@echo "  re           - Rebuild everything"

.PHONY: all chunk greedy k_sort lis radix queue bonus clean fclean re build_libft test help visualize checker_visual chunk_debug greedy_debug k_sort_debug lis_debug radix_debug queue_debug