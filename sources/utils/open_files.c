/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:07 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:50:35 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

void	token_to_cmds_helper1(int *len, t_token *t2, char **cm)
{
	*len = 0;
	while (t2 != NULL && t2->type != S_PIPE)
	{
		if (t2->type == WORD)
		{
			cm[*len] = t2->value;
			(*len)++;
		}
		t2 = t2->next;
	}
	cm[*len] = NULL;
}

void	token_to_cmds_helper(t_token *temp2, int *len, t_fds *fds)
{
	if (temp2->type == HERE_DOC)
	{
		fds->infd = here_doc_open(temp2->next->value);
		unlink(HERE_DOC_FILE);
	}
	if (temp2->type == IN_REDIR)
		fds->infd = open_file(temp2->next, INPUT);
	if (temp2->type == OUT_REDIR)
		fds->outfd = open_file(temp2->next, TRUNC);
	if (temp2->type == APPEND_REDIR)
		fds->outfd = open_file(temp2->next, APPEND);
	if (temp2->type == WORD)
		(*len)++;
}

void	init_fds(t_fds *fds)
{
	fds->infd = 0;
	fds->outfd = 1;
	fds->second_case = -1;
}

void	token_to_cmds(t_shell *shell, t_token *token_list)
{
	int		len;
	char	**cmd_args;
	t_token	*temp;
	t_token	*temp2;
	t_fds	fds;

	temp = token_list;
	while (temp != NULL)
	{
		init_fds(&fds);
		len = 0;
		temp2 = temp;
		while (temp2 != NULL && temp2->type != S_PIPE)
		{
			token_to_cmds_helper(temp2, &len, &fds);
			temp2 = temp2->next;
		}
		cmd_args = malloc(sizeof(char *) * (len + 1));
		if (!cmd_args)
			return ;
		token_to_cmds_helper1(&len, temp, cmd_args);
		ft_lstadd_back(shell, ft_lstnew(cmd_args, &fds));
		token_to_cmds_helper2(temp2, &temp);
	}
}

void	token_to_cmds_helper2(t_token *temp2, t_token **temp)
{
	if (temp2 != NULL)
		*temp = temp2->next;
	else
		*temp = temp2;
}
