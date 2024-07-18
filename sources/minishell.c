/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:08:54 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:06 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	g_exit_status = 0;

void	main_helper(t_token **token_list, t_shell *shell,
		char *cmd_line, t_pipex **ppx)
{
	if (tokenization(cmd_line, token_list) == 0)
	{
		if (check_syntax(*token_list) != 2)
		{
			dolarni2(token_list, shell->envr, false, false);
			get_bez_empty_nodes(token_list);
			chakertni(token_list);
			token_to_cmds(shell, *token_list);
			*ppx = run_cmds(shell);
			print_token_list(*token_list);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;
	t_pipex	*pipex;

	pipex = NULL;
	if (argc > 1)
		p_error(NULL, ARGS_COUNT_ERR, NULL, 1);
	argv = NULL;
	token_list = NULL;
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(shell->envr, env);
	shell->cmds = NULL;
	cmd_line = "";
	while (cmd_line)
	{
		set_singals();
		cmd_line = readline("\033[0;036m MINIVIBERSEIJ: \033[0m");
		add_history(cmd_line);
		if (cmd_line && *cmd_line)
			main_helper(&token_list, shell, cmd_line, &pipex);
		free_shell_token(&shell, &token_list, cmd_line);
		system("leaks minishell");
	}
	clear_shell_envr(shell);
	printf("exit\n");
}
