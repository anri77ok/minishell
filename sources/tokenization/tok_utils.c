#include "tokenization.h"
#include "utils.h"
#include <stdlib.h>

void	tokens_types(t_token *tokens)
{
	t_token *current;
	t_token_params params;

	params.cmd_found = 0;
	params.redir = 0;
	current = tokens;
	while (current)
	{
        current->type = set_token_type(current->value, 0);
        if (current->prev != NULL && current->type == WORD
            && ft_is_operator(current->prev->value, 0) > 0)
        {
            if (current->prev->type == IN_REDIR)
                current->type = FILEIN;
            if (current->prev->type == HERE_DOC)
                current->type = LIMITER;
            if (current->prev->type == OUT_REDIR)
                current->type = FILEOUT;
            if (current->prev->type == APPEND_REDIR)
                current->type = APPEND_FILEOUT;
        }
        current = current->next;
	}
}

t_token_type set_token_type(char *value, int i)
{
	if (!value || i < 0)
		return (ERROR);
	if (value[i] == '|')
	{
		if (value[i + 1] && value[i] == value[i + 1])
			return (D_PIPE);
		return (S_PIPE);
	}
	else if (value[i] == '&')
	{
		if (value[i + 1] && value[i] == value[i + 1])
			return (D_AND);
		return (S_AND);
	}
	else if (value[i] == '>')
    {
        if (value[i + 1] && value[i] == value[i + 1])
            return (APPEND_REDIR);
        return (OUT_REDIR);
    }
    else if (value[i] == '<')
    {
        if (value[i + 1] && value[i] == value[i + 1])
            return (HERE_DOC);
        return (IN_REDIR);
    }
    return (WORD);
}