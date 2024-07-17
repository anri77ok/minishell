/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:11:45 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:48:39 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

t_env_elem	*merge_sort(t_env_elem *begin_list, int (*cmp)())
{
	t_env_elem	*left;
	t_env_elem	*right;
	t_env_elem	*pre_right;
	int			list_size;

	list_size = ft_env_elem_size(begin_list);
	if (begin_list == NULL || list_size < 2)
		return (begin_list);
	left = begin_list;
	pre_right = ft_env_elem_at(begin_list, (list_size / 2) - 1);
	right = pre_right->next;
	pre_right->next = NULL;
	left = merge_sort(left, cmp);
	right = merge_sort(right, cmp);
	return (ft_merge_sorted_list(left, right, cmp));
}

t_env_elem	*ft_merge_sorted_list(t_env_elem *left,
	t_env_elem *right, int (*cmp)())
{
	t_env_elem	dummy;
	t_env_elem	*sorted_list;

	sorted_list = &dummy;
	while (left && right)
	{
		if ((*cmp)(left->key, right->key) < 0)
		{
			sorted_list->next = left;
			left = left->next;
		}
		else
		{
			sorted_list->next = right;
			right = right->next;
		}
		sorted_list = sorted_list->next;
	}
	if (left)
		sorted_list->next = left;
	else if (right)
		sorted_list->next = right;
	return (dummy.next);
}

t_env_elem	*ft_env_elem_at(t_env_elem *begin_list, unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	while (i < nbr && begin_list->next)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i != nbr)
		return (NULL);
	return (begin_list);
}

int	ft_env_elem_size(t_env_elem *begin_list)
{
	int	count;

	count = 0;
	while (begin_list)
	{
		count++;
		begin_list = begin_list->next;
	}
	return (count);
}

t_env_elem	*get_copy_env(t_env_elem *env)
{
	t_env_elem	*copy;
	t_env_elem	*node;
	t_env_elem	*temp;

	copy = NULL;
	temp = env;
	while (temp)
	{
		node = ft_lstnew_dlya_env(temp->key, temp->value, false);
		ft_lstadd_back_env(&copy, node);
		temp = temp->next;
	}
	return (copy);
}
