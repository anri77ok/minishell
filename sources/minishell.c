#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

int	main(int ac, char **av, char **env)
{
	t_token	*tokens;
	// char	*cmd_line;
	t_shell	*shell;

	ac = 0;
	av = NULL;
	tokens = NULL;
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(shell->envr, env);
	while(shell->envr)
	{
		printf("key=%s\n",shell->envr->key);
		shell->envr = shell->envr->next;
	}
	// shell->cmds = NULL;
	// check_env(shell);
	// while (1)
	// {
	// 	cmd_line = readline("VIBERSEIJSHELL:");
	// 	add_history(cmd_line);
	// 	if (cmd_line && *cmd_line)
	// 	{
	// 		tokenization(cmd_line, &tokens);
	// 		dolarni2(&tokens, env);
	// 		// chakertni(&tokens);
	// 		token_to_cmds(shell, tokens);
	// 		// run_cmds(shell->cmds, env);
	// 		print_token_list(tokens);
	// 		int i = 0;
	// 		while (shell->cmds)
	// 		{
	// 			i = 0;
	// 			while (shell->cmds->cmd_args[i])
	// 				printf("%s\n", shell->cmds->cmd_args[i++]);
	// 			printf("path -- %s\n", shell->cmds->cmd_path);
	// 			shell->cmds = shell->cmds->next;
	// 		}
	// 	}
	// 	ft_token_list_clear(&tokens);
	// 	free(cmd_line);
	// }
} 