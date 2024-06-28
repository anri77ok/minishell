#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include "tokenization.h"

# define INPUT 0
# define TRUNC 1
# define APPEND 2
# define HERE_DOC_FILE ".hd_tmp_file"

t_env_elem  *init_env(t_env_elem *envr, char	**env);
void	check_env(t_shell	*shell);
void	token_to_cmds(t_shell *shell, t_token *tokens);
void	ft_lstadd_back(t_shell *shell, t_cmd *new);
t_cmd	*ft_lstnew(char **cmd_args, t_fds *fds);
int	open_file(char *fn, int type);
int	here_doc_open(char *lim);
void    run_cmds(t_cmd *shell_cmds, char **env);

#endif