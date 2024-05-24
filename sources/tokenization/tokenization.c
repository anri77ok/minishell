#include "tokenization.h"
#include "utils.h"
#include <stdlib.h>

size_t skip_whitespaces(char *line, size_t i)
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

void tokenization(char *cmd_line, t_token **tokens)
{
	size_t i;
	size_t j;

	i = skip_whitespaces(cmd_line, 0);
	j = i;
	while (cmd_line[j])
	{
		while (cmd_line[j] && ft_isspace(cmd_line[j]) == 0)
				j++;
		*tokens = create_new_token(ft_substr(cmd_line, i, j - i));
		j = skip_whitespaces(cmd_line, j);
		i = j;
		printf("%s\n", (*tokens)->value);
	}
}