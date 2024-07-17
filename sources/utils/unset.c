/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:32 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 16:22:10 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	delete_node_with_that_key(t_pipex *pipex, char *key)
{
	int			pos;
	t_env_elem	*temp;
	t_env_elem	*del_node;

	temp = pipex->envp;
	pos = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			del_node = temp;
			free(temp->key);
			temp->key = NULL;
			if (temp->value && temp->value[0] != '\0')
			{
				free(temp->value);
				temp->value = NULL;
			}
			// if (temp->prev)
			// 	del_node->prev->next = temp->next;
			// if (temp->next)
			// 	temp->next->prev = del_node->prev;
			// del_node->prev = NULL;
			// del_node->next = NULL;
			//free(del_node);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}

int	unset(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int	i;
	int	error_exit;

	error_exit = 0;
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (is_valid_identifer(cmd->cmd_args[i]) == -1)
		{
			error_helper1("minishell: ", cmd->cmd_args[i], ": not a valid identifier\n", 1);
			error_exit = 1;
			i++;
			continue ;
		}
		delete_node_with_that_key(pipex, cmd->cmd_args[i]);
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
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (-1);
}

int check_this_key_in_env_list_unset(t_env_elem *env, char *key, int *pos)
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

int count_env_nodes_(t_env_elem *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
