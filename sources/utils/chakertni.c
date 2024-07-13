#include "tokenization.h"
#include "utils.h"

int	my_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

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

	current = *tokens;
	while (current)
	{
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 34 || current->value[i] == 39)
			{
				j = i;
				i = get_quote(current->value, i, current->value[i]);
				if (i != -1)
				{
					if (j != 0)
						begin = ft_substr(current->value, 0, j, true);
					else
						begin = ft_strdup("");
					if (j + 1 != i)
						word = ft_substr(current->value, j + 1, i, true);
					else
						word =ft_strdup("");
					if (i + 1 != my_strlen(current->value))
						end = ft_substr(current->value, i + 1, ft_strlen(current->value), true);
					else
						end = ft_strdup("");
					free(current->value);
					final = join(begin, word);
					current->value = join(final, end);
					// printf("j--%d i--%d\n", j, i);
					// printf("begin--%s--\n", begin);
					// printf("end--%s--\n", end);
					// printf("word--%s--\n", word);
					// printf("final--%s--\n", final);
					// printf("--%s--\n", current->value);
					if (word != '\0')
					{
						if (begin == '\0')
							i = my_strlen(word);
						else
							i = my_strlen(begin) + my_strlen(word);
					}
					else if (begin != '\0')
						i = (my_strlen(begin));
					else
						i = 0;
					// printf("i -- %d\n", i);
					free(begin);
					free(end);
					free(final);
					free(word);
					if (current->value == '\0')
						break ;
				}
			}
			else
				i++;
		}
		current = current->next;
	}
	// current = *tokens;
	// while (current)
	// {
	// 	printf("value=%s\n",current->value);
	// 	current= current->next;
	// }
}

