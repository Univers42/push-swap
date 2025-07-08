# NAME 
PS_PROG=push_swap
NAME=$(PS_PROG).a

define cmd_libs
	@echo "cmd $(2) used for $(1)"
	$(MAKE) -C $(1) $(2)
endef

#COMMAND
AR= ar rcs
RM=rm -rf
CC=clang
CFLAGS=-Wall -Wextra -Werror -g -O3 -I./libft -I./inc -ferror-limit=15 -fPIC

# PATH DIRECTORIES
D_PROJECT :=.
D_LIBFT := $(D_PROJECT)/libft
D_SRCS := $(D_PROJECT)/src
D_OPERATIONS := $(D_SRCS)/operations
D_TESTS := $(D_PROJECT)/tests
D_ALGOS := $(D_SRCS)/algorithms
D_OPTIMIZATION := $(D_SRCS)/optimizations
D_DEBUG := $(D_SRCS)/debug

# SOURCES
SRCS=	$(D_OPERATIONS)/push.c 		\
		$(D_OPERATIONS)/rotate.c	\
		$(D_OPERATIONS)/rrotate.c 	\
		$(D_OPERATIONS)/swap.c		\
		$(D_SRCS)/utils.c			\
		$(D_SRCS)/stack_utils.c		\
		$(D_SRCS)/op_buffer.c		\
		$(D_SRCS)/push_swap.c		\
		$(D_SRCS)/recorder.c		\
		$(D_ALGOS)/radix.c			\
		$(D_ALGOS)/simple_algos.c	\
		$(D_ALGOS)/greedy.c			\
		$(D_ALGOS)/chunk.c			\
		$(D_ALGOS)/algorithm_registry.c

# IMPLICIT RULES CONVERSION OBJECTS
OBJECTS=$(SRCS:.c=.o)

# UTILS TARGETS

# DEFAULT TARGET build the static library
all: $(NAME) $(PS_PROG)

$(NAME): build $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)

# IMPLICIT RULE CONVERSION
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Build push_swap executable
push_swap: $(NAME)
	@$(CC) $(CFLAGS) $(D_SRCS)/push_swap.c -L. -l:push_swap.a -L./$(D_LIBFT) -lft -o push_swap

# Build micro_test executable
micro_test: $(NAME)
	@$(CC) $(CFLAGS) $(D_TESTS)/micro_test.c -L. -l:push_swap.a -L./$(D_LIBFT) -lft -o micro_test

clean:
	@$(RM) $(OBJECTS) push_swap micro_test

MAKEFLAGS = --no-print-directory

build:
	@$(call cmd_libs, $(D_LIBFT), all)

fclean: clean
	@$(call cmd_libs, $(D_LIBFT), fclean)
	@$(RM) $(NAME) push_swap micro_test

re: fclean all

# Additional targets for testing
test: micro_test
	./micro_test 3 2 1

.PHONY: re fclean clean build all test push_swap micro_test