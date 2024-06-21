#include "minishell.h"
#include "tokenization.h"
#include "utils.h"

int	main(int ac, char **av, char **env)
{
	t_token	*tokens;
	char	*cmd_line;

	ac = 0;
	av = NULL;
	tokens = NULL;
	while (1)
	{
		cmd_line = readline("MINISHELL:");
		add_history(cmd_line);
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &tokens);
			dolarni2(&tokens, env);
			chakertni(&tokens);
			print_token_list(tokens);
		}
		ft_token_list_clear(&tokens);
		free(cmd_line);
	}
} 