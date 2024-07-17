#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	check_syntax(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == S_PIPE && (!temp->prev || !temp->next))
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
		if (temp->type == OUT_REDIR || temp->type == IN_REDIR || temp->type == APPEND_REDIR || temp->type == HERE_DOC)
		{
			if (!temp->next)
				return (p_error(NULL, SYNTAX_ERR, "newline", 258), 2);
			if (temp->next->type == FILEOUT || temp->next->type == FILEIN || temp->next->type == APPEND_FILEOUT || temp->next->type == LIMITER)
				return (0);
			return (p_error(NULL, SYNTAX_ERR, temp->next->value,258), 2);
		}
		if (temp->type == S_PIPE && control_operators(temp->next) == 1)
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
		if (permitted_operator(temp))
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
		temp = temp->next;
	}
	return (0);
}

int	permitted_operator(t_token *token)
{
	if (token->type == D_PIPE || token->type == S_AND || token->type == D_AND)
			return (1);
		return (0);
}

int	control_operators(t_token *token)
{
	// if (!token->value)
	// 	return (1);
	if (token->type == S_AND || token->type == D_AND || token->type == S_PIPE || token->type == D_PIPE)
		return (1);
	return (-1);
}


int	check_value_is_empty(char	*value)
{
	if (value[0] == '\0')
		return (1);
	return (-1);
}
