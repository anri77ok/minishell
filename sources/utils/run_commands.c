#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

extern int	g_exit_status;

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

void dupeing(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->input != 0)
	{
		if (dup2(cmd->input, 0) == -1)
			printf("DUP Error\n");
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		if (dup2(cmd->output, 1) == -1)
			printf("DUP Error\n");
		close(cmd->input);
	}
	close_pipes(pipex);
}

void run_shell_cmd(t_pipex *pipex, t_cmd *cmd, int i)
{
	pid_t	pid;
	char	*arr;
	char	**matrix;
	char	**env;

	// (void)cmd;
	env = NULL;
	pid = fork();
	if (pid == 0)
	{
		env = env_list_to_array(pipex->envp);
		dupeing(pipex, cmd);
		while (env[i])
		{
			if (ft_strstr(env[i], "PATH="))
				break ;
			i++;
		}
		arr = pipex->cmds->cmd_args[0];
		matrix = ft_split(env[i] + 5, ':');
		pipex->cmds->cmd_path = arr;
		if (access(pipex->cmds->cmd_path, X_OK) != -1)
			if (execve(pipex->cmds->cmd_path, pipex->cmds->cmd_args, env) == -1)
				printf("ERROR\n");
		i = 0;
		while (matrix[i])
		{
			// free(pipex->cmds->cmd_path);
			pipex->cmds->cmd_path = ft_strjoin(matrix[i++], arr, '/');
			if (access(pipex->cmds->cmd_path, X_OK) != -1)
				break ;
		}
		if (execve(pipex->cmds->cmd_path, pipex->cmds->cmd_args, env) == -1)
			printf("ERROR\n");
	}
	else
		pipex->pids[i] = pid;
	if (env != NULL)
		free(env);
}

void create_proceces(t_pipex *pipex)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = pipex->cmds;
	while (i < pipex->cmd_count)
	{
		if (!cmd->cmd_path)
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		which_built_in_will_be_runed(pipex, cmd);
		run_shell_cmd(pipex, pipex->cmds, i);
		cmd = cmd->next;
		i++;
	}
}

void	which_built_in_will_be_runed(t_pipex *pipex, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_path, "env") == 0)
		g_exit_status = print_env(pipex->envp);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		g_exit_status = pwd(STDOUT_FILENO);
	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
		g_exit_status = cd(pipex->cmds->cmd_args[1], pipex);
	else if (ft_strcmp(cmd->cmd_path, "echo") == 0)
		g_exit_status = echo(cmd->cmd_args, STDOUT_FILENO);
	else if (ft_strcmp(cmd->cmd_path, "export") == 0)
		g_exit_status = export(pipex, cmd);
	else if (ft_strcmp(cmd->cmd_path, "unset") == 0)
		g_exit_status = unset(pipex, cmd);
	// else if (ft_strcmp(cmd->cmd_path, "exit") == 0)
	// 	built_exit(cmd, is_builtin, 0);
	// if (*is_builtin == 1)
	// 	exit(g_exit_status);
}


void	wait_processes(t_pipex *pipex)
{
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	//  && is_builtin(pipex->cmds->cmd_path
	if (pipex->cmd_count == 1)
		return ;
	while (i < pipex->cmd_count - 1)
	{
		pid = waitpid(pipex->pids[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			g_exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			g_exit_status = TERM_CODE_SHIFT + WTERMSIG(exit_status);
		i++;
	}
}

void	run_cmds(t_shell *shell)
{
	t_pipex	pipex;

	pipex_init(&pipex, shell);
	if (pipex.cmd_count > 1)
	{
		init_pipes(&pipex);
		//printf("ashxtec\n");
	}

	printf("heysav\n");
	export(&pipex, shell->cmds);
	// unset(&pipex, shell->cmds);
	// cd(pipex.cmds->cmd_args[1], &pipex);
	// print_env(shell->envr);
	// create_proceces(&pipex);

	// printf("cmds count ----> %d\n", pipex.cmd_count);
	//export(&pipex, shell->cmds);
	// print_env(shell->envr);
	// create_proceces(&pipex);
	close_pipes(&pipex);
	wait_processes(&pipex);
	if (pipex.pipes != NULL)
		free(pipex.pipes);
	pipex.pipes = NULL;
	free(pipex.pids);
	//return (EXIT_SUCCESS);

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
	int	count_cmds;
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