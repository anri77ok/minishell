#include "minishell.h"
#include "tokenization.h"
#include "utils.h"

void redir(t_token **tokens)
{
	t_token *current;

	current = *tokens;
	while (current)
	{
		if ()
		current = current->next;
	}
}

t_cmd	*ft_lstnew(char **cmd_args, t_fds *fds)
{
	t_cmd	*new_node;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd_args = cmd_args;
	new_node->cmd_path = cmd_args[0];
	if (fds->infd > 2)
		new_node->input = fds->infd;
	else
		new_node->input = 0;
	if (fds->outfd > 2)
		new_node->output = fds->outfd;
	else
		new_node->output = 1;
	new_node->next = NULL;
	return (new_node);
}