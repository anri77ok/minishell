#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

extern int	g_exit_status;

void    init_pipes(t_pipex *pipex)
{
    int i;
    t_cmd *cur;

	pipex->pipes = malloc(sizeof(int [2]) * pipex->cmd_count - 1);
	if (!pipex->pipes)
	{}
		//error
    cur = pipex->cmds;
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipe(pipex->pipes[i]) == -1)
		{}
            //error
        if (cur && cur->output == 1)
			cur->output = pipex->pipes[i][1];
		if (cur->next && cur->next->input == 0)
			cur->next->input = pipex->pipes[i][0];
		i++;
		cur = cur->next;
    }
	// while (pipex->cmds)
	// {
	// 	// int	i = 0;
	// 	// while (pipex->cmds->cmd_args[i])
	// 	// 	printf("%s\n", pipex->cmds->cmd_args[i++]);
	// 	printf("path -- %s\n", pipex->cmds->cmd_args[0]);
	// 	pipex->cmds = pipex->cmds->next;
	// }
}

// void	run_builtins(t_pipex *pipex, t_cmd *cmd, int *is_builtin, int fork)
// {
// 	if (ft_strcmp(cmd->cmd_path, "env") == 0 && fork == 1)
// 		g_exit_status = print_env(pipex->envp);
// 	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0 && fork == 1)
// 		g_exit_status = pwd(STDOUT_FILENO);
// 	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
// 		g_exit_status = cd(pipex->cmds->cmd_args[1], pipex);
// 	else if (ft_strcmp(cmd->cmd_path, "echo") == 0 && fork == 1)
// 		g_exit_status = echo(cmd->cmd_args, STDOUT_FILENO);
// 	else if (ft_strcmp(cmd->cmd_path, "export") == 0)
// 		g_exit_status = export(pipex, cmd);
// 	else if (ft_strcmp(cmd->cmd_path, "unset") == 0)
// 		g_exit_status = unset(pipex, cmd);
// 	// else if (ft_strcmp(cmd->cmd_path, "exit") == 0)
// 	// 	built_exit(cmd, is_builtin, fork, 0);
// 	if (*is_builtin == 1 && fork == 1)
// 		exit(g_exit_status);
// }

