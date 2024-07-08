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
	int			cmd_count;
	t_cmd		*cmds;
	t_env_elem	*envp;
	pid_t		*pids;
}	t_pipex;

void	run_cmds(t_shell *shell);
int	count_shell_cmds(t_cmd *shell_cmds);
void	pipex_init(t_pipex *pipex, t_shell *shell);
void run_shell_cmd(t_pipex *pipex, t_cmd *cmd, int i);
void duping(t_pipex *pipex, t_cmd *cmd);
void	close_pipes(t_pipex *pipex);
void    init_pipes(t_pipex *pipex);


void	export(t_pipex *pipex, t_cmd *cmd);;
void	print_export(t_pipex *pipex, int flag);

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd ,int flag);
char	*get_word_after_equal(char	*value);
char	*get_word_before_equal(char	*key);
int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value);
int	have_equal_sign(char *str);

//unset
//unset
void    unset(t_pipex *pipex, t_cmd *cmd);
void    delete_node_with_that_key(t_env_elem **env, char *key);
void     delete_middle_node(t_env_elem **env, int pos);
int check_this_key_in_env_list_unset(t_env_elem *env, char *key, int *pos);
int count_env_nodes_(t_env_elem *env);
#endif