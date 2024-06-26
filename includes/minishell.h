#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef struct s_env_elem	t_env_elem;
typedef struct s_cmd		t_cmd;

typedef struct s_cmd
{
	int		input;
	int		output;
	char	*cmd_path;
	char	**cmd_args;
	t_cmd	*next;
}	t_cmd;

typedef struct s_env_elem
{
	char		*key;
	char		*value;
	t_env_elem	*next;
}	t_env_elem;

typedef struct s_shell
{
	t_env_elem	*envr;
	t_cmd		*cmds;
}	t_shell;

#endif