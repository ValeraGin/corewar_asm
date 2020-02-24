PROJ_NAME=ASM
NAME = asm
SRC = src
CC = gcc
FLAGS = -g -Wall
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
SRCS = $(shell find $(SRC) -type f | grep -E "\.c$$")
INC = $(LIBFTDIR)/inc inc
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	@echo "\033[0;32m [$(PROJ_NAME)] \033[0m   \033[0;33m Compiling:\033[0m" $<
	@$(CC) $(FLAGS) $(addprefix -I,$(INC)) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJS)
	@echo "\033[0;32m [$(PROJ_NAME)] \033[0m   \033[0;33m Compiling binary:\033[0m" $@
	@$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(addprefix -I,$(INC)) $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)

clean:
	@echo "\033[0;32m [$(PROJ_NAME)] \033[0m   \033[0;33m Clean objects $(PROJ_NAME) \033[0m" $<
	@rm -rf $(OBJS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@echo "\033[0;32m [$(PROJ_NAME)] \033[0m   \033[0;33m Clean bin $(PROJ_NAME) \033[0m" $<
	@rm -rf $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all
