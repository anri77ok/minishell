#include "minishell.h"
#include "tokenization.h"
#include "utils.h"

int	main(void)
{
	t_token	*tokens;
	char	*cmd_line;

	tokens = NULL;
	while (1)
	{
		cmd_line = readline("MINISHELL:");
		if (cmd_line && *cmd_line)
		{
			tokenization(cmd_line, &tokens);
			//print_tokens(tokens);
		}
	}
} 