/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:09:53 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:31:32 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	echo(char **cmd_args, int fd, int *is_builtin)
{
	int	i;
	int	ind;

	i = 1;
	ind = 1;
	*is_builtin = 1;
	echo_run_helper(cmd_args, i, fd, ind);
	return (0);
}

void	echo_run_helper(char **cmd_args, int i, int fd, int ind)
{
	int	flag;
	int	j;

	flag = 1;
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
		{
			j = 2;
			while (cmd_args[i][j] && cmd_args[i][j] == 'n')
				j++;
			if (cmd_args[i][j] == '\0')
			{
				ind++;
				flag = 0;
			}
			else
				break ;
		}
		else
			break ;
		i++;
	}
	write_helper(cmd_args, ind, fd, flag);
}

void	write_helper(char **cmd_args, int ind, int fd, int flag)
{
	while (cmd_args[ind])
	{
		fd_put_string(cmd_args[ind++], fd);
		if (cmd_args[ind])
			write (fd, " ", 1);
	}
	if (flag == 1)
		write (fd, "\n", 1);
}

void	fd_put_string(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}
