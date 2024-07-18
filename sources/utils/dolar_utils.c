/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:11 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 18:12:29 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"

extern int	g_exit_status;

void	karch(char *value, int *i, int *j, bool *flag_a)
{
	if (value[*i + 1] && value[*i + 1] == '?')
	{
		free(value);
		value = ft_itoa(g_exit_status);
		*flag_a = true;
	}
	*j = *i;
	while (value[*j] && (ft_isspace(value[*j]) != 1
			&& value[*j] != 34 && value[*j] != 39))
	{
		*j = *j + 1;
		if (value[*j] == '$' || value[*j] == '/' || value[*j] == '=')
			*flag_a = true;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**karch2(t_dollar *d, int start, int mid, int end)
{
	char	**arr;

	arr = NULL;
	arr = malloc(sizeof(char *) * 4);
	arr[0] = ft_substr(d->cur->value, 0, start, true);
	arr[1] = ft_substr(d->cur->value, start + 1, mid, true);
	if (d->harcakan == NULL)
		arr[2] = ft_substr(d->cur->value, mid, end - mid, false);
	else
		arr[2] = d->harcakan;
	arr[3] = NULL;
	return (arr);
}

void	karch3(char *p1, char **p, bool *flag)
{
	free(p1);
	free(p);
	*flag = false;
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
