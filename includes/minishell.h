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

# define RM "rm"
# define RF	"-rf"
# define HERE_DOC_FILE "hesa kjnjvem"
# define TERM_CODE_SHIFT 128

int	g_exit_status;
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
	t_env_elem	*prev;
}	t_env_elem;

typedef struct s_shell
{
	t_env_elem	*envr;
	t_cmd		*cmds;
}	t_shell;


t_env_elem	*merge_sort(t_env_elem *begin_list, int (*cmp)());
t_env_elem	*ft_merge_sorted_list(t_env_elem *left, t_env_elem *right, int (*cmp)());
t_env_elem	*ft_env_elem_at(t_env_elem *begin_list, unsigned int nbr);
int	ft_env_elem_size( t_env_elem *begin_list);
void	set_singals(void);
void	*ft_memset(void *b, int c, size_t len);
void	choose_signal(void (*f), int flag);
void	ctrl_bckslash(void);
void	disable_echoctl(void);

int	error_helper1(char *s1, char *s2, char *s3, int exit_status);


#endif