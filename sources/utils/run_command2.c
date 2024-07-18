/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:06:53 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 19:26:25 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipex->pipes)
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
		}
		i++;
	}
}

void	dupeing(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->input != 0)
	{
		if (dup2(cmd->input, 0) == -1)
			p_error(pipex, DUP_ERR, NULL, 1);
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		if (dup2(cmd->output, 1) == -1)
			p_error(pipex, DUP_ERR, NULL, 1);
		close(cmd->output);
	}
	close_pipes(pipex);
}

void	pipex_init(t_pipex *pipex, t_shell *shell)
{
	pipex->pipes = NULL;
	pipex->cmd_count = count_shell_cmds(shell->cmds);
	pipex->cmds = shell->cmds;
	pipex->envp = shell->envr;
	pipex->pids = malloc(sizeof(pid_t) * (pipex->cmd_count + 1));
}

int	count_shell_cmds(t_cmd *shell_cmds)
{
	int		count_cmds;
	t_cmd	*cur;

	cur = shell_cmds;
	count_cmds = 0;
	while (cur)
	{
		count_cmds++;
		cur = cur->next;
	}
	return (count_cmds);
}

int	check_is_built_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_path, "env") == 0
		|| ft_strcmp(cmd->cmd_path, "pwd") == 0
		|| ft_strcmp(cmd->cmd_path, "echo") == 0
		|| ft_strcmp(cmd->cmd_path, "export") == 0
		|| ft_strcmp(cmd->cmd_path, "unset") == 0
		|| ft_strcmp(cmd->cmd_path, "exit") == 0
		|| ft_strcmp(cmd->cmd_path, "cd") == 0)
		return (1);
	return (-1);
}
