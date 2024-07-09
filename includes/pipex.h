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

#define	 STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2

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
void dupeing(t_pipex *pipex, t_cmd *cmd);
void	close_pipes(t_pipex *pipex);
void    init_pipes(t_pipex *pipex);

void	which_built_in_will_be_runed(t_pipex *pipex, t_cmd *cmd);






int	export(t_pipex *pipex, t_cmd *cmd);
void	print_export(t_pipex *pipex);

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd, int *error_exit);
char	*get_word_after_equal(char	*value);
char	*get_word_before_equal(char	*key);
int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value);
int	have_equal_sign(char *str);

//unset
int    unset(t_pipex *pipex, t_cmd *cmd);
void    delete_node_with_that_key(t_env_elem **env, char *key);
void     delete_middle_node(t_env_elem **env, int pos);
int check_this_key_in_env_list_unset(t_env_elem *env, char *key, int *pos);
int count_env_nodes_(t_env_elem *env);
int is_valid_identifer(char *cmd);
int is_first_simbol_valid(char c);
int	is_digit_or_letter_or__(char c);
//cd 
int	cd(char *path, t_pipex *pipex);
void	update_env(t_env_elem *env, char *old_path, char *new_path);
int	cd_helper_1(char *modified_cmd);
int	can_access(char *modfied_cmd);
int	is_directory(char *modfied_cmd);
int is_file_or_directory(char *modified_cmd);
char	*home_kpcnel_pathin(t_env_elem *env, char *path);
char	*get_cmd_in_env(t_env_elem *env, char *pntrvox);



#endif