PROJ_NAME ?= ASM
TARGET_EXEC ?= asm

BUILD_DIR ?= ./obj
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -type f -name *.c )
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

INC_DIRS := $(LIBFTDIR)/inc inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CDEBUGFLAG = -g
CFLAGS ?= $(CDEBUGFLAG) -Wall -Wextra -Werror $(INC_FLAGS) -MMD -MP

# make executable file
$(TARGET_EXEC): $(OBJS) $(LIBFT)
	@echo "\033[0;32m[$(PROJ_NAME)] \033[0m      \033[0;33m Compiling binary:\033[0m" $@
	@$(CC) $(LIBFT) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	@echo "\033[0;32m[$(PROJ_NAME)] \033[0m      \033[0;33m Compiling:\033[0m" $<
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# make my libft
$(LIBFT):
	@make -C $(LIBFTDIR)

.PHONY: all clean fclean re

all: $(TARGET_EXEC) $(LIBFT)

clean:
	@echo "\033[0;32m[$(PROJ_NAME)] \033[0m      \033[0;33m Clean objects $(PROJ_NAME) \033[0m" $<
	@$(RM) -r $(BUILD_DIR)
	@make -C $(LIBFTDIR) clean

fclean:
	@echo "\033[0;32m[$(PROJ_NAME)] \033[0m      \033[0;33m Clean objects $(PROJ_NAME) \033[0m" $<
	@$(RM) -r $(BUILD_DIR)
	@echo "\033[0;32m[$(PROJ_NAME)] \033[0m      \033[0;33m Clean bin $(PROJ_NAME) \033[0m" $<
	@rm -rf $(TARGET_EXEC)
	@make -C $(LIBFTDIR) fclean

norme:
	@norminette | grep Error -B 1

re: fclean all

-include $(DEPS)

MKDIR_P ?= mkdir -p







