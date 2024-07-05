#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	export(t_pipex *pipex, t_cmd *cmd)
{
	if (!cmd->cmd_args[1])
		print_export(pipex);
	else
		ay_nor_export(pipex, cmd);
}

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd)
{
	t_env_elem	*new_node;
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (cmd->cmd_args[i])
	{
		key = get_word_before_equal(cmd->cmd_args[i]);
		value = get_word_after_equal(cmd->cmd_args[i]);
		if (check_this_key_in_env_list(pipex->envp, key, value) == -1)
		{
			i++;
			continue ;
		}
		new_node = ft_lstnew_dlya_env(key ,value);
		ft_lstadd_back_env(&pipex->envp, new_node);
		i++;
	}
	print_export(pipex);


}


int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			if (env_list->value && value[0])
			{
				char *temp = env_list->value;
				free(temp);
				env_list->value = ft_strdup(value);
				return (-1);
			}
			// return (-1);
			if(env_list->value && value[0] == '\0')
				return (-1);
		}
		env_list = env_list->next;
	}
	return (1);
}


char	*get_word_after_equal(char	*value)
{
	int	i;
	char	*res;

	i = 0;
	while (value[i])
	{
		if (value[i] == '=')
			break ;
		i++;
	}
	res = ft_substr(value, i + 1, ft_strlen(value), true);
	return (res);
}

char	*get_word_before_equal(char	*key)
{
	int	i;
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

void	print_export(t_pipex *pipex)
{
	t_env_elem	*temp;

	temp = merge_sort(pipex->envp, ft_strcmp);
	while (temp)
	{
		if (temp->value[0])
			printf("declare -x %s=%s\n", temp->key, temp->value);
		else
			printf("declare -x %s%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	// free_list(temp);
	temp = NULL;
}