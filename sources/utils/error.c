/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:32:53 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/17 20:02:06 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	global(int exit_status, int set)
{
	static int	status;

	if (set == 1)
		status = exit_status;
	return (status);
}

void	multy_putstr_fd(char *start, char *mid, char *end, int fd)
{
	int		i;

	i = 0;
	if (start != NULL)
	{
		while (start[i])
			write(fd, &start[i++], 1);
	}
	if (mid != NULL)
	{
		i = 0;
		while (mid[i])
			write(fd, &mid[i++], 1);
	}
	if (end != NULL)
	{
		i = 0;
		while (end[i])
			write(fd, &end[i++], 1);
	}
}

int	e_2(char *s1, char s2, char *s3, int exit_status)
{
	// global(exit_status, 1);
	g_exit_status = exit_status;
	if (s1 != NULL)
		fd_put_string(s1, 2);
	write(2, &s2, 1);
	if (s3 != NULL)
		fd_put_string(s3, 2);
	return (exit_status);
}

int	er_hp1(char *s1, char *s2, char *s3, int exit_status)
{
	//global(exit_status, 1);
	g_exit_status = exit_status;
	multy_putstr_fd(s1, s2, s3, 2);
	return (exit_status);
}

void	p_error(t_pipex *pipex, int error_code, char *m, int s)
{
	if (pipex && pipex->pipes != NULL)
	{
		free(pipex->pipes);
		pipex->pipes = NULL;
	}
	if (error_code == ARGS_COUNT_ERR)
		exit(er_hp1("Invalid count of arguments\n", NULL, NULL, 1));
	else if (error_code == SYNTAX_ERR)
		er_hp1("minishell : syntax error near unexpected token `", m, "'\n", s);
	else if (error_code == QUOT_ERR)
		e_2("minishell : syntax error near unexpected token `", m[0], "'\n", s);
	else if (error_code == MALLOC_ERR)
		exit(er_hp1("minishell: ", NULL, ": malloc error\n", 1));
	else if (error_code == PIPE_ERR)
		perror("pipe failed");
	else if (error_code == FORK_ERR)
		perror("fork failed");
	else if (error_code == DUP_ERR)
		perror("dup failed");
	else if (error_code == CMD_NOT_FOUND)
		exit(er_hp1("minishell: ", m, ": command not found\n", s));
	else if (error_code == EXECVE_ERR)
		perror("execve failed");
	else if (error_code == PATH_CHKA)
		exit(er_hp1("minishell: ", m, ": No such file or directory\n", s));
}
