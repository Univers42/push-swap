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
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -O3 -I./libft -I./inc

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
		$(D_SRCS)/push_swap.c		\
		$(D_ALGOS)/radix.c			\
		$(D_ALGOS)/simple_algos.c	\
		$(D_ALGOS)/greedy.c			\
		$(D_ALGOS)/chunk.c

# IMPLICIT RULES CONVERSION OBJECTS
OBJECTS=$(SRCS:.c=.o)

# UTILS TARGETS

# DEFAULT TARGET build the static library
all: $(NAME) $(PS_PROG) clean

$(NAME): build $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)

# IMPLICIT RULE CONVERSION
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Alternative: Use the static library instead of individual object files
$(PS_PROG): $(NAME)
	@$(CC) $(CFLAGS) $(D_TESTS)/micro_test.c -L. -l:push_swap.a -L./$(D_LIBFT) -lft -o $@

clean:
	@$(call cmd_libs, $(D_LIBFT), clean)
	@$(RM) $(OBJECTS) $(EXEC_OBJECTS)

MAKEFLAGS = --no-print-directory

build:
	@$(call cmd_libs, $(D_LIBFT), all)

fclean: clean
	@$(call cmd_libs, $(D_LIBFT), fclean)
	@$(RM) $(NAME) $(PS_PROG)

re: fclean all

.PHONY: re fclean clean build all