/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:09:23 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/18 16:25:25 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"
#include <stdlib.h>
#include "pipex.h"
#include "minishell.h"

int	tok_helper(char *cmd_line, t_tokvar *tok)
{
	while (cmd_line[tok->j] && ft_isspace(cmd_line[tok->j]) == 0)
	{
		if (cmd_line[tok->j] == 34 || cmd_line[tok->j] == 39)
		{
			tok->k = tok->j;
			tok->j = is_quote(cmd_line, tok->j);
			if (tok->j == -1)
			{
				p_error(NULL, QUOT_ERR, &cmd_line[tok->k], 2);
				return (-1);
			}
			tok->quote = true;
		}
		else
			tok->j = tok->j + 1;
	}
	return (0);
}

void	init_tok(t_tokvar *tok, char *cmd_line)
{
	tok->i = skip_whitespaces(cmd_line, 0);
	tok->j = tok->i;
	tok->k = 0;
	tok->quote = false;
}

void	toks(t_tokvar *tok, t_token **token_list, char *cmd_line)
{
	tokens_types(*token_list);
	tok->j = skip_whitespaces(cmd_line, tok->j);
	tok->i = tok->j;
}

int	tokenization(char *cmd_line, t_token **token_list)
{
	char		*line;
	t_token		*new_token;
	t_tokvar	tok;

	init_tok(&tok, cmd_line);
	while (cmd_line[tok.j])
	{
		if (tok_helper(cmd_line, &tok) == -1)
			return (-1);
		if (tok.quote == true)
		{
			line = ft_substr(cmd_line, tok.i, tok.j - tok.i, false);
			new_token = create_new_token(line);
			add_to_list(token_list, new_token);
		}
		else
		{
			line = ft_substr(cmd_line, tok.i, tok.j - tok.i, false);
			spliting(token_list, line, 0, 0);
		}
		toks(&tok, token_list, cmd_line);
		if (tok.quote == false)
			free(line);
	}
	return (0);
}
