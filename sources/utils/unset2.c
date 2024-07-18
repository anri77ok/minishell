/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:19:07 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/07/17 22:42:57 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	count_env_nodes_(t_env_elem *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	delete_node_with_that_key(t_pipex *pipex, char *key)
{
	int			pos;
	t_env_elem	*temp;
	t_env_elem	*del_node;

	temp = pipex->envp;
	pos = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			del_node = temp;
			free(temp->key);
			temp->key = NULL;
			if (temp->value && temp->value[0] != '\0')
			{
				free(temp->value);
				temp->value = NULL;
			}
			if (temp->prev)
				temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			// if (pos != 0)
			// {
			// 	temp->next->prev = temp->prev;
			// 	temp->prev->next = temp->next;
			// 	free(del_node);
			// }
				
		}
		pos++;
		temp = temp->next;
	}
}
