# Project name
NAME = minishell

# Readline name
READLINE = readline

# Compilator
CC = cc

# Compilator flags
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g -fsanitize=address

# Libraries
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

# Headers
HEADERS = 	includes/minishell.h \
			includes/tokenization.h \
			includes/utils.h \
			includes/env.h \
			includes/pipex.h

# Source directory
SRCS_DIR = sources/

# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = minishell.c tokenization/tokenization.c \
tokenization/tok_utils.c utils/utils.c utils/dolarni2.c \
utils/chakertni.c utils/redirect.c utils/envp.c utils/open_files.c \
utils/run_commands.c utils/split.c utils/pipex_ut.c utils/echo.c utils/pwd.c \
utils/merge.c utils/export.c utils/unset.c utils/cd.c utils/atol.c \
utils/exit.c utils/signals.c utils/cd2.c utils/envp2.c utils/signals2.c \
utils/utils2.c utils/utils3.c utils/dolar_utils.c utils/exit.c utils/signals.c \
utils/cd2.c utils/envp2.c utils/check_syntax.c utils/error.c utils/del_node.c \
utils/clear.c utils/unset2.c utils/export2.c utils/is_ambiguous.c \
utils/run_command2.c utils/run_commands3.c utils/dollarni1.c utils/chakertni2.c \
tokenization/tok_helper.c

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tokenization
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@ 

# Configuring readline
$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

# Cleaning
clean:
	@$(RM) $(OBJS)

# Force cleaning
fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

# Remaking
re: fclean all

# PHONY files
.PHONY: all clean fclean re