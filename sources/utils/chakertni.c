#include "tokenization.h"
#include "utils.h"

int get_quote(char *str, int i, char c)
{
	while (str[i])
	{
		i++;
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

void chakertni(t_token **tokens)
{
	t_token *current;
	char *begin;
	char *end;
	char *word;
	char *final;
	int i;
	int j;
	char c;

	current = *tokens;
	while (current)
	{
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 34 || current->value[i] == 39)
			{
				c = current->value[i];
				i++;
				j = i;
				i = get_quote(current->value, i, c);
				if (i != -1)
				{
					begin = ft_substr(current->value, 0, j - 1, true);
					word = ft_substr(current->value, j, i, true);
					end = ft_substr(current->value, i + 1, ft_strlen(current->value), true);
					free(current->value);
					final = join(begin, word);
					current->value = join(final, end);
					// printf("j--%d i--%d\n", j, i);
					// printf("begin--%s--\n", begin);
					// printf("end--%s--\n", end);
					// printf("--%s--\n", current->value);
					free(begin);
					free(end);
					free(final);
					free(word);
				}
			}
			i++;
		}
		current = current->next;
	}
}
