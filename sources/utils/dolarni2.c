/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarni2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:31 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 21:16:58 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include "env.h"

void	kp(t_dollar *dollar)
{
	char	*final;

	final = join(dollar->parts[0], dollar->word, 0, 0);
	// printf("begin -> %s, word-> %s,end -> %s\n", begin, word, end);
	free(dollar->current->value);
	dollar->current->value = join(final, dollar->parts[2], 0, 0);
	printf("value -> %s\n", final);
	printf("%s, %s, %s, %s\n", dollar->word, dollar->parts[0], dollar->parts[1], dollar->parts[2]);
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

char	*open_dollar(t_dollar *dollar, char **env)
{
	char	*word;
	char	*envp;
	int		i;
	int		j;

	word = NULL;
	i = 0;
	if (dollar->flag == true)
		return (ft_strdup("$"));
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		envp = ft_substr(env[i], 0, j, false);
		if (ft_strcmp(dollar->parts[1], envp) == 0)
		{
			word = ft_substr(env[i], j + 1, ft_strlen(env[i]), true);
			free(envp);
			return (word);
		}
		free(envp);
		i++;
	}
	return(word);
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
	if (dollar->current->value[dollar->i] == 34 && dollar->qt == false)
		dollar->double_qt = !dollar->double_qt;
	if (dollar->current->value[dollar->i] == 39 && dollar->double_qt == false)
		dollar->qt = !dollar->qt;
}

void init_dollar(t_dollar *dollar, t_token **list)
{
	dollar->qt = false;
	dollar->double_qt = false;
	dollar->i = 0;
	dollar->j = 0;
	dollar->parts = NULL;
	dollar->word = NULL;
	dollar->word = NULL;
	dollar->current = *list;
	dollar->flag = false;
}

void	dolarni2(t_token **token_list, char **env, bool flag, bool flag_a)
{
	t_dollar d;

	init_dollar(&d, token_list);
	// int i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	while(d.current)
	{
		if ((d.current->type == WORD || (d.current->type >= 12 && d.current->type <= 16)) && d.current->type != LIMITER)
		{
			d.i = 0;
			while(d.current->value && d.current->value[d.i])
			{
				qt_check_for_dollar(&d);
				if (d.current->value[d.i] == '$' && d.qt == false)
				{
					if (d.current->value[d.i + 1] && d.current->value[d.i + 1] == '?')
					{
						free(d.current->value);
						d.current->value = ft_itoa(g_exit_status);
						break ;
					}		
					d.j = d.i;
					while (d.current->value[d.j] && (ft_isspace(d.current->value[d.j]) != 1 &&
					d.current->value[d.j] != 34 && d.current->value[d.j] != 39))
					{
						d.j = d.j + 1;
						if (d.current->value[d.j] == '$' || d.current->value[d.j] == '/' || d.current->value[d.j] == '=')
							break ;
					}
					if (d.j == d.i + 1)
						flag = true;
					d.parts = karch2(d.current->value, d.i, d.j, my_strlen(d.current->value));
					d.word = open_dollar(&d, env);
					kp(&d);
				}
				if (d.current->value[0] != '\0')
					d.i++;
			}
		}
		d.current = d.current->next;
		flag_a = false;
	}
	free_env(env);
}

char	*foo(void)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 2);
	ptr[0] = 48;
	ptr[1] = '\0';
	return (ptr);
}

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	long_n;

	if (n == 0)
		return (foo());
	len = ft_len(n);
	arr = malloc(sizeof(char) *(len + 1));
	if (!arr)
		return (NULL);
	long_n = (long)n;
	arr[len] = '\0';
	len--;
	if (n < 0)
	{
		arr[0] = '-';
		long_n = -long_n;
	}
	while (long_n != 0)
	{
		arr[len--] = ((long_n % 10) + 48);
		long_n /= 10;
	}
	return (arr);
}
