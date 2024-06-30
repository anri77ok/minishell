#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

int	main(int ac, char **av, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	ac = 0;
	av = NULL;
	token_list = NULL;
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(shell->envr, env);
	shell->cmds = NULL;
	// while(shell->envr)
	// {
	// 	printf("key=%s\n",shell->envr->value);
	// 	shell->envr = shell->envr->next;
	// }
	check_env(shell);
	while (1)
	{
		cmd_line = readline("VIBERSEIJSHELL:");
		add_history(cmd_line);
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &token_list);
			dolarni2(&token_list, env);
			chakertni(&token_list);
			token_to_cmds(shell, token_list);
			//run_cmds(shell->cmds, env);
			print_token_list(token_list);
			int i = 0;
			while (shell->cmds)
			{
				i = 0;
				while (shell->cmds->cmd_args[i])
					printf("%s\n", shell->cmds->cmd_args[i++]);
				printf("path -- %s\n", shell->cmds->cmd_path);
				shell->cmds = shell->cmds->next;
			}
		}
		ft_token_list_clear(&token_list);
		free(cmd_line);
	}
} 