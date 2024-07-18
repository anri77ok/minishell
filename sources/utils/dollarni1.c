/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarni1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:22:49 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 19:31:41 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include "env.h"

void	kp(t_dollar *dollar)
{
	char	*final;

	final = join(dollar->parts[0], dollar->word, 0, 0);
	free(dollar->cur->value);
	dollar->cur->value = join(final, dollar->parts[2], 0, 0);
	free(final);
	free(dollar->word);
	if (dollar->parts[0] != NULL)
	{
		free(dollar->parts[0]);
		dollar->parts[0] = NULL;
	}
	if (dollar->parts[2] != NULL)
	{
		free(dollar->parts[2]);
		dollar->parts[2] = NULL;
	}
	free(dollar->parts[1]);
	free(dollar->parts);
	dollar->flag = false;
}

char	*open_dollar(t_dollar *dollar, t_env_elem *env)
{
	char	*word;
	int		i;

	i = dollar->i;
	word = NULL;
	if (dollar->flag == true)
	{
		while (dollar->cur->value[i] && dollar->cur->value[i] == '$')
			i++;
		dollar->i = i;
		return (ft_strdup("$"));
	}
	while (env)
	{
		if (ft_strcmp(dollar->parts[1], env->key) == 0)
		{
			word = ft_strdup(env->value);
			return (word);
		}
		env = env->next;
	}
	return (word);
}

void	veragrum(char **begin, char **word, char **end, char **dollar)
{
	*begin = NULL;
	*word = NULL;
	*end = NULL;
	*dollar = NULL;
}

void	qt_check_for_dollar(t_dollar *dollar)
{
	if (dollar->cur->value[dollar->i] == 34 && dollar->qt == false)
		dollar->double_qt = !dollar->double_qt;
	if (dollar->cur->value[dollar->i] == 39 && dollar->double_qt == false)
		dollar->qt = !dollar->qt;
	dollar->word = NULL;
}

void	init_dollar(t_dollar *dollar, t_token **list)
{
	dollar->qt = false;
	dollar->double_qt = false;
	dollar->i = 0;
	dollar->j = 0;
	dollar->parts = NULL;
	dollar->word = NULL;
	dollar->word = NULL;
	dollar->cur = *list;
	dollar->flag = false;
	dollar->harcakan = NULL;
}
