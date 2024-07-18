/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:45:40 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 16:00:24 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	func_1(t_cmd *cmd, int *i, int *error_exit)
{
	if (cmd->cmd_args && cmd->cmd_args[*i] && cmd->cmd_args[*i][0] == '=')
	{
		er_hp1("minishell: export: `", cmd->cmd_args[*i],
			"': not a valid identifier\n", 1);
		*error_exit = 1;
		(*i)++;
		return (1);
	}
	return (-1);
}

int	func_2(char *key, int *i, int *error_exit)
{
	if (is_valid_identifer(key) == -1)
	{
		er_hp1("minishell: export: `", key, "': not a valid identifier\n", 1);
		free(key);
		*error_exit = 1;
		(*i)++;
		return (1);
	}
	return (-1);
}

void	free_key_and_value(char *key, char *value)
{
	free(value);
	free(key);
}

void	ft_sort(t_env_elem **copy, int (*cmp)())
{
	*copy = merge_sort(*copy, cmp);
}

void	print_export(t_pipex *pipex)
{
	t_env_elem	*temp;
	t_env_elem	*copy;
	bool		yel;

	copy = pipex->envp;
	copy = get_copy_env(pipex->envp);
	ft_sort(&copy, ft_strcmp);
	temp = copy;
	if (ft_strcmp(pipex->cmds->cmd_args[0], "export") == 0
		&& !pipex->cmds->cmd_args[1])
	{
		while (temp)
		{
			if (temp->value == NULL && temp->key == NULL)
				yel = false;
			else if (temp->value == NULL)
				printf("declare -x %s\n", temp->key);
			else if (temp->value != NULL && temp->value[0] == '\0')
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else if (temp->value[0])
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
	free_list(copy);
}
