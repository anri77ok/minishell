#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

#include <sys/stat.h>

int	cd(char *path, t_pipex *pipex)
{
	char	*modified_cmd = NULL;
	char	old_path[PATH_MAX];
	char	new_path[PATH_MAX];
	if (!path)
	{
		modified_cmd = get_cmd_in_env(pipex->envp, "HOME");
		if (modified_cmd == NULL || !modified_cmd[0])
		{
			fd_put_string("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (path && path[0] == '-' && ft_strlen(path))
	{
		modified_cmd = get_cmd_in_env(pipex->envp, "OLDPWD");
		{
			if (modified_cmd == NULL || !modified_cmd[0])
			{
				fd_put_string("minishell: cd: OLDPWD not set\n", 2);
				return (1);
			}
		}
	}
	else if (path && path[0] == '~')
	{
		modified_cmd = home_kpcnel_pathin(pipex->envp, path);
	}
	else
		modified_cmd = path;
	getcwd(old_path, PATH_MAX);
	printf("old=%s\n",old_path);
	if (cd_helper_1(modified_cmd) == 1)
	{
		printf("STOOOOP\n");
		return (1);
	}
	getcwd(new_path, PATH_MAX);
	printf("new=%s\n",new_path);
	update_env(pipex->envp, old_path, new_path);
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
			temp->value = ft_strdup(old_path);
		}
		if (ft_strcmp(temp->key, "PWD") == 0)
			temp->value = ft_strdup(new_path);
		temp = temp->next;
	}
}

int	cd_helper_1(char *modified_cmd)
{
	if (is_file_or_directory(modified_cmd) == 0)
	{
		perror("No such file or directory\n");//sa nshanakuma vor chenq kara info imananq tvayl modified_path-@ fayla te direktoria
		//Причины могут быть различными, например:
		// Файл или директория не существуют.
		// У вас нет прав доступа к указанному пути.
		return (1);
	}
	if (is_directory(modified_cmd) == 0)
	{
		fd_put_string("Error: %s is not a directory\n", 2);//modified_cmd);
		return (1);
	}
	if (can_access(modified_cmd) == 0)
	{
		perror("Permission denided");
		return (1);
	}
	if (chdir(modified_cmd) == -1)
	{
		// return (p_err(1, "minishell: cd: ", mc,
		// 	": No such file or directory\n"), 1);
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
	struct stat path_stat;

	if (stat(modfied_cmd, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
	// Проверяем, является ли путь директорией
}

int is_file_or_directory(char *modified_cmd)
{
	struct stat path_stat;

    // Получаем информацию о файле
    if (stat(modified_cmd, &path_stat) != 0)
        return (0);
	return (1);
}



char	*home_kpcnel_pathin(t_env_elem *env, char *path)
{
	char	*HOME_VALUE;
	char	*res;

	HOME_VALUE = get_cmd_in_env(env, "HOME");
	res = join(HOME_VALUE, path);
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
