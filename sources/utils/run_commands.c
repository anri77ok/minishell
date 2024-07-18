/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:13:42 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 20:07:04 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

extern int	g_exit_status;

void	run_shell_cmd(t_pipex *pipex, t_cmd *cmd, int i, int *is_builtin)
{
	pid_t	pid;
	char	**env;

	env = NULL;
	pid = fork();
	if (pid == -1)
		p_error(pipex, FORK_ERR, NULL, 1);
	if (pid == 0)
	{
		dupeing(pipex, cmd);
		which_built_in_will_be_runed(pipex, cmd, is_builtin, 1);
		if (*is_builtin == 0)
			run_cmd_with_execve(pipex, cmd, i, env);
	}
	else
		pipex->pids[i] = pid;
	if (env != NULL)
		free(env);
}

void	run_cmd_with_execve(t_pipex *pipex, t_cmd *cmd, int i, char **env)
{
	char	*arr;
	char	**matrix;

	env = env_list_to_array(pipex->envp);
	i = find_pathi_line(env, i);
	if (!env[i])
		p_error(pipex, PATH_CHKA, cmd->cmd_path, 127);
	arr = cmd->cmd_args[0];
	matrix = ft_split(env[i] + 5, ':');
	cmd->cmd_path = arr;
	if (access(cmd->cmd_path, X_OK) != -1)
		if (execve(cmd->cmd_path, cmd->cmd_args, env) == -1)
			p_error(pipex, CMD_NOT_FOUND, NULL, 1);
	i = 0;
	while (matrix[i])
	{
		cmd->cmd_path = ft_strjoin(matrix[i++], arr, '/');
		if (access(cmd->cmd_path, X_OK) != -1)
			break ;
	}
	if (access(cmd->cmd_path, X_OK) != 0)
		p_error(pipex, CMD_NOT_FOUND, cmd->cmd_args[0], 127);
	if (execve(cmd->cmd_path, cmd->cmd_args, env) == -1)
		p_error(pipex, EXECVE_ERR, NULL, 1);
}

void	create_proceces(t_pipex *pipex)
{
	t_cmd	*cmd;
	int		i;
	int		is_builtin;

	i = 0;
	cmd = pipex->cmds;
	while (i < pipex->cmd_count)
	{
		is_builtin = 0;
		if (!cmd->cmd_path)
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		if (pipex->cmd_count == 1)
			which_built_in_will_be_runed(pipex, cmd, &is_builtin, 0);
		if (is_builtin == 0)
			run_shell_cmd(pipex, cmd, i, &is_builtin);
		cmd = cmd->next;
		i++;
	}
}

void	which_built_in_will_be_runed(t_pipex *pipex, t_cmd *cmd,
			int *is_builtin, int is_in_fork)
{
	if (ft_strcmp(cmd->cmd_path, "env") == 0)
		g_exit_status = print_env(pipex->envp, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		g_exit_status = pwd(STDOUT_FILENO, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
		g_exit_status = cd(pipex->cmds->cmd_args[1], pipex, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "echo") == 0)
	{
		if (is_in_fork == 1)
			g_exit_status = echo(cmd->cmd_args, STDOUT_FILENO, is_builtin);
		else
			g_exit_status = echo(cmd->cmd_args, cmd->output, is_builtin);
	}
	else if (ft_strcmp(cmd->cmd_path, "export") == 0)
		g_exit_status = export(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "unset") == 0)
		g_exit_status = unset(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "exit") == 0)
		mini_exit(cmd, is_builtin, is_in_fork);
	if (*is_builtin == 1 && is_in_fork == 1)
		exit(g_exit_status);
}

void	wait_processes(t_pipex *pipex)
{
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	if (pipex->cmd_count == 1 && check_is_built_in(pipex->cmds) == 1)
		return ;
	while (i < pipex->cmd_count)
	{
		pid = waitpid(pipex->pids[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			g_exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			g_exit_status = TERM_CODE_SHIFT + WTERMSIG(exit_status);
		i++;
	}
}
