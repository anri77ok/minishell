/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chakertni.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:09:46 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 15:10:15 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"

void	chakertni(t_token **tokens)
{
	t_token	*cur;
	int		i;
	int		j;

	cur = *tokens;
	while (cur)
	{
		i = 0;
		while (cur->value[i])
		{
			if (cur->value[i] == 34 || cur->value[i] == 39)
			{
				foo2(cur->value, &i, &j);
				if (i != -1)
				{
					chakertni_helper(cur, &i, j);
					if (cur->value == '\0')
						break ;
				}
			}
			else
				i++;
		}
		cur = cur->next;
	}
}

void	foo2(char *value, int *i, int *j)
{
	*j = *i;
	*i = get_quote(value, *i, value[*i]);
}

void	chakertni_helper(t_token *cur, int *i, int j)
{
	cur->begin = begin_func(j, cur->value);
	cur->word = word_func(*i, j, cur->value);
	cur->end = end_func(*i, cur->value);
	free(cur->value);
	cur->final = join(cur->begin, cur->word, 0, 0);
	cur->value = join(cur->final, cur->end, 0, 0);
	*i = i_func(cur->begin, cur->word);
	free_func(cur->begin, cur->end, cur->final, cur->word);
}

int	i_func(char *begin, char *word)
{
	int	i;

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
	return (i);
}

void	free_func(char *begin, char *end, char *final, char *word)
{
	free(begin);
	free(end);
	free(final);
	free(word);
}
