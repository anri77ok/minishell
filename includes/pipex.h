#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "minishell.h"

# define MIN_ARGS 4
# define INVALID_ARG_CNT 1
# define SYNTAX_ERR 2
# define FILEIN_ERR 3
# define QUOT_ERR 4
# define MALLOC_ERR 5
# define PIPE_ERR 6
# define FORK_ERR 7
# define DUP_ERR 8
# define CMD_NOT_FOUND 9
# define EXECVE_ERR 10

typedef struct s_pipex
{
	int			(*pipes)[2];
	int			cmd_cnt;
	t_cmd		*cmds;
	t_env_elem	*envp;
	pid_t		*pids;
}	t_pipex;

#endif