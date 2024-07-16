#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"
#include <sys/stat.h>

int	cd_helper_2(char *modified_cmd)
{
	if (is_file_or_directory(modified_cmd) == 0)
	{
		error_helper1("minishell: cd:", modified_cmd, ": No such file or directory\n", 1);
		return (1);
	}
	if (is_directory(modified_cmd) == 0)
	{
		error_helper1("minishell: cd:", modified_cmd, ": Not a directory\n", 1);
		return (1);
	}
	if (can_access(modified_cmd) == 0)
	{
		error_helper1("minishell: cd:", modified_cmd, ": Permission denied\n", 1);
		return (1);
	}
	if (chdir(modified_cmd) == -1)
	{
		error_helper1("minishell: cd:", modified_cmd, ": No such file or directory\n", 1);
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
}

int is_file_or_directory(char *modified_cmd)
{
	struct stat path_stat;

    if (stat(modified_cmd, &path_stat) != 0)
        return (0);
	return (1);
}
