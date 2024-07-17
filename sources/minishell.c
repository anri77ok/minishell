/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:08:54 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 17:30:02 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;
	t_pipex *pipex;

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
		{
			// run_minianri(cmd_line, &token_list, &pipex, &shell);
			if (tokenization(cmd_line, &token_list) == 0)
			{
				if (check_syntax(token_list) != 2)
				{
					if (pipex == NULL)
						dolarni2(&token_list, env_list_to_array(shell->envr), false, false);
					else
						dolarni2(&token_list, env_list_to_array(pipex->envp), false, false);
					get_bez_empty_nodes(&token_list);
					chakertni(&token_list);
					token_to_cmds(shell, token_list);
					pipex = run_cmds(shell);
					print_token_list(token_list);	
				}
			}
		}
		free_shell_token(&shell, &token_list, cmd_line);
		system("leaks minishell");//
	}
	clear_shell_envr(shell);
	printf("exit\n");
}


void	run_minianri(char *cmd_line, t_token **token_list, t_pipex **pipex, t_shell **shell)
{
		// set_singals();
		// cmd_line = readline("\033[0;036m MINIVIBERSEIJ: \033[0m");
		// add_history(cmd_line);
		// if (cmd_line && *cmd_line)
		// {
			if (tokenization(cmd_line, token_list) == 0)
			{
				if (check_syntax(*token_list) != 2)
				{
					if (pipex == NULL)
						dolarni2(token_list, env_list_to_array((*shell)->envr), false, false);
					else
						dolarni2(token_list, env_list_to_array((*pipex)->envp), false, false);
					get_bez_empty_nodes(token_list);
					chakertni(token_list);
					token_to_cmds(*shell, *token_list);
					*pipex = run_cmds(*shell);
					print_token_list(*token_list);	
				}
			}
		// }
		// free_shell_token(shell, token_list, cmd_line);
}





