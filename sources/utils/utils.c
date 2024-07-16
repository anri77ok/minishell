/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:39 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/16 18:10:41 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:38 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/16 18:10:38 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "utils.h"

char	*str_type(int token_type)
{
	if (token_type == 0)
		return ("WORD          ");
	else if (token_type == 1)
		return ("S_PIPE        ");
	else if (token_type == 2)
		return ("D_PIPE        ");
	else if (token_type == 3)
		return ("S_AND         ");
	else if (token_type == 4)
		return ("D_AND         ");
	else if (token_type == 5)
		return ("D_QUOTE       ");
	else if (token_type == 6)
		return ("S_QUOTE       ");
	else if (token_type == 7)
		return ("IN_REDIR      ");
	else if (token_type == 8)
		return ("OUT_REDIR     ");
	else if (token_type == 9)
		return ("HERE_DOC      ");
	else if (token_type == 10)
		return ("APPEND_REDIR  ");
	else if (token_type == 11)
		return ("ERROR         ");
	else if (token_type == 12)
		return ("NONE          ");
	else if (token_type == 13)
		return ("FILEIN        ");
	else if (token_type == 14)
		return ("LIMITER       ");
	else if (token_type == 15)
		return ("FILEOUT       ");
	else if (token_type == 16)
		return ("APPEND_FILEOUT");
	else if (token_type == 17)
		return ("OPEN_PAR      ");
	else if (token_type == 18)
		return ("CLOSE_PAR     ");
	else
		return ("\033[0;031mTOKEN_TYPE_NOT_FOUND");
}

void	ft_token_list_clear(t_token **lst)
{
	t_token	*tmp;
	t_token	*last;

	if (!lst)
		return ;
	last = *lst;
	while (last)
	{
		tmp = last->next;
		free(last->value);
		free(last);
		last = tmp;
	}
	*lst = NULL;
}

char	*ft_strjoin(char const *s1, char const *s2, char sep)
{
	char	*r_s;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!r_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	r_s[j++] = sep;
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}

char	*join(char *s1, char *s2, size_t i, size_t j)
{
	char	*r_s;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	r_s = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r_s)
		return (NULL);
	while (s1[i])
	{
		r_s[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		r_s[j++] = s2[i];
		i++;
	}
	r_s[j] = '\0';
	return (r_s);
}
