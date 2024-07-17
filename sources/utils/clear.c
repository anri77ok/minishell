#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	ft_clear_shell(t_shell **shell)
{
	t_cmd	*tmp;
	int		i;

	while ((*shell)->cmds)
	{
		tmp = (*shell)->cmds;
		i = 0;
		// while (tmp->cmd_args[i])
		// {
		// 	free(tmp->cmd_args[i]);
		// 	i++;
		// }
		(*shell)->cmds = (*shell)->cmds->next;
		free(tmp->cmd_args);
		free(tmp);
	}
}

void	clear_shell_envr(t_shell *shell)
{
	t_env_elem *temp;

	while (shell->envr)
	{
		temp = shell->envr;
		shell->envr = shell->envr->next;
		// shell->envr->prev = NULL;
		free(temp->key);
		// temp->next = NULL;
		free(temp->value);
		free(temp);
	}
	free(shell);
}

void free_shell_token(t_shell **shell, t_token **token_list, char *cmd_line)
{
	ft_clear_shell(shell);
	ft_token_list_clear(token_list);
	free(cmd_line);
}

void	get_bez_empty_nodes(t_token **token_list)
{
	t_token	*temp;
	int	pos;

	pos = 0;
	temp = *token_list;
	while (temp)
	{
		if (temp->prev && ft_strcmp(temp->value,"\"\"") == 0 && (temp->prev->type == OUT_REDIR || temp->prev->type == IN_REDIR))
			temp->flag = 1;
		if (check_value_is_empty(temp->value) == 1)
		{
			delete_this_node(token_list, pos);
			temp = *token_list;
			pos = 0;
		}
		else
		{
			pos++;
			temp = temp->next;
		}
	}
}

int	count_nodes_func(t_token	*token_list)
{
	t_token	*temp;
	int		count_nodes;

	count_nodes = 0;
	temp = token_list;
	while(temp)
	{
		count_nodes++;
		temp = temp->next;
	}
	return (count_nodes);
}
