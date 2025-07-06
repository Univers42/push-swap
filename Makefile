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
CFLAGS=-Wall -Wextra -Werror -g -O3 -I./libft

# PATH DIRECTORIES
D_PROJECT :=.
D_LIBFT := $(D_PROJECT)/libft

# SOURCES
SRCS= main.c

# IMPLICIT RULES CONVERSION OBJECTS
OBJECTS=$(SRCS=.c:.o)

# UTILS TARGETS

# DEFAULT TARGET build the static library
all: $(NAME) $(PS_PROG) clean

$(NAME): build $(OBJECTS)
	@$(AR) $(OBJECTS) $(NAME)

# IMPLICIT RULE CONVERSION
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PS_PROG): 
	@$(CC) $(CFLAGS) main.c -L./$(D_LIBFT) -lft -o $@

clean:
	@$(call cmd_libs, $(D_LIBFT), clean)
	@$(RM) $(OBJECTS)

MAKEFLAGS = --no-print-directory

build:
	@$(call cmd_libs, $(D_LIBFT), all)

fclean: clean
	@$(call cmd_libs, $(D_LIBFT), fclean)
	@$(RM) $(NAME) $(PS_PROG)

re: fclean all

.PHONY: re fclean clean build all