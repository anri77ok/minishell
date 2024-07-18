/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:32 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 15:41:20 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	unset(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int	i;
	int	error_exit;
	int	pos;

	pos = 0;
	error_exit = 0;
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (is_valid_identifer(cmd->cmd_args[i]) == -1)
		{
			er_hp1("minishell: ", cmd->cmd_args[i],
				": not a valid identifier\n", 1);
			error_exit = 1;
			i++;
			continue ;
		}
		delete_node_with_that_key(pipex, cmd->cmd_args[i], pos);
		i++;
	}
	*is_builtin = 1;
	return (error_exit);
}

int	is_valid_identifer(char *cmd)
{
	int	i;

	i = 1;
	if (is_first_simbol_valid(cmd[0]) == -1)
		return (-1);
	while (cmd[i])
	{
		if (is_digit_or_letter_or__(cmd[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int	is_first_simbol_valid(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (-1);
}

int	is_digit_or_letter_or__(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (-1);
}

int	check_this_key_in_env_list_unset(t_env_elem *env, char *key, int *pos)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		(*pos)++;
		env = env->next;
	}
	return (-1);
}
