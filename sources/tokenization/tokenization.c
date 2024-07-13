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
	new_token->flag = 0;
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
	if (cmd_line[i] == 34 || cmd_line[i] == 39)
		i++;
	else
		return (-1);
	if (cmd_line[i - 1] == 34)
	{
		while (cmd_line[i] && cmd_line[i] != 34)
			i++;
	}
	else if (cmd_line[i - 1] == 39)
	{
		while (cmd_line[i] && cmd_line[i] != 39)
			i++;
	}
	if (cmd_line[i] == '\0')
		return (-1);
	else
		i++;
	return (i);
}

void spliting(t_token **token_list, char *str)
{
	t_token	*new_token;
	int i = 0;
	int k = 0;
	char *pice;
	while (str[i])
	{
		while (str[i] && ft_is_operator(str, i) == 0)
			i++;
		while (str[k] && ft_is_operator(str, k) != 0)
			k = k + ft_is_operator(str, k);
		if (i > k)
		{
			pice = ft_substr(str, k, i, true);
			new_token = create_new_token(pice);
			add_to_list(token_list, new_token);
			k = i;
		}
		else if (i < k)
		{
			pice = ft_substr(str, i, k, true);
			new_token = create_new_token(pice);
			add_to_list(token_list, new_token);
			i = k - ft_is_operator(str, k);;
		}
	}
}

int tokenization(char *cmd_line, t_token **token_list)
{
	int i;
	int j;
	char *line;
	t_token	*new_token;
	bool quote = false;

	i = skip_whitespaces(cmd_line, 0);
	j = i;
	while (cmd_line[j])
	{
		while (cmd_line[j] && ft_isspace(cmd_line[j]) == 0)
		{
			if (cmd_line[j] == 34 || cmd_line[j] == 39)
			{
				j = is_quote(cmd_line, j);
				if (j == -1)
				{
					printf("syntax error\n");
					return (-1);
				}
				quote = true;
			}
			else
				j++;
		}
		if (quote == true)
		{
			line = ft_substr(cmd_line, i, j - i, false);
			new_token = create_new_token(line);
			add_to_list(token_list, new_token);
		}
		else
		{
			line = ft_substr(cmd_line, i, j - i, false);
			spliting(token_list, line);
		}
		tokens_types(*token_list);
		j = skip_whitespaces(cmd_line, j);
		i = j;
		if (quote == false)
			free(line);
	}
	return (0);
}
