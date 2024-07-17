/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:11:58 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:18:00 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	cd(char *path, t_pipex *pipex, int *is_builtin)
{
	char	*modified_cmd;
	char	old_path[PATH_MAX];
	char	new_path[PATH_MAX];

	modified_cmd = NULL;
	*is_builtin = 1;
	if (cd_helper_1(path, pipex, &modified_cmd) == 1)
		return (1);
	getcwd(old_path, PATH_MAX);
	if (cd_helper_2(modified_cmd) == 1)
		return (1);
	getcwd(new_path, PATH_MAX);
	update_env(pipex->envp, old_path, new_path);
	return (0);
}

int	cd_helper_1(char *path, t_pipex *pipex, char **modified_cmd)
{
	if (!path)
	{
		*modified_cmd = get_cmd_in_env(pipex->envp, "HOME");
		if (*modified_cmd == NULL || !*modified_cmd[0])
			return (fd_put_string("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (path && path[0] == '-' && ft_strlen(path) == 1)
	{
		*modified_cmd = get_cmd_in_env(pipex->envp, "OLDPWD");
		{
			if (*modified_cmd == NULL || !*modified_cmd[0])
				return (fd_put_string("minishell: cd: OLDPWD not set\n", 2), 1);
		}
	}
	else if ((path && path[0] == '~' && path[1] == '\0')
		|| (path && path[0] == '~' && path[1] == '/'))
		*modified_cmd = home_kpcnel_pathin(pipex->envp, path + 1);
	else
		*modified_cmd = path;
	return (0);
}

void	update_env(t_env_elem *env, char *old_path, char *new_path)
{
	t_env_elem	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "OLDPWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(old_path);
		}
		if (ft_strcmp(temp->key, "PWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(new_path);
		}
		temp = temp->next;
	}
}

char	*home_kpcnel_pathin(t_env_elem *env, char *path)
{
	char	*home_value;
	char	*res;

	home_value = get_cmd_in_env(env, "HOME");
	res = join(home_value, path, 0, 0);
	if (!res)
		return (NULL);
	return (res);
}

char	*get_cmd_in_env(t_env_elem *env, char *pntrvox)
{
	t_env_elem	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, pntrvox) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
