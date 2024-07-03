#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	run_cmds(t_shell *shell, char **env)
{
	pid_t	pid;
	int	i;
	char	*arr;
	char	**matrix;

	t_pipex	pipex;

	pipex_init(&pipex, shell);
	if (pipex.cmd_count > 1)
		init_pipes(&pipex);
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (env[i])
		{
			if (ft_strstr(env[i], "PATH="))
				break ;
			i++;
		}
		arr = shell->cmds->cmd_args[0];
		matrix = ft_split(env[i] + 5, ':');
		// if (!matrix)
		// 	split_matrix_failed(pipex, split_cmd);
		shell->cmds->cmd_path = arr;
		if (access(shell->cmds->cmd_path, X_OK) != -1)
			if (execve(shell->cmds->cmd_path, shell->cmds->cmd_args, env) == -1)
				printf("ERROR\n");
		i = 0;
		while (matrix[i])
		{
			shell->cmds->cmd_path = ft_strjoin(matrix[i++], arr, '/');
			// if (!cmd)
			// 	join_failed(pipex, split_cmd, matrix);
			if (access(shell->cmds->cmd_path, X_OK) != -1)
				break ;
			free(shell->cmds->cmd_path);
		}
		// if (!matrix[i])
		// 	//chi kara execve ani
		if (execve(shell->cmds->cmd_path, shell->cmds->cmd_args, env) == -1)
			printf("ERROR\n");
	}
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