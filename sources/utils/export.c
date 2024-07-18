/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:19:05 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 16:00:39 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	export(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int	error_exit;

	error_exit = 0;
	if (cmd)
	{
		if (!cmd->cmd_args[1])
		{
			print_export(pipex);
		}
		else
		{
			ay_nor_export(pipex, cmd, &error_exit);
		}
	}
	*is_builtin = 1;
	return (error_exit);
}

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd, int *error_exit)
{
	t_env_elem	*new_node;
	int			i;
	char		*key;
	char		*value;

	i = 1;
	while (cmd->cmd_args[i])
	{
		key = NULL;
		if (func_1(cmd, &i, error_exit) == 1)
			continue ;
		key = get_word_before_equal(cmd->cmd_args[i]);
		if (func_2(key, &i, error_exit) == 1)
			continue ;
		value = get_word_after_equal(cmd->cmd_args[i]);
		if (check_this_key_in_env_list(pipex->envp, key, value) == -1)
		{
			i++;
			continue ;
		}
		new_node = ft_lstnew_dlya_env(key, value, true);
		ft_lstadd_back_env(&pipex->envp, new_node);
		i++;
	}
}

int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			if (value == NULL)
				return (free_key_and_value(key, value), -1);
			if (env_list->value == NULL && (value[0] == '\0' || value[0]))
			{
				env_list->value = ft_strdup(value);
				return (free_key_and_value(key, value), -1);
			}
			if (env_list->value && (value[0] == '\0' || value[0]))
			{
				free(env_list->value);
				env_list->value = ft_strdup(value);
				return (free_key_and_value(key, value), -1);
			}
		}
		env_list = env_list->next;
	}
	return (1);
}

char	*get_word_after_equal(char	*value)
{
	int	i;
	int	flag;
	int	index_equal;

	flag = 0;
	i = 0;
	index_equal = 0;
	while (value[i])
	{
		if (value[i] == '=' && flag == 0)
		{
			flag = 1;
			index_equal = i;
		}
		i++;
	}
	if (flag == 1)
	{
		if (value[index_equal + 1] == '\0')
			return (ft_strdup(""));
		if (i > index_equal - 1)
			return (ft_substr(value, index_equal + 1, ft_strlen(value), true));
	}
	return (NULL);
}

char	*get_word_before_equal(char	*key)
{
	int		i;
	char	*res;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		i++;
	}
	res = ft_substr(key, 0, i, true);
	return (res);
}
