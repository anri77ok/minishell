/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarni2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:31 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 16:15:41 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include "env.h"

void	dollarni_helperi_axper(t_dollar *d)
{
	while (d->cur->value[d->j] && (ft_isspace(d->cur->value[d->j]) != 1
			&& d->cur->value[d->j] != 34 && d->cur->value[d->j] != 39))
	{
		d->j = d->j + 1;
		if (d->cur->value[d->j] == '$' || d->cur->value[d->j] == '/'
			|| d->cur->value[d->j] == '=')
			break ;
	}
}

void	dollarni_helper(t_dollar *d, t_env_elem *env, bool flag)
{
	while (d->cur->value && d->cur->value[d->i])
	{
		qt_check_for_dollar(d);
		if (d->cur->value[d->i] == '$' && d->qt == false)
		{
			if (d->cur->value[d->i + 1]
				&& d->cur->value[d->i + 1] == '?')
			{
				free(d->cur->value);
				d->cur->value = ft_itoa(g_exit_status);
				break ;
			}
			d->j = d->i;
			dollarni_helperi_axper(d);
			if (d->j == d->i + 1)
				flag = true;
			d->parts = karch2(d->cur->value, d->i, d->j,
					my_strlen(d->cur->value));
			d->word = open_dollar(d, env);
			kp(d);
		}
		if (d->cur->value[0] != '\0')
			d->i++;
	}
}

void	dolarni2(t_token **token_list, t_env_elem *env, bool flag, bool flag_a)
{
	t_dollar	d;

	init_dollar(&d, token_list);
	while (d.cur)
	{
		if ((d.cur->type == WORD || (d.cur->type >= 12 && d.cur->type <= 16))
			&& d.cur->type != LIMITER)
		{
			d.i = 0;
			dollarni_helper(&d, env, flag);
		}
		d.cur = d.cur->next;
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
