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

void dupeing(t_pipex *pipex, t_cmd *cmd)
{
	printf("-----input-----%d\n", cmd->input);
	printf("-----output-----%d\n", cmd->output);
	if (cmd->input != 0)
	{
		printf("lavaa\n");
		if (dup2(cmd->input, 0) == -1)
			printf("DUP Error\n");
		close(cmd->input);
	}
	if (cmd->output != 1)//ste grel eir eli cmd->input
	{
		printf("lava\n");
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
	//t_cmd *cmd;
	int i;

	i = 0;
	//cmd = pipex->cmds;
	//while (i < pipex->cmd_count)
	//{
		//printf("%s\n", pipex->cmds->cmd_path);
		run_shell_cmd(pipex, pipex->cmds, i);
		printf("%d\n", pipex->cmd_count);
		//cmd = cmd->next;
		//i++;
	//}
}

void	run_cmds(t_shell *shell)
{
	t_pipex	pipex;

	pipex_init(&pipex, shell);
	if (pipex.cmd_count > 1)
	{
		init_pipes(&pipex);
		printf("ashxtec\n");
	}
	printf("heysav\n");
	// export(&pipex, shell->cmds);
	unset(&pipex, shell->cmds);
	// print_env(shell->envr);
	// create_proceces(&pipex);
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