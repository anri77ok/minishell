/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:46 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/16 18:12:49 by anrkhach         ###   ########.fr       */
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
		if (cmd->cmd_args && cmd->cmd_args[i] && cmd->cmd_args[i][0] == '=')
		{
			error_helper1("minishell: export: `", cmd->cmd_args[i], "': not a valid identifier\n", 1);
			*error_exit = 1;
			i++;
			continue ;
		}
		key = get_word_before_equal(cmd->cmd_args[i]);
		if (is_valid_identifer(key) == -1)
		{
			error_helper1("minishell: export: `", key, "': not a valid identifier\n", 1);
			free(key);
			*error_exit = 1;
			i++;
			continue ;
		}
		value = get_word_after_equal(cmd->cmd_args[i]);
		if (check_this_key_in_env_list(pipex->envp, key, value) == -1)
		{
			i++;
			continue ;
		}
		new_node = ft_lstnew_dlya_env(key ,value, true);
		ft_lstadd_back_env(&pipex->envp, new_node);
		i++;
	}
	//printf("DDUM\n");
	// print_export(pipex);
}


int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			if (value == NULL)
			{
				free(value);
				free(key);
				return (-1);//esi arel enq vor export c  export c(erku hat node chsarqi nuyn c key-ov)
			}
			if(env_list->value == NULL && (value[0] == '\0' || value[0]))
			{
				env_list->value = ft_strdup(value);
				free(value);
				free(key);
				return (-1);
			}//ete unenq export f heto anum enq export f= kam export f=aa popoxutyuny lini
			if (env_list->value && (value[0] == '\0' || value[0]))
			{
				free(env_list->value);
				env_list->value = ft_strdup(value);
				free(value);
				free(key);
				return (-1);
			}//ete lini export a=d heto export a=xx kam export export a=  poxi et node-i key-i value-n

		}
		env_list = env_list->next;
	}
	// if (key)
	// 	free(key);//es frinery seg en talmmmmmmmm
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
		if (value[i] == '=')
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

void	ft_sort(t_env_elem **copy, int (*cmp)())
{
	*copy = merge_sort(*copy, cmp);
}

void	print_export(t_pipex *pipex)
{
	t_env_elem	*temp;
	t_env_elem	*copy;

	copy = pipex->envp;
	copy = get_copy_env(pipex->envp);
	ft_sort(&copy, ft_strcmp);
	temp = copy;
	if (ft_strcmp(pipex->cmds->cmd_args[0], "export") == 0 && !pipex->cmds->cmd_args[1])
	{
		while (temp)
		{
			if (temp->value == NULL)
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

t_env_elem	*get_copy_env(t_env_elem *env)
{
	t_env_elem	*copy;
	t_env_elem	*node;
	t_env_elem	*temp;

	copy = NULL;
	temp = env;
	while (temp)
	{
		// printf("%s=%s\n", temp->key, temp->value);
		node = ft_lstnew_dlya_env(temp->key, temp->value, false);
		ft_lstadd_back_env(&copy, node);
		temp = temp->next;
	}
	return (copy);
}

void	free_list(t_env_elem *temp)
{
	t_env_elem	*del;

	while (temp)
	{
		printf("mtaaaaa\n");
		del = temp;
		temp = temp->next;
		free(del->key);
		free(del->value);
		free(del);
		// if (temp)
		// 	temp->prev = NULL;
	}
}
