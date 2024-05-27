#include "tokenization.h"
#include "utils.h"
#include <stdlib.h>

int skip_whitespaces(char *line, int i)
{
	if (line == NULL)
		return (0);
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	return (i);
}
t_token *create_new_token(char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = value;
	new_token->type = ERROR;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_to_list(t_token **list_of_tokens, t_token *new_token)
{
	t_token	*ptr;

	if (list_of_tokens == NULL || new_token == NULL)
		return ;
	if (*list_of_tokens == NULL)
	{
		*list_of_tokens = new_token;
		return ;
	}
	ptr = *list_of_tokens;
	while (ptr && ptr->next)
		ptr = ptr->next;
	ptr->next = new_token;
	new_token->prev = ptr;
}

int is_quote(char *cmd_line, int i)
{
	if (cmd_line[i] == 34)
		i++;
	else
		return (-1);
	while (cmd_line[i] && cmd_line[i] != 34)
		i++;
	if (cmd_line[i] == '\0')
		return (-1);
	else
		i++;
	return (i);
}

void tokenization(char *cmd_line, t_token **tokens)
{
	t_token	*new_token;
	int i;
	int j;

	i = skip_whitespaces(cmd_line, 0);
	j = i;
	while (cmd_line[j])
	{
		if (cmd_line[j] == 34)
			j = is_quote(cmd_line, j);
		else
			while (cmd_line[j] && ft_isspace(cmd_line[j]) == 0)
				j++;
		new_token = create_new_token(ft_substr(cmd_line, i, j - i));
		j = skip_whitespaces(cmd_line, j);
		i = j;
		add_to_list(tokens, new_token);
		tokens_types(*tokens);
	} 
}