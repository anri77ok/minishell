#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

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