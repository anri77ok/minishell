/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:26:56 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 18:28:20 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	check_syntax(t_token *token)
{
	t_token	*tm;

	tm = token;
	while (tm)
	{
		if (tm->type == S_PIPE && (!tm->prev || !tm->next))
			return (p_error(NULL, SYNTAX_ERR, tm->value, 2), 2);
		if (tm->type == OUT_REDIR || tm->type == IN_REDIR
			|| tm->type == APPEND_REDIR || tm->type == HERE_DOC)
		{
			if (!tm->next)
				return (p_error(NULL, SYNTAX_ERR, "newline", 2), 2);
			if (tm->next->type == APPEND_FILEOUT || tm->next->type == LIMITER
				|| tm->next->type == FILEOUT || tm->next->type == FILEIN)
				return (0);
			return (p_error(NULL, SYNTAX_ERR, tm->next->value, 2), 2);
		}
		if (tm->type == S_PIPE && control_operators(tm->next) == 1)
			return (p_error(NULL, SYNTAX_ERR, tm->value, 2), 2);
		if (permitted_operator(tm))
			return (p_error(NULL, SYNTAX_ERR, tm->value, 2), 2);
		tm = tm->next;
	}
	return (0);
}

int	permitted_operator(t_token *token)
{
	if (token->type == D_PIPE || token->type == S_AND || token->type == D_AND)
		return (1);
	return (0);
}

int	control_operators(t_token *token)
{
	if (!token->value)
		return (1);
	if (token->type == S_AND || token->type == D_AND
		|| token->type == S_PIPE || token->type == D_PIPE)
		return (1);
	return (-1);
}

int	check_value_is_empty(char	*value)
{
	if (value[0] == '\0')
		return (1);
	return (-1);
}

int	syntx_err(char *value, int i)
{
	if (value[i] != '\0')
		return (1);
	return (0);
}
