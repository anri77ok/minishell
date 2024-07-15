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

	//printf("%d qanak\n", pipex->cmd_count);
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
		// printf("fd=%d\n",cur->input);
		// printf("fdoutput=%d\n",cur->output);
        if (pipe(pipex->pipes[i]) == -1)
			p_error(pipex, PIPE_ERR, NULL, 1);
		// if (cur->input == 20 || cur->output == 20)
		// {
		// 	printf("ambiguous redirect\n");
		// 	i++;
		// 	cur = cur->next;
		// 	continue ;
		// }
        if (cur && cur->output == 1)
		{
			cur->output = pipex->pipes[i][1];
			printf("pip1 - arajinn!!!\n");
		}
		if (cur->next && cur->next->input == 0)
		{
			cur->next->input = pipex->pipes[i][0];
			printf("pip2 - erkrord!!!\n");
		}
		i++;
		cur = cur->next;
    }
}
