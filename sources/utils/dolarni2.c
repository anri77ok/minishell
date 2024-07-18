/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarni2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:31 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 15:35:43 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include "env.h"

void dollarni_helperi_axper(t_dollar *d)
{
	while (d->current->value[d->j] && (ft_isspace(d->current->value[d->j]) != 1 &&
	d->current->value[d->j] != 34 && d->current->value[d->j] != 39))
	{
		d->j = d->j + 1;
		if (d->current->value[d->j] == '$' || d->current->value[d->j] == '/' || d->current->value[d->j] == '=')
			break ;
	}
}

void dollarni_helper(t_dollar *d, t_env_elem *env, bool flag)
{
	while(d->current->value && d->current->value[d->i])
	{
		qt_check_for_dollar(d);
		if (d->current->value[d->i] == '$' && d->qt == false)
		{
			if (d->current->value[d->i + 1] && d->current->value[d->i + 1] == '?')
			{
				free(d->current->value);
				d->current->value = ft_itoa(g_exit_status);
				break ;
			}
			d->j = d->i;
			dollarni_helperi_axper(d);
			if (d->j == d->i + 1)
				flag = true;
			d->parts = karch2(d->current->value, d->i, d->j, my_strlen(d->current->value));
			d->word = open_dollar(d, env);
			kp(d);
		}
		if (d->current->value[0] != '\0')
			d->i++;
	}
}

void	dolarni2(t_token **token_list, t_env_elem *env, bool flag, bool flag_a)
{
	t_dollar d;

	init_dollar(&d, token_list);
	while(d.current)
	{
		if ((d.current->type == WORD || (d.current->type >= 12 && d.current->type <= 16)) && d.current->type != LIMITER)
		{
			d.i = 0;
			dollarni_helper(&d, env, flag);
		}
		d.current = d.current->next;
		flag_a = false;
	}
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

