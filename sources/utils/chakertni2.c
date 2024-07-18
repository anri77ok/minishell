/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chakertni2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:06:31 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 15:09:07 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	get_quote(char *str, int i, char c)
{
	while (str[i])
	{
		i++;
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

char	*begin_func(int j, char *value)
{
	if (j != 0)
		return (ft_substr(value, 0, j, true));
	else
		return (ft_strdup(""));
}

char	*word_func(int i, int j, char *value)
{
	if (j + 1 != i)
		return (ft_substr(value, j + 1, i, true));
	else
		return (ft_strdup(""));
}

char	*end_func(int i, char *value)
{
	if (i + 1 != my_strlen(value))
		return (ft_substr(value, i + 1, ft_strlen(value), true));
	else
		return (ft_strdup(""));
}
