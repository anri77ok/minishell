#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_cnt - 1)
	{
		if (pipex->pipes)
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
		}
		i++;
	}
}

void duping(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->input != 0)
	{
		if (dup2(cmd->input, 0) == -1)
			printf("DUP Error\n");
		close(cmd->input);
	}
	if (cmd->input != 1)
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

	env = NULL;
	pid = fork();
	if (pid == 0)
	{
		env = env_list_to_array(pipex->envp);
		dupeing()
		while (env[i])
		{
			if (ft_strstr(env[i], "PATH="))
				break ;
			i++;
		}
		arr = shell->cmds->cmd_args[0];
		matrix = ft_split(env[i] + 5, ':');
		shell->cmds->cmd_path = arr;
		if (access(shell->cmds->cmd_path, X_OK) != -1)
			if (execve(shell->cmds->cmd_path, shell->cmds->cmd_args, env) == -1)
				printf("ERROR\n");
		i = 0;
		while (matrix[i])
		{
			shell->cmds->cmd_path = ft_strjoin(matrix[i++], arr, '/');
			if (access(shell->cmds->cmd_path, X_OK) != -1)
				break ;
			free(shell->cmds->cmd_path);
		}
		if (execve(shell->cmds->cmd_path, shell->cmds->cmd_args, env) == -1)
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
		run_shell_cmd(pipex, cmd, i);
		cmd = cmd->next;
		i++;
	}
}

void	run_cmds(t_shell *shell, char **env)
{
	pid_t	pid;
	int	i;

	t_pipex	pipex;

	pipex_init(&pipex, shell);
	if (pipex.cmd_count > 1)
		create_proceces(&pipex);
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