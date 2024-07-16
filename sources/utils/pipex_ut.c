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
	{
		p_error(pipex, MALLOC_ERR, NULL, 1);
		return ;
	}
    cur = pipex->cmds;
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipe(pipex->pipes[i]) == -1)
			p_error(pipex, PIPE_ERR, NULL, 1);
        if (cur && cur->output == 1)
			cur->output = pipex->pipes[i][1];
		if (cur->next && cur->next->input == 0)
			cur->next->input = pipex->pipes[i][0];
		i++;
		cur = cur->next;
    }
}
