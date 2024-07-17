/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:09:59 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:44:25 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	mini_exit(t_cmd *cmd, int *is_builtin, int is_in_fork)
{
	long long	exit_num;

	*is_builtin = 1;
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
		{
			printf("exit\n");
			g_exit_status = 1;
			fd_put_string("minishell: exit: too many arguments\n", 2);
		}
		else if (is_only_digits_and_plus_minus(cmd->cmd_args[1]) == -1)
			in_this_condition(cmd);
		else
		{
			exit_num = ft_atoll(cmd->cmd_args[1]);
			if (exit_num > INT_MAX || exit_num < INT_MIN
				|| ft_strlen(cmd->cmd_args[1]) > 11)
				in_this_condition(cmd);
			check_exit_num_plus_or_minus(exit_num);
		}
	}
	else
		just_exit_bez_argumentov(is_in_fork);
}

void	just_exit_bez_argumentov(int is_in_fork)
{
	g_exit_status = 0;
	if (is_in_fork != 1)
		printf("exit\n");
	exit(g_exit_status);
}

void	check_exit_num_plus_or_minus(long long exit_num)
{
	if (exit_num > 0)
		g_exit_status = exit_num % 256;
	if (exit_num < 0)
		g_exit_status = (exit_num % 256) + 256;
	printf("exit\n");
	exit (g_exit_status);
}

void	in_this_condition(t_cmd *cmd)
{
	printf("exit\n");
	g_exit_status = 255;
	er_hp1("minishell: exit: ", cmd->cmd_args[1],
		": numeric argument required\n", g_exit_status);
	exit(g_exit_status);
}

int	is_only_digits_and_plus_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
			i++;
		else
			return (-1);
	}
	return (1);
}
