/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:09:10 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 15:23:55 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include <stdlib.h>

void	tokens_types(t_token *token_list)
{
	t_token			*current;
	t_token_params	params;

	params.cmd_found = 0;
	params.redir = 0;
	current = token_list;
	while (current)
	{
		current->type = set_token_type(current->value, 0);
		if (current->type == ERROR)
			printf("hop\n");
		if (current->prev != NULL && current->type == WORD
			&& ft_is_operator(current->prev->value, 0) > 0)
		{
			if (current->prev->type == IN_REDIR)
				current->type = FILEIN;
			if (current->prev->type == HERE_DOC)
				current->type = LIMITER;
			if (current->prev->type == OUT_REDIR)
				current->type = FILEOUT;
			if (current->prev->type == APPEND_REDIR)
				current->type = APPEND_FILEOUT;
		}
		current = current->next;
	}
}

int	syntx_err(char *value, int i)
{
	if (value[i] != '\0')
		return(1);
	return(0);
}

int	is_pipe_or_dpipe(char *value, int i)
{
	if (value[i + 1] && value[i] == value[i + 1] && syntx_err(value, i + 2) != 1)
		return (D_PIPE);
	if (syntx_err(value, i + 1) == 1)
		return (ERROR);
	return (S_PIPE);
}

int is_and_or_dand(char *value, int i)
{
	if (value[i + 1] && value[i] == value[i + 1] && syntx_err(value, i + 2) != 1)
		return (D_AND);
	if (syntx_err(value, i + 1) == 1)
		return (ERROR);
	return (S_AND);
}

int	is_append_or_out_redir(char *value, int i)
{
	if (value[i + 1] && value[i] == value[i + 1] && syntx_err(value, i + 2) != 1)
		return (APPEND_REDIR);
	if (syntx_err(value, i + 1) == 1)
		return (ERROR);
	return (OUT_REDIR);
}


t_token_type	set_token_type(char *value, int i)
{
	if (!value || i < 0)
		return (ERROR);
	if (value[i] == '|')
		return (is_pipe_or_dpipe(value, i));
	else if (value[i] == '&')
		return (is_and_or_dand(value, i));
	else if (value[i] == '>')
		return (is_append_or_out_redir(value, i));
	else if (value[i] == '<')
	{
		if (value[i + 1] && value[i] == value[i + 1] && syntx_err(value, i + 2) != 1)
			return (HERE_DOC);
		if (syntx_err(value, i + 1) == 1)
		{
			//printf();
			return (ERROR);
		}
		return (IN_REDIR);
	}
	return (WORD);
}
