#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	run_cmds(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->cmd_path, cmd->cmd_args, env) == -1)
			printf("ERROR\n");
	}
}