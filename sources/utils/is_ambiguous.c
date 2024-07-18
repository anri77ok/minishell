/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ambiguous.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:57:35 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/18 15:10:41 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

int	check_is_ambiguous(t_token *cmd)
{
	if (!cmd)
	{
		er_hp1("minishell: ", NULL, ": ambiguous redirect\n", -20);
		return (-20);
	}
	return (0);
}
