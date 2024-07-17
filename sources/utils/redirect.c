/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:10:12 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 20:02:59 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

t_cmd	*ft_lstnew(char **cmd_args, t_fds *fds)
{
	t_cmd	*new_node;

	new_node = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd_args = cmd_args;
	new_node->cmd_path = cmd_args[0];
	if (fds->infd == -20 || fds->outfd == -20)
		return (NULL);
	if (fds->infd > 2)
		new_node->input = fds->infd;
	else
		new_node->input = 0;
	if (fds->outfd > 2)
		new_node->output = fds->outfd;
	else
		new_node->output = 1;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_shell *shell, t_cmd *new)
{
	t_cmd	*current;

	if (shell->cmds == NULL)
	{
		shell->cmds = new;
		return ;
	}
	current = shell->cmds;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = new;
}

int	open_file(t_token *cmd, int type)
{
	int	fd;

	fd = -1;
	if (check_is_ambiguous(cmd) == -20)
		return (-20);
	if (type == INPUT)
	{
		fd = open(cmd->value, O_RDONLY);
		if (fd < 0)
			fd = -2;
	}
	else if (type == TRUNC)
		fd = open(cmd->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(cmd->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd > 2)
		return (fd);
	if (fd == -1)
		return (er_hp1("minishell: ", cmd->value,
				": Permission denied\n", 1), 1);
	if (fd == -2 && type != INPUT)
		return (er_hp1("minishell: ", cmd->value,
				": No such file or directory\n", 1), 1);
	return (-1);
}

void	here_doc_write(int tmp_file_fd, char *lim)
{
	char	*buff;
	int		buff_size;

	while (1)
	{
		buff = readline("\033[0;032m> \033[0m");
		buff_size = ft_strlen(buff);
		if (buff == NULL || ft_strcmp(buff, lim) == 0)
		{
			free(buff);
			break ;
		}
		write(tmp_file_fd, buff, buff_size);
		write(tmp_file_fd, "\n", 1);
		free(buff);
		buff = NULL;
	}
	close(tmp_file_fd);
}

int	here_doc_open(char *lim)
{
	int	fd;

	fd = open(HERE_DOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(HERE_DOC_FILE, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);
	here_doc_write(fd, lim);
	close(fd);
	fd = open(HERE_DOC_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
