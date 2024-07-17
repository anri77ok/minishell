#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	count_node_equal_1(t_token **token_list)
{
	free((*token_list)->value);
	free(*token_list);
	*token_list = NULL;
}

void	del_node_when_pos_0(t_token **token_list)
{
	t_token	*del_node;

	del_node = *token_list;
	free(del_node->value);
	*token_list = (*token_list)->next;
	(*token_list)->prev = NULL;
	free(del_node);
	del_node = NULL;
}

void	delete_this_node(t_token	**token_list, int pos)
{
	int		count_nodes;
	t_token	*del_node;
	t_token	*temp;

	temp = *token_list;
	count_nodes = count_nodes_func(*token_list);
	if (count_nodes == 1)
		return (count_node_equal_1(token_list));
	if (pos == 0)
		del_node_when_pos_0(token_list);
	else if (pos == count_nodes - 1)
	{
		while (temp->next->next)
			temp = temp->next;
		del_node = temp->next;
		free(del_node->value);
		free(del_node);
		temp->next = NULL;
	}
	else
		middle_node(token_list, pos);
}

void	middle_node(t_token **token_list, int pos)
{
	t_token	*temp;
	t_token	*del_node;

	temp = *token_list;
	while (pos > 0)
	{
		temp = temp->next;
		pos--;
	}
	del_node = temp;
	free(del_node->value);
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(del_node);
}
