/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:18:29 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 20:19:42 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include "tokenization.h"

# define INPUT 0
# define TRUNC 1
# define APPEND 2
# define HERE_DOC_FILE "hesa kjnjvem"

t_env_elem	*init_env(t_env_elem *envr, char	**env);
void		check_env(t_shell	*shell);
void		token_to_cmds(t_shell *shell, t_token *tokens);
void		token_to_cmds_helper2(t_token	*temp2, t_token	**temp);
void		token_to_cmds_helper1(int *len, t_token *t2, char **cm);
void		ft_lstadd_back(t_shell *shell, t_cmd *new);
t_cmd		*ft_lstnew(char **cmd_args, t_fds *fds);
int			open_file(t_token *cmd, int type);
int			here_doc_open(char *lim);
char		**env_list_to_array(t_env_elem *temp);
void		del_here_doc_file(void);
void		unset_env_lav(t_env_elem *env, char *key);

#endif