/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:12:02 by anrkhach          #+#    #+#             */
/*   Updated: 2024/07/17 19:41:07 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"
#include <sys/stat.h>

int	cd_helper_2(char *mc)
{
	if (is_file_or_directory(mc) == 0)
	{
		er_hp1("minishell: cd:", mc, ": No such file or directory\n", 1);
		return (1);
	}
	if (is_directory(mc) == 0)
	{
		er_hp1("minishell: cd:", mc, ": Not a directory\n", 1);
		return (1);
	}
	if (can_access(mc) == 0)
	{
		er_hp1("minishell: cd:", mc, ": Permission denied\n", 1);
		return (1);
	}
	if (chdir(mc) == -1)
	{
		er_hp1("minishell: cd:", mc, ": No such file or directory\n", 1);
		return (1);
	}
	return (0);
}

int	can_access(char *modfied_cmd)
{
	if (access(modfied_cmd, R_OK | X_OK) != 0)
		return (0);
	return (1);
}

int	is_directory(char *modfied_cmd)
{
	struct stat	path_stat;

	if (stat(modfied_cmd, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

int	is_file_or_directory(char *modified_cmd)
{
	struct stat	path_stat;

	if (stat(modified_cmd, &path_stat) != 0)
		return (0);
	return (1);
}
