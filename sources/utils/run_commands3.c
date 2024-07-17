/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:07:03 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/17 20:16:27 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	find_pathi_line(char **env, int i)
{
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH="))
			break ;
		i++;
	}
	return (i);
}

t_pipex	*run_cmds(t_shell *shell)
{
	t_pipex	pipex;
	t_pipex	*link;

	pipex_init(&pipex, shell);
	if (pipex.cmd_count > 1)
		init_pipes(&pipex);
	create_proceces(&pipex);
	close_pipes(&pipex);
	wait_processes(&pipex);
	if (pipex.pipes != NULL)
		free(pipex.pipes);
	pipex.pipes = NULL;
	free(pipex.pids);
	link = &pipex;
	return (link);
}
