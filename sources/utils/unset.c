#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	unset(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int i;
	int error_exit;

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
		delete_node_with_that_key(&pipex->envp, cmd->cmd_args[i]);
		i++;
	}
	*is_builtin = 1;
	return (error_exit);
}

int is_valid_identifer(char *cmd)
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

int is_first_simbol_valid(char c)
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

void    delete_node_with_that_key(t_env_elem **env, char *key)
{
	int pos;
	t_env_elem  *temp;
	t_env_elem	*del_node;

	temp = *env;
	pos = 0;
	if (check_this_key_in_env_list_unset(*env, key, &pos) == 1)
	{
		if (pos == 0)
		{
			printf("sax esem\n");
			// del_first_node(env);
			del_node = *env;
			free(del_node->key);
			free(del_node->value);
			*env = (*env)->next;
			(*env)->prev = NULL;
			free(del_node);
			del_node = NULL;
		}
		else if (pos > 0 && pos < count_env_nodes_(*env) - 1)
			delete_middle_node(env, pos);
		else if (pos == count_env_nodes_(*env) - 1)
		{
			while (temp->next->next)
				temp = temp->next;
			del_node = temp->next;
			free(del_node->key);
			free(del_node->value);
			free(del_node);
			temp->next = NULL;
		}
	}

}

void	del_first_node(t_env_elem **env)
{
	t_env_elem	*del_node;

	del_node = *env;
	free(del_node->key);
	free(del_node->value);
	*env = (*env)->next;
	(*env)->prev = NULL;
	free(del_node);
	del_node = NULL;
}

void     delete_middle_node(t_env_elem **env, int pos)
{
    t_env_elem	*temp;
	t_env_elem	*del_node;

	temp = *env;
	while (pos > 0)
	{
		temp = temp->next;
		pos--;
	}
	del_node = temp;
	free(del_node->key);
	free(del_node->value);
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(del_node);
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
    int count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}
