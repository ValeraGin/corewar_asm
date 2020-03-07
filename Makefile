PROJ_NAME ?= ASM
TARGET_EXEC ?= asm

OBJ_DIR = ./obj

FILE_LAST_MODE = $(OBJ_DIR)/last_version.txt
cat := $(if $(filter $(OS),Windows_NT),type,cat)
LAST_MODE = $(shell $(cat) $(FILE_LAST_MODE) 2>/dev/null)

ifneq ($(mode),debug)
   mode = release
   BUILD_DIR = $(OBJ_DIR)/release
   PREFIX = RELEASE MODE
else
   mode = debug
   BUILD_DIR = $(OBJ_DIR)/debug
   PREFIX = DEBUG MODE
endif

ifneq ($(mode),$(LAST_MODE))
    REBUILD = clean_only_exe
endif

SRC_DIRS = ./src

SRCS := $(shell find $(SRC_DIRS) -type f -name *.c )
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

INC_DIRS := $(LIBFTDIR)/inc inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS ?= -Wall -Wextra -Werror $(INC_FLAGS) -MMD -MP
ifeq ($(mode),release)
   CFLAGS += -O3
else
   CFLAGS += -O0 -g
endif

.PHONY: all clean fclean re info debug release

all: info $(TARGET_EXEC)

clean_only_exe:
	@if [ -f "$(TARGET_EXEC)" ]; then \
		printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Clean bin $(PROJ_NAME), because changed MODE COMPILATION."; \
		rm -rf $(TARGET_EXEC); \
	fi
	@make -s -C $(LIBFTDIR) $(MAKECMDGOALS)

# make executable file
$(TARGET_EXEC): $(OBJS) $(LIBFT) $(REBUILD)
	@printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m %s\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Linking:  " "$@"
	@$(CC) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)
	@rm -f $(FILE_LAST_MODE)
	@echo "$(mode)" >> $(FILE_LAST_MODE)

# c source
$(BUILD_DIR)/%.c.o: %.c
	@printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m %s\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Compiling:" "$<"
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# make my libft
$(LIBFT):
	@make -s -C $(LIBFTDIR) $(MAKECMDGOALS)

info:

debug:
	@make -s mode=debug

release:
	@make -s mode=release

clean:
	@printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Clean objects $(PROJ_NAME)"
	@$(RM) -rf $(OBJ_DIR)
	@make -s -C $(LIBFTDIR) clean

fclean:
	@printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Clean objects $(PROJ_NAME)"
	@$(RM) -rf $(OBJ_DIR)
	@printf "\033[0;32m%-10s\033[0;34m%-9s\033[0;33m  %s\033[0m\n" "[$(PROJ_NAME)]" "[$(PREFIX)]" "Clean bin $(PROJ_NAME)"
	@rm -rf $(TARGET_EXEC)
	@make -s -C $(LIBFTDIR) fclean

norme:
	@norminette | grep Error -B 1

re: fclean all

-include $(DEPS)

MKDIR_P ?= mkdir -p
